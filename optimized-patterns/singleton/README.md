# Singleton Pattern

- The singleton Pattern is a creational design pattern that ensures
a class or module has only one instance throughout the application.

- It abstract the complexities of initialization and provides a
streamlined mechanism to create objects dynamically or statically.

- In embedded systems, the singleton pattern is especially useful
for managing shared hardware resources, such as UART, drivers, clocks,
timers, and other communication modules, where having multiple instances
could lead to conflicts or resource overuse.

### Why use?

- **Resource Management:** Embedded systems oftem have limited resources
(memory, peripherals). Singleton ensures efficient management by preventing
duplicate instances of a resource.

- **Consistency:** certain peripherals, like UART or SPI, must operate
consistenly. Singleton provides a single, consistent interface for interaction.

- **Global Access:** singleton offers a straighforward way to access shared
resources across different modules without passing pointers or maintaining
external references.

- **Thread-Safety:** in multi-threaded enviroments, singleton ensures
synchronized access to critical resources.

## Code

- **[main.c](app/Src/main.c)**
- **[driver_uart.h](drivers/Inc/driver_uart.h)**
- **[driver_uart.c](drivers/Src/driver_uart.c)**