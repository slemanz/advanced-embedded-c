# MCU Background

Reference notes on microcontroller architecture that used to live in the
section README. Nothing here is specific to one data structure; it is the
context that makes the choices in [data-structures](../) make sense.

## Common Microcontroller Architectures

The architecture of an MCU plays a critical role in determining its
computational power, memory constraints, peripheral support, and suitability
for various embedded applications.

Microcontrollers are typically categorized by their word size, which
represents the width of the data bus, the size of registers, and the
fundamental unit of processing.

- 8-bit MCUs (ATmega328P, PIC16F877A): consumer electronics, IoT, automotive control
- 16-bit MCUs (MSP430, dsPIC33): industrial automation, motor control, medical devices
- 32-bit MCUs (ARM Cortex-M, ESP32): advanced IoT, real-time systems, automotive

### 8-Bit Microcontrollers

8-bit MCUs process 8-bit data at a time, meaning their accumulators,
registers, and data buses are 8 bits wide.

These microcontrollers are optimized for cost-effectiveness, low power
consumption, and small memory footprint, making them ideal for applications
where processing power is not the primary concern.

### 16-Bit Microcontrollers

16-bit MCUs are a middle ground between 8-bit and 32-bit architectures. They
are optimized for higher computational performance and better memory
management while still being power-efficient.

- Larger address space: can typically access up to 1 MB of memory without
  bank-switching.
- Enhanced computational power: supports more complex math operations and DSP
  functions.
- Wider data bus: improves data transfer rates and efficiency.
- Increased peripheral support: real-time clocks, enhanced ADCs, USB
  interfaces, and wireless communication modules.

### 32-Bit Microcontrollers

32-bit MCUs offer high computational power, larger address space, and support
for advanced peripherals, making them ideal for real-time embedded
applications that require high-speed data processing.

- Expanded address space: supports up to 4 GB of memory.
- Advanced instruction set: implements RISC architectures such as ARM
  Cortex-M.
- High clock speeds: operates from 50 MHz to over 600 MHz, suitable for
  real-time computing.
- Integrated advanced peripherals: Ethernet, USB, CAN, cryptographic
  accelerators.

## Architectural Differences in Data Structures

**Memory considerations:**

- 8-bit MCUs: favor fixed-size arrays and bit-packed structures due to
  limited RAM.
- 16-bit MCUs: can handle linked lists and simple hash tables efficiently.
- 32-bit MCUs: suitable for dynamic memory allocation, binary trees, and
  graph-based structures.

**Execution speed and computational constraints:**

- 8-bit MCUs: require minimalistic data structures to optimize speed (e.g.,
  lookup tables).
- 16-bit MCUs: benefit from efficient stack-based structures for computation.
- 32-bit MCUs: can process floating-point operations and large datasets.

**Key takeaways:**

- 8-bit MCUs are best for simple, low-power applications with small memory
  constraints.
- 16-bit MCUs provide a balance between computational efficiency and cost.
- 32-bit MCUs enable advanced applications requiring high-speed processing
  and large memory.

Data structure selection should align with the processing power and memory
constraints of the chosen MCU.

## Memory Systems in MCUs

Unlike general-purpose computing devices, MCUs have constrained memory
resources, making efficient memory management essential. Microcontrollers
typically employ a mix of volatile and non-volatile memory to store firmware,
runtime data, and configuration parameters. The three most common types are
SRAM, flash, and EEPROM.

- SRAM (Static Random Access Memory)
    - Volatile: loses data when power is removed.
    - Fast access: single-cycle read/write, suitable for stack and heap.
    - Limited capacity: typically 2 KB to 512 KB.
    - Holds runtime variables, the stack, and heap allocations.
    - No periodic refreshing needed (unlike DRAM), which keeps access
      deterministic.

- Flash memory (program memory)
    - Non-volatile: retains data when power is lost.
    - Slower writes: writing and erasing are much slower than SRAM, and
      erases happen in blocks.
    - Limited write endurance: typically 10,000 to 100,000 cycles.
    - Stores firmware, bootloaders, and read-only data.
    - High capacity and cheaper per byte than SRAM.

- EEPROM (Electrically Erasable Programmable Read-Only Memory)
    - Non-volatile, with byte-level write access: unlike flash, individual
      bytes can be written or erased independently, which suits frequent
      updates to small amounts of data.
    - Lower capacity: typically 128 bytes to 512 KB.
    - Higher endurance than flash: 100,000 to over 1,000,000 cycles per byte.
    - Typical use: calibration data, device configuration, unique IDs.

## Harvard and von Neumann

The two main memory architectures differ in how they separate or unify
program and data memory.

**Harvard architecture**

- Separate buses for program memory (flash) and data memory (SRAM).
- Allows simultaneous instruction fetch and data access, improving speed and
  real-time behavior.
- Prevents unintended modification of program memory.
- Costs: more complex hardware, less flexibility in sharing memory between
  instructions and data.

**Von Neumann architecture**

- Unified memory and a single bus for instructions and data.
- Simpler and cheaper hardware, more flexible memory usage.
- Costs: the shared bus can bottleneck, and self-modifying code errors become
  possible.

## Endianness

Endianness defines how multi-byte data is stored in memory.

- Little-endian: least significant byte first (Intel x86, ARM Cortex-M).
- Big-endian: most significant byte first (PowerPC, some RISC architectures).

It matters at every boundary where data leaves the MCU: network protocols
(TCP/IP is big-endian, so a Cortex-M converts before transmission), SPI and
I2C devices that expect a specific byte order, and any serialization shared
with external memory or other machines.
