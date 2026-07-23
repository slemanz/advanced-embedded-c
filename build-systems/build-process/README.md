# Build Process

Typing `make` hides five separate programs, and when a build fails the error
almost always names one of them. Knowing which stage produced a message is the
difference between fixing it and guessing. This module runs one tiny blinky
through the toolchain by hand and keeps the output of every stage in the folder,
so you can open the file the compiler saw and compare it to the file it wrote.

```
 ┌──────────────┐                    ┌────────────────────┐                 ┌────────────────┐
 | Source files |─── Preprocessor ──>| Preprocessed files | ─── Compiler ──>| Assembly Files |
 |   (.c/.h)    |                    |        (.i)        |                 |      (.s)      |
 └──────────────┘                    └────────────────────┘                 └────────────────┘
                                                                                    |
       ┌────────────────────────────── Assembler ───────────────────────────────────┘
       ↓
 ┌──────────────┐               ┌───────────────────┐               ┌────────────┐
 | Object files |               | Relocatable files |               | Executable |
 |     (.o)     |─── Linker ──> |                   |─── Locator ──>|            |
 └──────────────┘               └───────────────────┘               └────────────┘
```

## The idea

The source here is a bare-metal blink written straight against registers, no
headers at all, which is what makes each stage easy to read.

```c
#define RCC_AHB1ENR  (*(volatile unsigned int *)(RCC_BASE + 0x30))
GPIOA_ODR ^= (1 << 11);
```

**Preprocessing** is pure text. It strips comments, pastes in `#include` files,
and expands macros. Nothing is understood, only substituted. In `main.i` the
macros are gone and what remains is the expression they stood for:

```c
(*(volatile unsigned int *)(0x40020000 + 0x14)) ^= (1 << 11);
```

The `#define` lines are gone too, replaced by blank lines that keep the line
numbering honest, which is why a compiler error can point at the right line of
the original file. Stop here with `-E`. This is where a "undefined macro" or a
missing header shows up, before any C is checked.

**Compiling** turns that C into assembly for the target architecture. `main.s`
is the result, and the peripheral addresses have become literals in a constant
pool at the end of the function:

```
	ldr	r3, .L5+8      @ load the address of GPIOA_ODR
	ldr	r3, [r3]       @ read the register
	eor	r3, r3, #2048  @ toggle bit 11
	str	r3, [r2]       @ write it back
...
	.word	1073872916     @ 0x40020014, GPIOA_ODR
```

That read-modify-write is the `volatile` doing its job: the value is fetched
from the register every pass instead of being kept in a register. Stop here with
`-S`. Syntax and type errors come from this stage.

**Assembling** turns the mnemonics into machine code, producing the object file
`main.o`. This is where the text becomes bytes. In `contents.txt` you can find
those same addresses sitting at the end of `.text`, little-endian:

```
 0040 ...30380240   @ 0x40023830, RCC_AHB1ENR
 0050 00000240 14000240   @ 0x40020000 and 0x40020014
```

**Linking** merges all the object files and libraries into one, resolving the
symbols each of them referenced but did not define. This is where "undefined
reference to ..." comes from, and it means the symbol was declared but no object
file supplied it.

**Locating** assigns real addresses. This is the step that only exists in
embedded work, and the object file shows why. In `header.txt`, every section of
`main.o` has VMA and LMA of zero:

```
Idx Name      Size      VMA       LMA
  0 .text     00000058  00000000  00000000
```

The code exists but has no idea where it lives. The linker script supplies the
memory map of the actual part, flash here, RAM there, and the locator places
each section at a real address to produce the final `.elf`. That is the subject
of [linker-startup](../linker-startup/), including what VMA and LMA mean when
they differ.

## Doing it by hand

Each stage has a flag that stops the process there, which is the whole trick for
inspecting a build.

```
arm-none-eabi-gcc -E -mcpu=cortex-m4 -mthumb main.c -o main.i   # stop after preprocessing
arm-none-eabi-gcc -S -mcpu=cortex-m4 -mthumb main.c -o main.s   # stop after compiling
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb main.c -o main.o   # compile and assemble, no link
```

The output name is only a convention; `-o other_name.o` works the same. Common
flags worth knowing:

| Option | Purpose |
| --- | --- |
| `-c` | Compile and assemble, do not link |
| `-o FILE` | Write output to FILE |
| `-g` | Include debugging information |
| `-Wall` / `-Werror` | Enable all warnings / treat them as errors |
| `-I DIR` | Add DIR to the header search path |
| `--std=STANDARD` | Pick the language standard |
| `-mcpu=NAME` / `-march=NAME` | Target processor / architecture |
| `-mthumb` / `-marm` | Generate Thumb or ARM instructions |

And the tools for looking at what came out:

| Tool | Use |
| --- | --- |
| `nm` | List the symbols in an object file |
| `size` | Section sizes of an object or executable |
| `objdump` | Dump headers, disassembly, or raw section contents |
| `readelf` | Read ELF structure directly |
| `objcopy` | Convert between formats, for example `.elf` to `.bin` |
| `gdb` | Inspect and control running code, and flash it |

The dumps in this folder came from `objdump`: `-x` for headers and symbols,
`-D` to disassemble everything, `-d` for executable sections only, `-s` for raw
section contents.

## Why it is worth knowing

Most days `make` does all of this silently, and that is fine. The stages matter
when something goes wrong or when you need to see what the compiler actually
did. An "undefined reference" is a link error, not a compile error, so the fix
is a missing object file or library, not a missing `#include`. A macro
misbehaving is answered by reading `main.i`. A suspicion that the optimizer
deleted your delay loop or dropped a register read is answered by reading
`main.s`, which is exactly the `volatile` story in [optimized](../optimized/).
A binary that is too big for flash is answered by `size` and the map file.

The formats you meet at the end of it all: ELF (what the debugger and OpenOCD
want, since it carries symbols and section addresses), plus Intel Hex, Motorola
SREC, and plain binary, which are what programmers and bootloaders usually take.
The `objcopy` step in every Makefile here is what makes the `.bin` from the
`.elf`. The Makefile side of the story is in [the-make](../the-make/).

## Files

- [main.c](main.c): the source, a register-level blink with no includes.
- [main.i](main.i): after preprocessing, macros expanded and comments gone.
- [main.s](main.s): the generated assembly, with the peripheral addresses in the
  constant pool.
- [main.o](main.o): the object file, machine code with unassigned addresses.
- [header.txt](header.txt): `objdump -x`, sections with VMA and LMA still zero,
  plus the symbol table.
- [disassembly.txt](disassembly.txt) and
  [disassembly_exec.txt](disassembly_exec.txt): `objdump -D` and `-d`.
- [contents.txt](contents.txt): `objdump -s`, the raw bytes of each section.
