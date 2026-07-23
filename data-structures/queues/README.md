# Queues

A queue is FIFO: things go in at one end and come out the other, in order. On a
microcontroller its most important job is decoupling two pieces of code that run
at different rates, and the classic case is an interrupt that must finish fast
handing work to a main loop that can take its time. This module builds the queue
three ways and, more usefully, shows what makes the ISR-to-main-loop version
actually safe.

## The idea

The naive version is a linear queue: a fixed array with a `front` and a `rear`
index that only ever move forward. `linear_queue.c` is that, buffering UART
bytes from the interrupt.

```c
uart_rx_queue.buffer[uart_rx_queue.rear] = data;
uart_rx_queue.rear++;      /* never wraps */
uart_rx_queue.length++;
```

It works until `rear` reaches the end of the array. From that point `enqueue`
refuses forever, even if every byte has been consumed and the buffer is empty,
because the space behind `front` is never reused. That is not a small
inefficiency, it is the queue dying after a fixed number of bytes.

The circular queue fixes it with one operator. The indices wrap with modulo, so
the array is reused end to end and the queue runs forever.

```c
/* enqueue */
uart_rx_queue.buffer[uart_rx_queue.tail] = data;
uart_rx_queue.tail = (uart_rx_queue.tail + 1) % QUEUE_SIZE;

/* dequeue */
*data = uart_rx_queue.buffer[uart_rx_queue.head];
uart_rx_queue.head = (uart_rx_queue.head + 1) % QUEUE_SIZE;
```

Empty is `head == tail`. Full is `(tail + 1) % SIZE == head`, which is why one
slot is deliberately left unused: without it, full and empty would look
identical. Capacity is `SIZE - 1`, and that wasted slot is the price of not
needing a counter, which turns out to matter a lot.

`circular_queue.c` runs three of these at once: a UART receive queue filled by
the interrupt, a command queue the main loop fills from decoded bytes, and an
ADC sample queue. `priority_queue.c` is a different structure with a queue's
interface: a fixed array of tasks kept sorted by priority on insert, so the
highest-priority task always comes out first, which is a miniature of how an
RTOS picks the next task to run.

## The ring buffer between an ISR and the main loop

This is the pattern worth internalizing. The UART interrupt enqueues, the main
loop dequeues, and there is no mutex, no disabled interrupt, no critical
section anywhere. It is still correct, and the reasons are specific.

**Each side owns exactly one index.** The producer (the ISR) writes only `tail`
and reads `head`. The consumer (the main loop) writes only `head` and reads
`tail`. No variable is written by both. That single property is what removes the
need for a lock.

**Index updates are atomic.** The indices are `uint8_t` on a 32-bit core, so
each write is one store instruction that cannot be interrupted halfway. The
reader either sees the old value or the new one, never garbage.

**The indices are `volatile`.** The compiler cannot cache `head` or `tail` in a
register across the loop, so the main loop actually re-reads what the interrupt
wrote instead of spinning on a stale copy.

**Order of operations.** Enqueue writes the data into the buffer *before*
advancing `tail`. If it advanced `tail` first, the consumer could read a slot
the producer had not filled yet. Same on the other side: read the value, then
advance `head`.

Now the ways to break it, because they are how this goes wrong in real code:

- **A shared counter.** Add a `length` field that the producer increments and
  the consumer decrements and the whole argument collapses, because `length++`
  is a read, a modify, and a write. An interrupt landing between the read and
  the write of the main loop's `length--` loses a count permanently.
  `linear_queue.c` does exactly this, and it is the sharper reason to prefer the
  circular form, well beyond the wasted space. Its indices are not `volatile`
  either.
- **More than one producer or one consumer.** The reasoning above is
  single-producer, single-consumer only. Two ISRs enqueuing, or a main loop and
  an ISR both dequeuing, need a real guard.
- **An index wider than the word size**, or a non-power-of-two size handled with
  a read-modify-write instead of a clean store, puts you back in torn-update
  territory.

And the behavior you must still design for: the queue can fill. The ISR's
`enqueue` returns false and the byte is dropped. Silence is not an option here,
because dropping UART bytes silently is how a protocol desynchronizes and stays
broken; either size the buffer for the worst-case burst, or count the drops and
surface them.

## When to use it (and when not to)

A ring buffer is the default for any producer-consumer stream on an MCU: UART
and SPI receive, ADC sampling, event and command queues, anything where an
interrupt must hand off and get out. It is fixed size, so no allocation, no
fragmentation, and constant-time enqueue and dequeue, which is what a real-time
path needs.

| Structure | Reuses memory | Deterministic | Good for |
| --- | --- | --- | --- |
| Linear queue | No, dies at the end | Yes | Little, mostly a teaching step |
| Circular queue | Yes | Yes | Streaming, ISR to main loop |
| Priority queue | Yes | Insert is O(n) | Ordering by urgency, not arrival |
| Heap-backed queue | Yes | No | Variable-size items, off the MCU path |

It is the wrong tool when order is not what you need. If items must come out by
urgency rather than arrival, that is the priority queue, and its insert shifts
elements, so it is O(n) and not free. If the items are variable-sized buffers
rather than fixed values, hand out blocks from [pools](../pools/) and queue the
pointers. If you were reaching for a growing queue of nodes, the honest
comparison is in [linked](../linked/), and it usually ends here. The fixed-size
argument itself comes from [memory](../memory/).

Two things in this code, noted rather than fixed: `adc_data_queue.buffer` is
`uint8_t[64]` while `enqueue_adc` takes a `uint32_t` and `dequeue_adc` returns
one, so ADC samples are truncated to 8 bits on the way in. And `linear_queue.c`
has the shared `length` counter described above, non-volatile indices, and the
permanent stall once `rear` reaches the end.

## Build and run

STM32F411 (black pill). The Makefile builds `app/Src/main.c`, which this module
does not ship, so pick a demo and make it `main.c` first (copy or rename
`circular_queue.c`, `linear_queue.c`, or `priority_queue.c`). Then `make` builds
`Build/flash.elf` and `Build/flash.bin`, and `make load` flashes it through
OpenOCD with a J-Link over SWD. On UART2 at 115200 the circular demo takes `1`,
`2`, and `3` to turn the LED on, off, and print queued ADC values; the linear
demo echoes each processed byte; the priority demo runs three tasks in priority
order at startup.

## Files

- [app/Src/linear_queue.c](app/Src/linear_queue.c): the non-wrapping queue, kept
  as the illustration of why wrapping matters and why a shared counter is unsafe.
- [app/Src/circular_queue.c](app/Src/circular_queue.c): three ring buffers, UART
  receive filled from the ISR, commands, and ADC samples.
- [app/Src/priority_queue.c](app/Src/priority_queue.c): a fixed task array kept
  sorted by priority on insert, executed highest priority first.
