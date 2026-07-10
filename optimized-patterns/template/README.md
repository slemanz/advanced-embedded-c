# Template

The pattern modules in this section run on real hardware, so each one needs
drivers, a linker script, startup code and a Makefile before the pattern
itself shows up. This folder is that common base, kept as a ready-to-build
STM32F411 project: copy it, rename it after the pattern and write only the
pattern code in `app/`.

## What comes preconfigured

- `drivers/`: register-level drivers for the F411 (GPIO, UART, SysTick, ADC,
  I2C, SPI, FPU) plus the `stm32f411xx.h` register map.
- `bsp/`: board support for the LED and the user button on top of the
  drivers.
- `linkers/`: `STM32F411xC.ld`, `startup.c` with the vector table, and
  `syscalls.c` retargeting `printf` to UART2.
- `Makefile`: hard-float Cortex-M4 flags, builds everything from source into
  `app/Build/final.elf`, a `load` target that flashes through OpenOCD with a
  J-Link probe, and a `debug` target that leaves OpenOCD running for GDB.
- `app/`: a demo `main.c` that blinks the LED and prints a float division,
  which doubles as a check that the FPU and `-u _printf_float` are wired
  correctly.

All the pattern modules in this section share this same skeleton, so once you
know this folder you know the layout of every one of them.

## Build and run

```
make        # builds app/Build/final.elf and flash.bin
make load   # flashes via OpenOCD (J-Link over SWD)
make debug  # starts OpenOCD and waits for a GDB connection
make clean
```

Open a serial terminal on UART2 at 115200 to see the demo output.
