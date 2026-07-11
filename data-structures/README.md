# Data Structures

Data structures for firmware, each in a small buildable project on the
STM32F411. The interesting question is never "what is a queue", it is which
structure fits which problem under embedded constraints, so this index is
organized by problem.

## Which structure for which problem

- **Data arrives faster than it is consumed, or crosses an interrupt
  boundary.** [Queues](queues/): linear, circular (the usual choice for ISR
  to main loop handoff) and priority variants, compared in one module.
- **The code needs malloc-like allocation, but fragmentation and
  nondeterministic timing are unacceptable.** [Memory Pools](pools/):
  fixed-size chunks from a static block, allocation and free in constant
  time.
- **Elements come and go in the middle of a sequence, and their count is
  unknown upfront.** [Linked Lists](linked/): nodes chained by pointers,
  demonstrated with a command list and an event simulation.
- **RAM is tight and the data is mostly flags and small fields.**
  [Bit-Packed](bit-packed/): packing state into bits, with a bad/better
  comparison showing what the packing costs and saves.
- **Before any of them: where does memory come from.** [Memory
  Allocations](memory/): static versus dynamic allocation on a
  microcontroller, and why most firmware leans static.

## Background

The MCU context behind these choices (architectures, memory types, Harvard
versus von Neumann, endianness) lives in
[mcu-background/](mcu-background/).

## Template

New modules here start from [template/](template/), the same preconfigured
F411 skeleton used across the section.
