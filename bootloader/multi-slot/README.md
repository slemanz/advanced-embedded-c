# Multi Slot Bootloader System

A complete boot chain for the STM32F411. A small bootloader runs first and
decides which program gets the CPU: the main application, which is the default,
or a factory app that stays in flash as a permanent fallback. The three
programs are built separately, each with its own linker script, but they ship
as one merged flash image, so a single flash operation programs the whole
system.

## Memory map

The F411 flash starts with 16 KB sectors, and each program owns one region:

| Region      | Start address | Size             | Linker script            |
|-------------|---------------|------------------|--------------------------|
| Bootloader  | `0x08000000`  | 16 KB (sector 0) | `STM32F411xC_BOOT.ld`    |
| Factory app | `0x08004000`  | 16 KB (sector 1) | `STM32F411xC_FACTORY.ld` |
| Application | `0x08008000`  | rest of flash    | `STM32F411xC.ld`         |

All three share the same SRAM region (128 KB at `0x20000000`), which is fine
because only one program runs at a time and each one sets up its own stack,
`.data` and `.bss` from scratch.

These addresses appear twice on purpose: in the linker scripts, which place
each binary, and in `bootloader/Inc/config.h` (`SECTOR1_BASE_ADDRESS`,
`SECTOR2_BASE_ADDRESS`), which tells the bootloader where to jump. If one side
changes, the other must follow.

## Boot flow

After reset the bootloader configures UART2, SysTick and the board LED, then
opens a window of about 5 seconds before booting the default application. The
LED blinks fast (100 ms) while the window is open.

```
reset
  |
  v
bootloader @ 0x08000000
  |
  |-- button pressed during the window?
  |     yes -> menu over UART2:
  |             '1' -> jump to application (0x08008000)
  |             'F' -> jump to factory app (0x08004000)
  |
  '-- no input after ~4.7 s
        -> jump to application (0x08008000)
             |
             '-- slot invalid? print error and stay in the
                 bootloader, LED slows down to 500 ms,
                 the button menu remains available
```

The factory app is not entered automatically: it exists as a recovery path you
select by hand. If the application slot fails validation, the bootloader keeps
running instead of guessing, and you use the menu to boot the factory app or
reflash the board.

### How a slot is considered valid

Before jumping, `jmp_to_app()` in `bootloader/Src/config.c` reads the first
word of the target slot, which by Cortex-M convention holds the initial stack
pointer. Two checks are available, selected by a `#define` in
`bootloader/Inc/config.h`:

- `MEM_CHECKK_V2` (the active one): the slot is valid if the word is not
  `0xFFFFFFFF`, since erased flash reads as all ones.
- `MEM_CHECKK_V1`: masks the word and accepts it only if it looks like an
  address inside SRAM, a stricter test of the same idea.

### The jump itself

A valid slot starts with two words: the initial stack pointer and the address
of the reset handler. The bootloader reads the second word, casts it to a
function pointer and calls it, which is all a Cortex-M needs to start another
program. In the timeout path interrupts are disabled before the jump. One
known gap, marked with a TODO in `config.c`: the MSP is not reloaded from the
slot's first word, so the application inherits the stack position left by the
bootloader. It works because both use the same SRAM and the apps barely touch
the stack before `main`, but a strict bootloader would set the MSP first.

On the other side, the first thing each application does in `main()` is
relocate the vector table: `SCB->VTOR` gets the slot base (`0x4000` offset for
the factory app, `0x8000` for the application). Without this, interrupts would
still be served by the bootloader's table at `0x08000000`.

## How the merged image works

The application is the piece that glues everything together. Its linker script
starts at `0x08000000` and reserves the first two regions:

1. `pad_bootloader.py` and `pad_factory.py` pad `bootloader.bin` and
   `factory.bin` with `0xFF` up to exactly 16 KB (`0x4000`) each.
2. `app/Src/merged.S` pulls both padded binaries in with `.incbin`, into the
   sections `.bootloader_section` and `.factory_section`.
3. The app linker script places these two sections first, so the application's
   own vector table lands exactly at `0x08008000`, where the bootloader
   expects it.

The result is a single `flash.bin` that contains bootloader, factory app and
application at their final addresses.

## Project structure

```
multi-slot/
|-- bootloader/    program in sector 0: boot window, menu, slot check, jump
|-- factory-app/   recovery application, lives in sector 1
|-- app/           main application, sector 2, also builds the merged image
|-- drivers/       register-level peripheral drivers (GPIO, UART, SysTick, ...)
|-- bsp/           board support on top of the drivers: led, button, simple-timer
|-- linkers/       the three .ld scripts plus shared startup.c and syscalls.c
`-- workspaces/    one VS Code workspace per program
```

The three programs (`bootloader/`, `factory-app/`, `app/`) have the same
shape: an `Inc/` and `Src/` pair with the code that is unique to them, and a
Makefile that compiles the shared folders directly from source. There is no
prebuilt library: each program compiles `drivers/`, `bsp/`, `linkers/startup.c`
and `linkers/syscalls.c` on its own, against its own linker script. That keeps
the three builds independent while guaranteeing they all use the same driver
code.

The Makefiles of the bootloader and the factory app call their pad script as
the last build step, so `bootloader.bin` and `factory.bin` always come out
slot-sized. The app Makefile consumes those two binaries through `merged.S`,
which is why the app must be built last.

`workspaces/` holds one `.code-workspace` per program. Each one opens the
program folder together with `bsp/`, `drivers/` and `linkers/`, with the
include paths already set, so IntelliSense resolves everything while you work
on one program at a time.
