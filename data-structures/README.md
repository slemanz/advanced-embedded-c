# Advanced Data Structures

### Common Microcontroller Architectures

The architecture of an MCU plays a critical role in determining its
computational power, memory constraints, peripheral support, and suitability for
various embedded applications.

Microcontrollers are typically categorized by their word size, which represents
the width of the data bus, the size of registers, and the fundamental unit of
processing.

- 8-bit MCUs (ATmega328P, PIC16F877A): Consumer electronics, IoT, automotive control
- 16-bit MCUs (MSP430, dsPIC33): Industrial automation, motor control, medical devices
- 32-bit MCUs (ARM Cortex-M, ESP32): Advanced loT, real-time systems, automotive

#### 8-Bit Microcontroller

8-bit MCUs process 8-bit data at a time, meaning their accumulators, registers,
and data buses are 8-bit wide.

These microcontrollers are optimized for cost-effectiveness, low power
consumption, and small memory footprint, making them ideal for applications
where processing power is not the primary concern.

#### 16-Bit Microcontroller

16-bit MCUs are a middle ground between 8-bit and 32-bit architectures. They are
optimized for higher computational performance and better memory management
while still being power-efficient.

- Larger Address Space: Can typically access up to 1 MB of memory without bank-switching.
- Enhanced Computational Power: Supports more complex math operations and DSP
(Digital Signal Processing) functions.
- Wider Data Bus: Improves data transfer rates and efficiency.
- Increased Peripheral Support: Includes real-time clocks, enhanced ADCS, USB
interfaces, and wireless communication modules.

#### 32-Bit Microcontroller

32-bit MCUs offer high computational power, larger address space, and support
for advanced peripherals, making them ideal for real-time embedded applications
that require high-speed data processing.

- Expanded Address Space: Supports up to 4 GB of memory.
- Advanced Instruction Set Architecture: Implements RISC (Reduced Instruction
- Set Computing) architectures such as ARM Cortex-M.
- High Clock Speeds: Operates from 50 MHz to over 600 MHz, suitable for
real-time computing. Integrated Advanced Peripherals: Includes Ethernet, USB,
CAN, and cryptographic accelerators etc.

### Architecural Differences in Data Structures

**Memory Considerations:**

- 8-bit MCUs: Favor fixed-size arrays and bit-packed structures due to limited
RAM.
- 16-bit MCUs: Can handle linked lists and simple hash tables efficiently.
- 32-bit MCUs: Suitable for dynamic memory allocation, binary trees, and
graph-based structures.

**Execution Speed and Computational Constraints:**

- 8-bit MCUs: Require minimalistic data structures to optimize speed (e.g.,
lookup tables).
- 16-bit MCUs: Benefit from efficient stack-based structures for computation.
These MCUs typically have enough resources to use stack operations effectively.
- 32-bit MCUs: Can process floating-point operations and large datasets.

With their enhanced processing capabilities and larger memory space, they are
designed to handle complex calculations and larger data structures efficiently,
which is a significant advantage in applications requiring high precision and
extensive data manipulation

**Key Takeaways:**

- 8-bit MCUs are best for simple, low-power applications with small memory constraints.
- 16-bit MCUs provide a balance between computational efficiency and cost-effectiveness.
- 32-bit MCUs enable advanced applications requiring high-speed processing and large memory.

Data structure selection should align with the processing power and memory
constraints of the chosen MCU.

### Memory Systems in MCUs

Memory is a critical component of microcontroller (MCU) systems, impacting
performance, efficiency, and the types of applications an embedded system can
support.

Unlike general-purpose computing devices, MCUs have constrained memory
resources, making efficient memory management essential.

**Types of Memory:**

Microcontrollers typically employ a mix of volatile and non-volatile memory to
store firmware, runtime data, and configuration parameters.

The three most common types of memory found in MCUS are Static RAM (SRAM), Flash
memory, and Electrically Erasable Programmable Read-Only Memory (EEPROM).

- SRAM (Static Random Access Memory)
    - Volatile: Loses data when power is removed.
    - Fast access: Provides quick read/write speeds, making it suitable for
    stack and heap storage.
    - Limited capacity: Typically ranges from 2 KB to 512 KB in most
    microcontrollers.
    - Storage of runtime variables (local variables, function parameters).
    - Stack memory for function calls and return addresses.
    - Heap allocation for dynamic memory management.
    - Fast read/write operations (single-cycle access).
    - No need for periodic refreshing (unlike DRAM).
    - Ideal for real-time and deterministic operations.

- Flash memory (Program Memory)
    - Non-volatile: Retains data even when power is lost.
    - Slower write speed: Writing/erasing is slower than SRAM.
    - Limited write endurance: Typically 10,000 to 100,000 write cycles before
    degradation.
    - Stores firmware and bootloaders.
    - Often used for non-volatile storage of read-only data.
    - Retains program code after power loss.
    - High storage capacity (compared to SRAM).
    - More cost-effective than SRAM for storing large amounts of data.

- EEPROM (Electrically Erasable Programmable Read-Only Memory)
    - Non-volatile: Retains data after power loss: This characteristic is
    crucial for applications that require data persistence, such as storing
    configuration settings and firmware in embedded systems
    - Byte-level write access: Unlike Flash memory, which typically requires
    data to be written or erased in larger blocks (sectors), EEPROM allows for
    individual bytes to be written or erased independently. This feature makes
    EEPROM suitable for applications that need frequent updates to small amounts
    of data.
    - Lower storage capacity: Typically 128 bytes to 512 KB.  This limitation
    makes EEPROM less suitable for applications requiring large data storage
    - EEPROM generally has a higher number of write cycles compared to Flash
    memory. While Flash memory typically supports 10,000 to 100,000 write cycles
    per block, EEPROM can endure 100,000 to 1,000,000+ write cycles per byte.
    - Storing calibration data, device configurations, and unique IDs.
    - Used in applications requiring occasional updates without frequent reprogramming.

### Architectures

The two main architectures used are Harvard and von Neumann, which differ in how
they separate or unify program and data memory.

**Harvard Architecture**

- **Separate buses** for program memory (Flash) and data memory (SRAM).
- Allows simultaneous instruction fetch and data access, improving execution
speed.
- Higher performance due to parallel data and instruction access.
- Prevents unintended modification of program memory.
- Reduces bus contention, improving real-time performance.
- More complex hardware design due to separate buses.
- Less flexibility in sharing memory between instructions and data.

**Von Neumann Architecture**

- Unified memory for both instructions and data
- Simpler design with a single address bus and data bus
- Simpler hardware implementation, reducing cost.
- More flexibility in memory usage.
- Memory bandwidth limitations can cause bottlenecks.
- Susceptible to self-modifying code errors.

###  Endianess Consideration

Endianness defines how multi-byte data is stored in memory.

**Types of Endianness**

- Little-Endian: Stores the least significant byte (LSB) first. (Example
architectures: Intel x86, ARM Cortex-M.)
- Big-Endian: Stores the most significant byte (MSB) first (Example
architectures: PowerPC, some RISC architectures.)

**Impact on Embedded Systems**

- Cross-platform compatibility: Endianness differences must be accounted for in
network protocols (e.g., TCP/IP).
- Peripheral communication: SPI and I²C devices may expect data in a specific
endian format.
- Data serialization: MCUs interfacing with external memory or cloud services
need consistent endianness.

Example: 

- The Ethernet protocol (TCP/IP) uses big-endian format, requiring little-endian
MCUs (e.g., ARM Cortex-M) to convert values before transmission.


### List of Data Structures

- [Memory Allocations](memory)
- [Bit-Packed](bit-packed/)
- [Linked Lists](linked/)
- [Memory Pools](pools/)
- [Queues](queues/)