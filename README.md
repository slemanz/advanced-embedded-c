# Advanced Embedded C

A collection of independent mini repositories about advanced embedded C,
grouped in one place to keep my GitHub tidy. I wrote it for my future self:
each section is a refresher on a topic I already worked through, built around
small projects that compile and run instead of theory alone.

## Sections

1. **[Design Patterns](design-patterns/)**: classic patterns in clean C, one
   buildable project each, from ADT to publisher-subscriber and state machines.
2. **[Optimized Patterns](optimized-patterns/)**: the same idea revisited under
   embedded constraints such as memory cost and determinism.
3. **[Data Structures](data-structures/)**: queues, pools, linked structures
   and bit packing for constrained targets.
4. **[Build Systems](build-systems/)**: what happens between source and flash:
   make, linker scripts, startup code, newlib, assembly and CMSIS.
5. **[Bootloader](bootloader/)**: from a minimal bootloader to a multi-slot
   design with a factory fallback image.
6. **[TDD](tdd/)**: notes on test-driven development for embedded, expanded in
   its own repository (link below).

## Hardware and toolchain

Every subfolder is a self-contained project with its own Makefile, linker
script and startup code, so each one builds on its own. Most projects target
the STM32F411 (Cortex-M4), including the whole bootloader section. The design
patterns section runs on the STM32G0B1 (Cortex-M0+). The boards I actually
keep on my desk are the F411 and the F401.

Everything builds with the arm-none-eabi-gcc toolchain. Flashing and debugging
go through OpenOCD.

## Related repositories

- [safety-critical-embedded](https://github.com/slemanz/safety-critical-embedded):
  safety-critical development practices and MISRA notes.
- [unity-embedded-tdd](https://github.com/slemanz/unity-embedded-tdd): the full
  TDD study repo, with Unity and test doubles.

## Planned

- Fault handling and diagnostics on Cortex-M.
