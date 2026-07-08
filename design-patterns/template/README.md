# Template

Every pattern in this section is a small program that runs on real hardware,
so each module needs drivers, a linker script, startup code and a Makefile
before the pattern itself shows up. This folder is that common base, kept as
a ready-to-build project: copy it, rename it after the pattern and write only
the pattern code in `app/`.

Unlike most of this repository, which targets the STM32F411, this section
runs on the STM32G0B1 (Cortex-M0+), so the drivers and build flags here are
specific to it.

## What comes preconfigured

- `Drivers/`: register-level drivers for the G0B1 (GPIO, UART, SysTick, ADC)
  plus the `stm32g0.h` register map.
- `linkers/`: `STM32G0B1.ld`, `startup.c` with the vector table, and
  `syscalls.c` retargeting `printf` to UART2.
- `Makefile`: Cortex-M0+ flags, builds everything from source into
  `app/Build/flash.elf` and has a `load` target that flashes through OpenOCD
  with an ST-Link probe.
- `app/`: a demo `main.c` that blinks the LED (PA5), watches the user button
  (PC13) and reads the MCU temperature over the ADC, useful to confirm the
  board is alive before replacing it with a pattern.

All the pattern modules in this section share this same skeleton, so once you
know this folder you know the layout of every one of them.

## Build and run

```
make        # builds app/Build/flash.elf and flash.bin
make load   # flashes via OpenOCD (ST-Link)
make clean
```

Open a serial terminal on UART2 at 115200 to see the demo output.
