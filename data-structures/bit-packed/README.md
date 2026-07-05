# Bit-Packed

Bit-packing is a critical optimization technique in embedded systems, where
memory constraints are a primary concern.

Efficient data storage is essential for reducing RAM usage, minimizing flash
storage requirements, and optimizing CPU processing speed.

| Advantage                 | Description |
| --- | --- |
| Memory Optimization       | Reduces RAM/ROM usage by efficiently storing values. |
| Data Compression          | Saves bandwidth in communication protocols (e.g., SPI, I2C). |
| Efficient I/O Storage     | Helps fit more sensor data in limited EEPROM or flash. |
| Faster Processing         | Reduces cache misses and improves CPU efficiency. |
| Low-Power Optimization    | Decreases memory access operations, saving energy. |

- [Bad Example](app/Src/bad.c)

### Memory Saving Analysis

| Field         | Without Bit-Packing (int8)    | With Bit-Packing |
| --- | --- | --- |
| mode (2 bits)  | 1 byte       | 2 bits |
| flag (1 bit)   | 1 byte       | 1 bit  |
| speed (3 bits) | 1 byte       | 3 bits |
| **Total**      | **3 bytes**  | **1 byte** |

### Limitations of Bitfiels

While bitfields offer a simple way to reduce memory consumption, they have
significant limitations:

| Limitation | Description |
| --- | --- |
| Portability Issues            | Bit ordering depends on the compiler and target CPU architecture. |
| Inefficient Bit Manipulation  | Accessing individual bits generates extra CPU instructions. |
| Cannot Take Addresses (&)     | Bitfields cannot be referenced via pointers. |
| Alignment and Padding         | Some compilers add padding between bitfields, causing unpredictable memory sizes. |

### Alternative Approaches to Bit-Packing

- Using Bitwise Operators Instead of Bitfields
- Bitwise operators (&, |, <<, >>) provide more control than bitfields.

**Advantages:**

- Portable across different architectures.
- No compiler-dependent alignment issues.
- Efficient bitwise manipulation with constant-time performance.

**Best Practices:**

1. Prefer Bitwise Operators Over Bitfields
    - Bitwise operations offer consistent behavior across different architectures.
    - Use bitmasks (&, |, <<, >>) for manual bit-packing.
2. Align Data Structures Properly
    - When working with MCU registers, ensure bit alignment matches hardware specifications.
    - Use `__attribute__((packed))` for memory-efficient structures

- [Better Example](app/Src/better.c)
- [GPIO Bit Packing](app/Src/gpio_packed.c)

