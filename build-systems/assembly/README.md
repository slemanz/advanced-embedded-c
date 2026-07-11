# Assembly

A complete blinky written in ARM assembly, down to the register setup. The
point is not to advocate writing firmware this way, but to see exactly what
the C compiler generates for you, and to keep the muscle for the few cases
where assembly is still the only option.

## The idea

[main.s](Src/main.s) does everything the usual C blinky does, instruction by
instruction: `.equ` constants stand in for the register `#define`s, and each
register access becomes the explicit read-modify-write that C hides behind
`|=`:

```asm
.equ RCC_AHB1ENR,   RCC_BASE + AHB1ENR_OFFSET
.equ GPIO_EN,       1<<0

LDR     R0, =RCC_AHB1ENR
LDR     R1, [R0]
ORR     R1, #GPIO_EN
STR     R1, [R0]
```

The toggle is an `EOR` on the ODR bit and the delay is a raw `SUBS`/`BNE`
countdown loop. Reading this next to the equivalent C makes the compiler's
job concrete: every `GPIOA->ODR ^= (1 << 5)` you ever wrote was these four
instructions.

The build has an inverted twist: `main` is assembly but the startup stays in
C ([startup.c](Src/startup.c), vector table and `.data`/`.bss` init). Both go
through `arm-none-eabi-gcc`, which assembles `.s` files directly, so the
Makefile treats the two sources the same and links them with `-nostdlib`.

## When to use it (and when not to)

Writing whole programs in assembly stopped making sense long ago: the
compiler schedules Thumb-2 better than hand-written code and costs nothing to
maintain. Assembly is still necessary in the few spots C cannot express:
context switch code in an RTOS (saving and restoring registers directly),
touching special registers like MSP or CONTROL, the entry of a fault handler
that must capture the stacked frame, and cycle-exact bit-banging. The other
reason to keep the skill is passive: reading disassembly is how you debug
hard faults and verify what the optimizer did, even if you never write a
line.

## Build and run

STM32F411 (LED on PA5). `make` builds `Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The map file (`Build/flash.map`) shows
the handful of bytes the whole program takes.

## Files

- [Src/main.s](Src/main.s): the blinky in assembly.
- [Src/startup.c](Src/startup.c): vector table and startup, kept in C.
- [Makefile](Makefile): gcc assembling and linking both with `-nostdlib`.
