# Linked lists

A linked list is a chain of nodes, each holding a value and a pointer to the
next one. Unlike an array, the nodes do not sit contiguously in memory, so the
list can grow and shrink one node at a time and an insert or delete is just a
pointer swap, no shifting. That flexibility is the whole appeal, and on a
microcontroller it is also exactly what makes the structure worth a second look
before you reach for it.

```c
typedef struct node
{
    Command_t command;   /* the value this node holds */
    struct node *next;   /* NULL at the tail */
} Node_t;
```

## The idea

Each node points to the next; the `head` is the entry point and the tail's
`next` is NULL. Traversal walks the chain from the head. The three shapes are
singly linked (one `next` per node, one direction), doubly linked (a `prev` too,
so you can walk backward and delete a known node without finding its
predecessor), and circular (the tail points back at the head).

The two demos here both use a singly linked list as a queue, adding at the tail
and removing at the head.

`linked_command.c` is a command queue. A UART interrupt turns each received byte
into a `Command_t`, `malloc`s a node, and links it at the tail; the main loop
drains the queue from the head, running each command and `free`ing its node.

```c
Node_t *newNode = malloc(sizeof(Node_t));
if (newNode == NULL) return false;   /* the allocation that can fail */
newNode->command = command;
newNode->next = NULL;
/* walk to the tail, link it on */
```

`main.c` (the file the build runs) is an event log. A UART command parser
accepts `add_event`, `print_events`, and `remove_event`; each event node carries
an RTC timestamp and a description string, and `remove_event` unlinks a node by
timestamp, fixing the previous node's `next` around it and freeing it. It shows
the delete-in-the-middle that a linked list makes cheap and an array makes
painful.

## When a linked list makes sense on an MCU, and when an array is better

This is the part that matters, because the textbook answer and the embedded
answer differ. Every node in these demos is a `malloc`, and on a
microcontroller that carries costs an array does not have.

A linked list on an MCU means the heap, and the heap means the risks from
[memory](../memory/): a `malloc` can fail and must be checked (both demos do),
repeated alloc and free of nodes fragments the heap over a long run, and each
allocation takes a variable, non-deterministic amount of time. There is also
per-node overhead: every element pays for a `next` pointer, four bytes a node
here, which for a list of small values can cost more RAM than the values
themselves. And traversal chases pointers across scattered addresses, so it is
slower and less cache and prefetch friendly than walking a contiguous array.

A fixed array is the right default when you can name a maximum. It is one
contiguous block sized at build time, so there is no allocator, no fragmentation,
deterministic access, and no per-element pointer. Index access is O(1) and
iteration is a straight sweep. The array only loses when you must insert or
delete in the middle a lot, since that shifts every following element.

So the honest rule:

- **Array** when the size has a sane upper bound and the work is mostly index
  access and iteration. This is most embedded data: sensor buffers, lookup
  tables, fixed queues. If you can say "at most N", allocate N.
- **Linked list** when the size is genuinely unbounded or wildly variable, or
  when frequent middle insert and delete would make array shifting the
  bottleneck: an RTOS ready or priority list, an event list reordered as it
  grows, driver or device chains built and torn down at runtime.
- **The embedded compromise** when you want the list's O(1) splice without the
  heap's risk: pre-allocate a fixed array of nodes once and hand them out from a
  free list. That is a linked list over static storage, with a known ceiling and
  no fragmentation. See [pools](../pools/). And when the list is really just a
  FIFO between a producer and a consumer, a ring buffer beats a linked queue on
  every count that matters here; see [queues](../queues/).

There is a concrete hazard in `linked_command.c` worth flagging (noted, not
fixed): `insert_at_tail` runs inside the UART interrupt while the main loop runs
`remove_at_head` on the same list, so the list pointers and the allocator are
touched concurrently with no guard, and `malloc`/`free` inside an ISR is itself
non-deterministic and not reentrant-safe. It is the textbook argument for the
pool-plus-ring-buffer approach over a heap-backed list shared with an interrupt.

## Build and run

STM32F411 (black pill). `make` builds `Build/flash.elf` and `Build/flash.bin`
from `app/Src/main.c`, and `make load` flashes it through OpenOCD with a J-Link
over SWD. The running demo is the event log: type commands like `add_event
ButtonPressed*`, `print_events*`, or `remove_event 3679*` on UART2 at 115200
(each command ends with `*`). To run the command-queue demo instead, point
`main.c` at `linked_command.c`.

## Files

- [app/Src/linked_command.c](app/Src/linked_command.c): a command queue, insert
  at tail from the UART ISR, drain from the head in the main loop.
- [app/Src/linked_event_sim.c](app/Src/linked_event_sim.c): the event-list
  operations exercised without live input.
- [app/Src/main.c](app/Src/main.c): the event log with an RTC timestamp per node
  and a UART command parser for add, print, and remove; this is what the build
  runs.
