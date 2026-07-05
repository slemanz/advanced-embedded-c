# Builder Design Pattern

- The builder design pattern separates the construction of a complex
object from its representation, enabling the creation of different
configurations through the same construction process.

- In embedded systems, this pattern is particularly useful for initializing
hardware peripherals, configuring communication protocols, or building
layered data structures while maintaining flexibility and reducing coupling.

### Components

1. **Builder Interface:** defines the methods for setting up different
parts of the product (for example, configuration parameters). Each method
returns a builder instance to allow method chaining.

2. **Concrete Builder:** implements the builder interface for a specific
product. For example, a UART Builder might provide methods to set the
baudrate, word length, parity, etc. and then produce a fully configured
UART driver object.

3. **Product:** represents the final assembled object. In our example,
the product could be a structure representing a peripheral driver (such
as UART configuration structure).

4. **Director:** This is optional. It encapsulate a specific construction
process by invoking builder methods in a predefined order. In many embedded
systems, the client code itself acts as the director, directly calling the
builder's methods.

### Key goals

- Decouple configuration logic from hardware implementation.
- Simplify the creation of objects with many parameters or initialization steps.
- Reuse construction processes across multiple hardware variants.

## Code

**[main.c](app/Src/main.c)**

- **[driver_uart.h](drivers/Inc/driver_uart.h)**
- **[driver_uart.c](drivers/Src/driver_uart.c)**