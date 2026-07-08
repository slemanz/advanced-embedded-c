# Template

The data structure modules in this section run on real hardware, so each one
needs drivers, a linker script, startup code and a Makefile before the actual
topic even starts. This folder is that common base, kept as a ready-to-build
STM32F411 project: copy it, rename it and write only the data structure.

## What comes preconfigured

- `drivers/`: register-level drivers for the F411 (GPIO, UART, SysTick, ADC,
  I2C, SPI, RTC, FPU, interrupts) plus the `stm32f411xx.h` register map.
- `bsp/`: board support for the LED and the user button on top of the
  drivers.
- `linkers/`: `STM32F411xC.ld`, `startup.c` with the vector table, and
  `syscalls.c` retargeting `printf` to UART2.
- `Makefile`: builds everything from source into `Build/flash.elf` and has a
  `load` target that flashes through OpenOCD with a J-Link probe.
- `app/`: a demo `main.c` that blinks the LED and prints over UART, useful to
  confirm the board is alive before replacing it with real code.

The modules in this section ([queues](../queues/), [pools](../pools/),
[linked](../linked/), [memory](../memory/), [bit-packed](../bit-packed/))
share this same skeleton, so once you know this folder you know the layout of
all of them.

## Build and run

```
make        # builds Build/flash.elf and flash.bin
make load   # flashes via OpenOCD (J-Link over SWD)
make clean
```

Open a serial terminal on UART2 at 115200 to see the demo output.
