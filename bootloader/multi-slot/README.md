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
