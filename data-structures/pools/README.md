# Memory Pools

A memory pool is a fixed-size allocator: one block of memory reserved at startup
and cut into equal chunks, handed out one chunk at a time and returned when
done. It buys you the thing dynamic allocation offers, taking and releasing
memory at runtime, without the things that make the heap a bad idea on a
microcontroller. Allocation is a couple of pointer moves, the time is always the
same, and fragmentation cannot happen because the blocks are never subdivided.

## The idea

The pool is a static two-dimensional array plus a pointer to the first free
block. The trick is where the free list lives: while a block is free, its own
bytes hold the `next` pointer, so tracking the free blocks costs no extra RAM at
all.

```c
typedef struct MemBlock
{
    struct MemBlock *next;   /* only meaningful while the block is free */
} MemBlock_t;

typedef struct {
    uint8_t pool[MEMORY_POOL_SIZE][MEMORY_BLOCK_SIZE];  /* the storage, static */
    MemBlock_t *freelist;                               /* head of the free chain */
} MemoryPool_t;
```

Init threads every block onto the chain, last one pointing at NULL.

```c
void MemoryPool_Init(void)
{
    memPool.freelist = (MemBlock_t*)memPool.pool;
    for(int i = 0; i < MEMORY_POOL_SIZE - 1; i++)
        ((MemBlock_t*)memPool.pool[i])->next = (MemBlock_t*)memPool.pool[i+1];
    ((MemBlock_t*)memPool.pool[MEMORY_POOL_SIZE - 1])->next = NULL;
}
```

From there both operations are O(1) and branch-free apart from one check.
Allocating pops the head; freeing pushes the block back on the front.

```c
void *MemoryPool_Allocate(void)
{
    if(memPool.freelist == NULL) return NULL;   /* pool exhausted */
    MemBlock_t *block = memPool.freelist;
    memPool.freelist = block->next;
    return block;
}

void MemoryPool_free(void *ptr)
{
    MemBlock_t *block = ptr;
    block->next = memPool.freelist;             /* push onto the free chain */
    memPool.freelist = block;
}
```

That is the whole allocator. Compare it to `malloc`, which has to search for a
fit, split blocks, track sizes, and coalesce neighbors on free.

`pool_basic.c` is the pool on its own: ten 32-byte blocks, allocate two, free
both, printing the free count at each step. `main.c` (what the build runs) is
the pool wired into the UART driver: `uart_send_message` takes a block, copies
the message in, sends it, and returns the block.

## When to use it (and when not to)

A pool is the answer whenever you wanted dynamic allocation but cannot accept
the heap's behavior, which on an MCU is most of the time. The comparison is the
useful part:

| Method | Deterministic | Overhead | Fragments | Best for |
| --- | --- | --- | --- | --- |
| Memory pool | Yes | None, the link sits in the free block | No | Fixed-size buffers in real time |
| Ring buffer | Yes | Low | No | Continuous streaming |
| Linked list on the heap | No | A pointer per node, plus heap metadata | Yes | Variable-size items |
| `malloc`/`free` | No | High | Yes | Large or truly dynamic buffers |

This is the compromise [linked](../linked/) points at and the escape hatch from
the heap risks in [memory](../memory/): the free list here *is* a linked list,
but it runs over static storage with a ceiling known at build time, so there is
no allocation that can fragment and no size you did not budget for. For a pure
producer-consumer stream, a ring buffer is still simpler; see
[queues](../queues/).

The costs are real and all follow from "fixed". The pool can run out, and
`MemoryPool_Allocate` returns NULL when it does, so every call site has to
handle exhaustion, which is the same discipline `malloc` needs. One block size
fits all, so a 17-byte message in a 64-byte block wastes the rest, and a system
with genuinely varied sizes needs several pools with a rule for which to use.
Blocks must also be at least as large as a pointer, since the free list is
stored inside them.

Two things about this specific code, noted rather than fixed. First,
`memory_pool_allocate` and `memory_pool_free` both read and write the free-list
head without a critical section, so a pool shared between an ISR and the main
loop can lose or double-hand-out a block; here the UART interrupt only echoes,
so it does not bite, but the guard is what makes a pool interrupt-safe. Second,
`uart_send_message` allocates a block, copies into it, transmits byte by byte
blocking, and frees before returning, so the buffer never outlives the call and
a local array would do exactly the same job. The pool earns its keep when a
buffer must outlive the function that filled it: interrupt-driven or DMA
transmission where you hand the block to the hardware and free it in the
completion callback. As written, the demo shows the mechanism, not yet the
motivation.

## Build and run

STM32F411 (black pill). `make` builds `Build/flash.elf` and `Build/flash.bin`
from `app/Src/main.c`, and `make load` flashes it through OpenOCD with a J-Link
over SWD. The running demo sends two messages through the pooled UART path and
prints the remaining free block count on UART2 at 115200; bytes you type are
echoed back. To run the standalone pool demo instead, point `main.c` at
`pool_basic.c`.

## Files

- [app/Src/pool_basic.c](app/Src/pool_basic.c): the pool by itself, init,
  allocate, free, and a free-block count, printed step by step.
- [drivers/Src/driver_uart.c](drivers/Src/driver_uart.c): the same pool built
  into the UART driver (ten 64-byte blocks) and `uart_send_message` using it.
- [app/Src/main.c](app/Src/main.c): the demo the build runs, sending two
  messages through the pooled path.
