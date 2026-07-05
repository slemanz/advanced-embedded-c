# Build Systems

- There are a number ways to develop the firmware for a particular
microcontroller depending on the resouces provided be the manufacturer.

Example STM32: Hardware Abstraction Layer (HAL), Low Layer APIs (LL),
direct register access (Bare-Metal C) and Assembly.

## Tools of the Trade

**Integrated Development Environment (IDE):**  A single software
application with GUI for developing other software applications.

**Toolchain:** A set of development tools chained together by specific
stages used to develop final software product for a target.

E.g: GNU Toolchain for ARM and ARMCC

## Development Environment

- Editing code: text editor (Notepad++, VIM, or VSCode)
- Building: GNU Toolchain
- Flashing: GNU Toolchain and OpenOCD
- Debugging: GNU Toolchain and OpenOCD

There are two most famous ARM toolchains: GNU toolchain for ARM (Opensource)
and ARMCC (Non-Opensource, provided by Arm Ltd.)

## Cross Compilation

Compiling code using one machine (host) and then running the executable
on another machine (target).

Native compilation: compile code on a machine and run on the same machine.

## Deep Topics

1. **[Build Process](build-process/)**
2. **[Linker and Startup](linker-startup/)**
3. **[Make Build System](the-make/)**
4. **[CMSIS](cmsis/)**
5. **[Assembly](assembly/)**
6. **[Cpp](cpp/)**
7. **[Semihosting](semihosting/)**
8. **[Newlib](newlib/)**
8. **[Optimized](optimized/)**