# Bootloader v1

The first working bootloader of this section: the minimum code needed to have
one program hand the CPU to another on the STM32F411. Everything the
[multi-slot](../multi-slot/) system does grew out of what this version does
and what it lacks.

## What it does

The flash is split in two: the bootloader owns the first 32 KB
(`0x08000000`, `STM32F411xC_BOOT.ld`) and the application starts right after
(`0x08008000`, `STM32F411xC.ld`). After reset the bootloader blinks the LED
for 5 seconds and then jumps: it reads the first word of the application slot
to check the slot is not erased (`0xFFFFFFFF`), takes the reset handler from
the second word, casts it to a function pointer and calls it. The application
relocates `SCB->VTOR` to its own base as its first action.

The packaging trick is the same one multi-slot uses later: the application
embeds the padded `bootloader.bin` at the start of its own image through an
`.incbin` in [bootloader.S](app1/Src/bootloader.S), so flashing the app image
programs both programs in one step.

`app1/` and `app2/` are two copies of the same blinky application. The point
of having two is proving that the bootloader does not care which app it
boots: build either one and the jump works the same.

## Limitations, and what multi-slot solves

- There is no way to interact: the bootloader always jumps after the timeout.
  Multi-slot adds the button check and the UART menu.
- There is a single application slot and no recovery: if the slot is empty or
  broken, the bootloader just prints an error and sits there. Multi-slot adds
  the factory app, a known-good image in its own sector that you can always
  boot.
- The 32 KB reserved for the bootloader is generous. Multi-slot tightens the
  regions to one 16 KB flash sector each.

## Build and run

Build the bootloader first (`make` in `bootloader/`, the pad script runs
automatically), then one of the apps (`make` in `app1/` or `app2/`). Flash
the app image with `make load` (OpenOCD, J-Link over SWD) and open a serial
terminal on UART2 at 115200: you should see `Init bootloader...`, 5 seconds
of fast blinking and then the jump into the app.

## Files

- [bootloader/Src/bootloader.c](bootloader/Src/bootloader.c): timeout, slot
  check and jump.
- [app1/Src/bootloader.S](app1/Src/bootloader.S): embeds the bootloader
  binary into the app image.
- [linkers/STM32F411xC_BOOT.ld](linkers/STM32F411xC_BOOT.ld) and
  [linkers/STM32F411xC.ld](linkers/STM32F411xC.ld): the two halves of the
  flash split.
