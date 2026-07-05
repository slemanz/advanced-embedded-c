# Memory Pools

A memory pool, also known as a fixed-size allocator, is a pre-allocated block of
memory divided into fixed-size chunks.

When a program needs a chunk of memory, it's taken from the pool, and when that
chunk is no longer needed, it's returned to the pool.

**Key Concepts of Memory Pools**

1. **Pre-Allocation:** A large block of memory is reserved at initialization time,
before the system starts performing the main task. This pre-allocated memory
forms the memory pool.

2. **Fixed-Size Chunks:** The memory pool is divided into equal-sized blocks or
chunks. This chunk size is usually determined based on the expected needs of the
application.

3. **Allocation and Deallocation:** When the system needs memory, it takes a free
chunk from the pool (allocation). When the chunk is no longer required, it is
released back to the pool (deallocation).

The memory allocation within the pool occurs quickly and in a predictable way.

4. **Internal Management:** The memory pool manages the available and allocated
chunks. This can be done with a variety of mechanisms (e.g., linked lists, bit
arrays).

5. **No Fragmentation:** Because the blocks are fixed sized and they are never
subdivided, there is no fragmentation.

### Comparing UART Memory Pool Implementation with other Data Structures

The choice of data structures impacts performance, memory usage, determinism,
and reliability.

UART Buffering can implemented using various data structures:
- Memory Pool (Fixed Block Allocation)
- FIFO Circular Buffer
- Linked List-Based Buffering
- Dynamic Heap Allocation (malloc/free)

| Method | Deterministic? | Memory Overhead | Fragmentation? | Best For |
| --- | --- | --- | --- | --- |
| Memory Pool                   | Yes | Low  | No  | Real-time, fixed-size buffers |
| Circular Buffer (FIFO)        | Yes | Low  | No  | Continuous UART streaming |
| Linked List                   | No  | High | Yes | Variable-size messages |
| Heap Allocation (malloc/free) | No  | High | Yes | Dynamic, large buffers |

### Implementation

- [Pool Basic Implementation](app/Src/pool_basic.c)
- [Send message - driver uart](drivers/Src/driver_uart.c)
- [Send message - main.c file](app/Src/main.c)