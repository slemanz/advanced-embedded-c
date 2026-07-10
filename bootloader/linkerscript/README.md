# Linker Script

By default the linker decides where everything goes: code fills flash from the
bottom, variables fill RAM. A bootloader cannot live with that, because its
whole job is to guarantee that specific things sit at specific addresses. This
module is the smallest example of taking that control back.

## The idea

The linker script carves the memory into named regions and pins sections to
fixed addresses:

```ld
MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =512K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =128K
    CUSTOM_MEMORY (rx) : ORIGIN = 0x800C000, LENGTH = 64K
}
```

On top of the standard sections, the script defines three custom ones:

- `.custom_flash_block`, pinned at `0x08004000` inside FLASH.
- `.custom_ram_block`, pinned at `0x20000100` in SRAM, marked `(NOLOAD)` so
  nothing tries to initialize it at startup.
- `.custom_section`, placed in the `CUSTOM_MEMORY` region carved out of the
  upper flash.

The C side then places things there with an attribute:

```c
#define CUSTOM_FUNC __attribute__((section(".custom_section")))

unsigned char __attribute__((section(".custom_flash_block"))) custom_flash_buff[10];

void CUSTOM_FUNC _led_toggle2(uint32_t dly_ms) { ... }
```

Every custom section is wrapped in `KEEP()`, otherwise the linker's garbage
collection would drop them as unreferenced. The demo also shows `.RamFunc`,
the standard trick of running a function from RAM: the section is placed in
SRAM but loaded from flash, and the startup code copies it over like `.data`.

## Why this is the foundation of the bootloader

Look at the addresses: a buffer pinned at `0x08004000`, code running from a
region carved out of flash. Replace "buffer" with "application image" and this
is exactly the [multi-slot](../multi-slot/) memory map. A bootloader is this
technique applied seriously: one linker script per program, each one owning a
fixed slice of flash, plus a jump between them.

## Build and run

STM32F411. `make` builds `Build/flash.elf`, `make load` flashes it through
OpenOCD with a J-Link probe. The LED blinks from a function placed in
`CUSTOM_MEMORY`, and the map file (`Build/flash.map`) is the interesting
output: search for the custom sections to see where everything landed.

## Files

- [linkers/STM32F411xC.ld](linkers/STM32F411xC.ld): the linker script with
  the custom regions and sections.
- [app/Src/main.c](app/Src/main.c): the attributes placing variables and
  functions into them.
