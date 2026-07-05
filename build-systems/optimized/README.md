# Generic Code

There are many ways to optimize code size beyond `-Os`, The `-Os`  should be the
last option to reduce code size.

For our simple blinky with printf retarget example: [main.c](app/Src/main.c).

Here are the linker and C flags:

```makefile
CFLAGS  = -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nano.specs $(LINKER) $(MAP_FILE) \
          -u _printf_float -Wl,--print-memory-usage
```

Resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  26.092 B | 256 KB | 9.95% |
| RAM           |   2.232 B |  60 KB | 3.63% |


## Remove Float Print

The first thing that will help a lot is to avoid enabling floating-point support
in `printf`.

Here are the linker and C flags:

```makefile
CFLAGS  = -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nano.specs $(LINKER) $(MAP_FILE) \
          -Wl,--print-memory-usage
```

Resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  11.012 B | 256 KB | 4.20% |
| RAM           |   1.864 B |  60 KB | 3.03% |

## Linker and C flags optimizations

- **`--specs=nosys.specs`**: Links against a “no system” implementation — tells
the standard library to use **empty stubs** for system calls (like `_write`,
`_read`, `_sbrk`) instead of trying to call an OS. Embedded bare-metal targets
don’t have an OS; you provide your own low-level I/O if needed.

- **`-Wl,--gc-sections`**: Garbage-collects unused sections from the final binary.
When combined with `-ffunction-sections` and `-fdata-sections` during compile,
the linker can remove unused functions and data, reducing binary size.

- **`-static`**: Forces **static linking** — no shared libraries. Embedded
firmware must be fully self-contained; no dynamic linking possible.

- **`--specs=nano.specs`**: Links against the **newlib-nano** C library — a
smaller, reduced-feature version of newlib. It is the default if not specified other lib. 
Smaller printf/scanf features (unless linked with `-u _printf_float` to enable float formatting).

- **`-Wl,--start-group ... -Wl,--end-group`**: Groups libraries for
**multiple-pass linking**. In normal linking, if a library earlier in the
command needs symbols from one later, it might fail. Grouping makes the linker
search repeatedly until all symbols are resolved. Is used for circular
dependencies between `libc`, `libm`, etc.

- **`-lc`**: Link against the standard C library (`libc.a`). Standard C
functions like `memcpy`, `strlen`, etc.

- **`-lm`**: Link against the math library (`libm.a`). Provides: `sin`, `cos`,
`sqrt`, `pow`, etc.

Be careful: when using options like `-Wl,--gc-sections`, some sections in the
linker script must be protected with `KEEP`, such as the vector table and other
data arrays used by libc, like the `.init` and `.fini` sections.

See the example in: [Linker with KEEP](linkers/linker.ld)

Here are the linker and C flags:

```makefile
CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS =  $(MACH) -mthumb $(FLOAT) --specs=nosys.specs  $(LINKER) $(MAP_FILE) \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm -Wl,--end-group \
 			-Wl,--print-memory-usage
```

Resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  9.296 B | 256 KB | 3.55% |
| RAM           |  1.704 B |  60 KB | 2.77% |

## Flag -Os

The last option is to use the `-Os` flag, but it’s not highly recommended because
a lot of strange things can start to happen, so you need to have a deep
understanding of the code you’re writing.

```makefile
CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -Os \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS =  $(MACH) -mthumb $(FLOAT) --specs=nosys.specs  $(LINKER) $(MAP_FILE) \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm -Wl,--end-group \
 			-Wl,--print-memory-usage
```

Resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  8.340 B | 256 KB | 3.18% |
| RAM           |  1.704 B |  60 KB | 2.77% |

## Compiler version

Other thing that makes the difference is the compiler version, all the
examples was made with: **arm-none-eabi-gcc (15:10.3-2021.07-4) 10.3.1 20210621 (release)**.

With we compile with the last linker and C flags in a newer version, for example: 
**arm-none-eabi-gcc (Arm GNU Toolchain 12.3.Rel1 (Build arm-12.35)) 12.3.1 20230626**

We will get the following, resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  5.668 B | 256 KB | 2.16% |
| RAM           |  2.016 B |  60 KB | 3.28% |

---

### Great reference

[Demystifying Arm GNU Toolchain Specs: nano and nosys](https://metebalci.com/blog/demystifying-arm-gnu-toolchain-specs-nano-and-nosys/)