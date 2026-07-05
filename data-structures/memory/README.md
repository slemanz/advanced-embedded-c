# Memory Allocations

**Static Memory Allocation**

- Static memory allocation occurs at compile-time, meaning memory space is
predefined and cannot be changed at runtime.

- The compiler assigns addresses to variables and allocates memory in the.bss
and .data sections of the executable file.

- Memory is allocated once and remains allocated throughout program execution.

- All static variables have fixed memory locations.

- No risk of fragmentation or runtime memory leaks.

- Predictability - Memory allocation is known at compile time, making debugging
easier.

- No fragmentation - Unlike dynamic memory, static allocation does not suffer
from memory fragmentation.

- Faster execution - No overhead from runtime memory allocation functions
(`malloc()`, `free()`).

- Memory inefficiency - Pre-allocated memory may be wasted if not fully utilized.

- Lack of flexibility - Cannot adjust memory size at runtime.

**Dynamic Memory Allocation**

- Dynamic memory allocation occurs at runtime, allowing memory to be allocated
and deallocated as needed.

- This is typically done using malloc(), calloc(), realloc(), and free()
functions from the C standard library.

- Memory is allocated and freed during program execution.

- Uses the heap memory region.

- Enables flexible memory management for varying data sizes.

- Efficient use of RAM - Memory is allocated only when needed.

- Flexible data structures - Enables use of dynamic structures like linked lists
and variable-sized buffers.

- Heap fragmentation - Frequent allocation and deallocation can fragment memory,
reducing available contiguous space

- Unpredictability - Memory allocation success is not guaranteed, and malloc()
may return NULL if RAM is exhausted.

- Performance overhead - Allocating and freeing memory at runtime incurs
computational overhead.

### Static Allocation in Realtime_Systems

Real-time embedded systems operate under strict timing constraints where
deterministic execution is essential.

Static Vs Dynamic:

| Factor                | Static Allocation                         | Dynamic Allocation |
| --- | --- | --- |
| Execution Time        | Deterministic (fixed at compile-time)     | Non-deterministic (depends on heap availability) |
| Memory Fragmentation  | No fragmentation                          | Heap fragmentation can cause allocation failures |
| Overhead              | Zero runtime overhead                     | CPU-intensive allocation/deallocation |
| Reliability           | More predictable behavior                 | Risk of memory leaks, dangling pointers |
| Real-Time Safety      | Ensures WCET (Worst-Case Execution Time)  | Unbounded allocation time disrupts RT execution |

**Downsides of Using Excessive Global and Static Variables**

While global and static variables provide persistent storage throughout program
execution, excessive use can introduce performance, debugging, and
maintainability challenges.

|Problem                    | Impact on Embedded Systems |
| --- | --- |
| Increased Memory Usage    | Every global/static variable consumes SRAM, reducing memory for stack/heap. |
| Reduced Modularity        | Global variables tie functions together, making reuse harder. |
| Data Inconsistency        | If a variable is modified in multiple locations, debugging becomes complex. |
| Race Conditions           | In multi-threaded or interrupt-driven systems, global variables require synchronization. |

### Practical Examples

- [Static Allocation](app/Src/static_allocation.c)
- [Dynamic Allocation](app/Src/dynamic_allocation.c)

### Common Memory Corruption Issue

**Memory Collision Risk:**

- If an embedded system has limited RAM, the stack and heap can collide, leading
to catastrophic failures.
- Solution: Use stack guards, heap analysis tools, and configure linker scripts
to define memory limits.

Memory corruption occurs when the code accidentally modifies memory regions it
is not meant to modify, leading to erratic behavior, system crashes, or security
vulnerabilities.

**Buffer Overflow**

- Occurs when writing occurs beyond allocated memory boundaries.
- Impact: Overwrites adjacent memory, leading to unpredictable behavior.

```C
char buffer[10];
strcpy(buffer, "This is too long!"); // Buffer overflow
```

Solution in this case:

1. Use strncpy() instead of strcpy(): The strncpy() function allows safe copying
with size restrictions, ensuring that only the allocated buffer size is written
to.

2. Enabling Compiler Warnings (-Woverflow in GCC): Many Compilers provide static
analysis tools to detect buffer overflows at compile-time. The -Woverflow flag
in GCC (GNU Compiler Collection) warns us when a buffer is too small for the
assigned value.

3. Implementing Stack Canaries: A stack canary is a random security value placed
between the function stack frame and the return address. If a buffer overflow
occurs and attempts to overwrite the return address, the canary value is
altered, triggering a system abort or exception.

How Stack Canaries Work
- Before a function executes, a random value (the canary) is stored.
- Before returning from the function, the canary value is checked.
- If the canary has been modified, the program detects a buffer overflow and
halts execution.

**Other possible issues when using dynamic memory:**

| Problem | Cause | Primary Consequence |
| --- | --- | --- |
| **Double Free** | Freeing a pointer twice. | Heap corruption -> Crash or undefined behavior. |
| **Use After Free** | Using a pointer after its memory is freed. | Data corruption or security vulnerabilities. |
| **Memory Leak** | Not freeing memory that is no longer needed. | Resource exhaustion → Program or system failure. |
| **Null Pointer Deref**| Using the result of a failed `malloc()` without checking. | Immediate program crash (segmentation fault). |
| **Buffer Overflow** | Writing past the end of an allocated block. | Corruption of heap metadata or adjacent data. |
| **Allocation Failure** | Heap is exhausted or fragmented. | Program cannot proceed if error is unhandled. |
| **Invalid Free** | Freeing a non-heap or corrupted pointer. | Severe heap corruption -> Immediate crash. |
| **Fragmentation** | Many small gaps between allocated blocks. | Failure to allocate large contiguous blocks. |