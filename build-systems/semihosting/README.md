# Semihosting

Semihosting in ARM Cortex-M microcontrollers is a mechanism that allows
embedded code, running on a target device, to utilize the input/output
(I/O) resources of a host computer (like a PC running a debugger).

Essentially, it enables functions like printf and scanf in your embedded
code to work with the host's console and file system instead of requiring
dedicated I/O peripherals on the target

### Example

Here, the most simple implementation:

- [Linker](Src/linker.ld)
- [Startup](Src/startup.c)
- [main.c](Src/main.c)
- [Makefile](Makefile)