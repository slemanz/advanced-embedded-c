# Memory Allocations

Every variable a firmware uses lives somewhere: flash, the .data or .bss region
of RAM, the stack, or the heap. Where it lives decides when the space is
reserved, whether it can run out, and whether the timing is predictable. This
module walks the choices with two runnable demos, one that only ever uses
compile-time storage and one that goes through `malloc`, `calloc`, `realloc`,
and `free`, so the tradeoff is concrete rather than a rule you take on faith.

## The idea

There are two ways to get memory, and the difference is *when* the space is
decided.

Static allocation is settled at compile and link time. Globals, `static` locals,
and fixed arrays get a fixed address in `.data` (if initialized) or `.bss` (if
not), and constants go to flash. The space exists for the whole run, so there is
nothing to fail at runtime and nothing to time. `static_allocation.c` shows the
forms: a global counter, a `static` local that keeps its value across calls, a
`static` struct, a `static` array, and a `const` that lives in flash.

```c
int global_counter = 10;          /* .data: has an initializer */
const float PI = 3.14159;         /* flash: read-only */

void staticFunctionDemo(void)
{
    static int static_counter = 0; /* .data, allocated once, kept across calls */
    int local_counter = 0;         /* stack, gone when the function returns */
    static_counter++;
    local_counter++;
}
```

Dynamic allocation is settled at runtime from the heap. `malloc` reserves a
block, `calloc` reserves and zeroes it, `realloc` resizes one, and `free`
returns it. The size can depend on data that only exists while running, which is
the whole point, but the call can fail, it takes a variable amount of time, and
every block you take you have to give back exactly once.

```c
int *ptr = malloc(5 * sizeof(int));
if (ptr == NULL) return;          /* the failure you must always handle */
/* ... use ptr ... */
free(ptr);                        /* exactly once, and not a byte after */
```

`dynamic_allocation.c` runs each of these and includes the failure modes on
purpose: the NULL check after every allocation, and a double-free example where
the second `free` is left commented out with a note on why.

## When to use each strategy

The default on an MCU is static, and the reasons are timing and certainty. A
statically allocated system uses a known, fixed amount of RAM that the linker
reports at build time, so you find out you are out of memory when you link, not
when a customer's board reboots. There is no allocator to run, so every access
is a fixed cost, which is what a real-time deadline needs. Reach for it for
anything with a bounded size: sensor buffers, protocol frames, state, lookup
tables. If you can name a maximum, allocate the maximum once.

| Factor | Static | Dynamic |
| --- | --- | --- |
| When space is decided | Compile/link time | Runtime |
| Can it fail | No | Yes, `malloc` returns NULL |
| Timing | Deterministic | Varies with heap state |
| Fragmentation | None | Grows with alloc/free churn |
| Out-of-memory found | At link | At runtime, often far from the cause |

Dynamic earns its place only when a size genuinely cannot be known until runtime
and cannot be bounded to a sane maximum: a variable-length message whose size
arrives in a header, a data structure that grows and shrinks with no useful
ceiling. Even then, the safer embedded answer is usually a fixed pool of
reusable blocks rather than the general heap, because a pool has a known size
and cannot fragment. See [pools](../pools/) for that, and [queues](../queues/)
for the fixed ring buffer that replaces a growing dynamic queue.

The trap in the middle is heap fragmentation. Repeated `malloc` and `free` of
different sizes leaves the heap full of small gaps, so a later request for a
large contiguous block fails even though the total free space is plenty. On a
desktop this is a slow leak of efficiency; on a device that must run for months
without rebooting it is a failure that shows up long after the code that caused
it. That is why long-running firmware that does use the heap usually allocates
everything once at startup and never frees, which is dynamic allocation used to
buy flexibility at boot with none of the runtime risk.

One more static caution: leaning on globals because they are easy is its own
problem. Every global consumes SRAM for the whole run, ties functions together
so they are harder to reuse, and turns any interrupt that touches the same
variable into a race unless you guard it. Static allocation is the right default;
a wall of globals is not the same thing.

## Common ways memory goes wrong

Static and dynamic fail differently, and knowing which failure you are exposed
to is half of choosing.

The static and stack side is dominated by overflow. Writing past the end of a
fixed array (`strcpy` into a buffer that is too small is the classic) corrupts
whatever sits next to it. The fixes are size-bounded calls (`strncpy` over
`strcpy`), compiler warnings (`-Woverflow`), and stack canaries, a known value
placed between a frame and its return address that is checked on the way out so
an overflow that reaches the return address is caught instead of silently taken.
The other static-side hazard is a stack-versus-heap collision: on a small part
the two grow toward each other, and if they meet the result is corruption with
no warning, which is why the linker script fixes the limits of each region.

The dynamic side has its own catalog, and every entry is a bug the compiler
cannot catch for you.

| Problem | Cause | Consequence |
| --- | --- | --- |
| Double free | Freeing the same pointer twice | Heap corruption, later crash |
| Use after free | Using a pointer after `free` | Corruption or a security hole |
| Memory leak | Never freeing what you took | RAM runs out over time |
| Null deref | Using `malloc`'s result without checking | Immediate crash |
| Buffer overflow | Writing past a block | Corrupts heap metadata or a neighbor |
| Invalid free | Freeing a non-heap or corrupt pointer | Severe heap corruption |
| Fragmentation | Many small gaps between blocks | Large allocations fail |

Most of these have no equivalent in the static demo, which is the honest
argument for the static default: the whole class of leak, double-free, and
use-after-free bugs simply cannot happen when there is no `free` to call.

## Build and run

STM32F411 (black pill). The Makefile builds `app/Src/main.c`, and this module
ships the demo as two separate files instead, so pick one and make it `main.c`
first (copy or rename `static_allocation.c` or `dynamic_allocation.c` to
`app/Src/main.c`). Then `make` builds `Build/flash.elf` and `Build/flash.bin`,
and `make load` flashes it through OpenOCD with a J-Link over SWD. The chosen
demo prints its walkthrough on UART2 at 115200 and then blinks the LED.

## Files

- [app/Src/static_allocation.c](app/Src/static_allocation.c): globals, `static`
  locals, a `static` struct and array, and a flash `const`, each printed so you
  can see what persists and what resets.
- [app/Src/dynamic_allocation.c](app/Src/dynamic_allocation.c): `malloc`,
  `calloc`, `realloc`, and `free`, each with its NULL check, plus a double-free
  example left commented with the reason.
- [app/Src/config.c](app/Src/config.c): clocks, UART, and driver setup shared by
  both demos.
