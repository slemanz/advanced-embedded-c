# Template

Every project in the bootloader section needs the same base: register-level
drivers, a linker script, startup code and a Makefile. This folder is that
base, kept as a ready-to-build STM32F411 project so a new bootloader
experiment starts from a working board instead of from scratch.

## What comes preconfigured

- `drivers/`: register-level drivers for the F411 (GPIO, UART, SysTick, ADC,
  I2C, SPI, RTC, FPU, interrupts) plus the `stm32f411xx.h` register map.
- `bsp/`: board support for the LED and the user button on top of the
  drivers.
- `linkers/`: `STM32F411xC.ld` using the full flash, `startup.c` with the
  vector table, and `syscalls.c` retargeting `printf` to UART2.
- `Makefile`: builds everything from source into `Build/flash.elf` and has a
  `load` target that flashes through OpenOCD with a J-Link probe.
- `app/`: a demo `main.c` that prints over UART and exercises SysTick, ADC
  and RTC, useful to confirm the board is alive before changing anything.

## How to use it

Copy the folder, rename it after the new experiment and strip the demo code
out of `app/Src/main.c`. The projects in this section grew exactly this way:
[bootloader-v1](../bootloader-v1/) and [multi-slot](../multi-slot/) are this
skeleton plus their own boot logic and linker scripts.

## Build and run

```
make        # builds Build/flash.elf and flash.bin
make load   # flashes via OpenOCD (J-Link over SWD)
make clean
```

Open a serial terminal on UART2 at 115200 to see the demo output.
