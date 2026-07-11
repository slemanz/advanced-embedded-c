# Build Systems

- There are a number of ways to develop the firmware for a particular
microcontroller depending on the resources provided by the manufacturer.

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

1. **[Build Process](build-process/)**: the five steps that turn source into a
   binary image (preprocess, compile, assemble, link, objcopy).
2. **[Linker and Startup](linker-startup/)**: the memory model, the linker
   script, and the startup code that runs before `main`.
3. **[Make Build System](the-make/)**: how a Makefile drives the toolchain,
   from a first target to a reusable pattern.
4. **[CMSIS](cmsis/)**: the vendor-neutral Cortex-M interface standard and what
   it provides on top of bare registers.
5. **[Assembly](assembly/)**: a blinky written in ARM assembly, and when
   assembly is still necessary.
6. **[Cpp](cpp/)**: C++ on bare metal, what changes in the build and which
   language features to avoid.
7. **[Semihosting](semihosting/)**: routing `printf` and file I/O to the host
   through the debugger, no UART needed.
8. **[Newlib](newlib/)**: the embedded C standard library and the syscall stubs
   it expects you to provide.
9. **[Optimized](optimized/)**: reducing code size beyond `-Os`, using a
   printf-retarget blinky as the case study.