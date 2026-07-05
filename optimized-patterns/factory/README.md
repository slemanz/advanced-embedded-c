# Factory Pattern

- The Factory Method design pattern defines an interface for
creating objects but delegates the instantiation to subclasses
(or derived modules in C).

- This allows a system to dynamically select implementations
(e.g., chosing I2C or SPI for sensor communication) without
hardcoding dependencies.

- In embedded systems, hardware peripherals often share abstract
functionalities (e.g., sending/receiving data) but differ in
implementation. For example:
    - A temperature sensor could use I2C or SPI.
    - A display might use SPI or 8-bit parallel interfaces.
    
_Hardcoding protocol selection leads to inflexible, tightly coupled
code_

The factory method solves this by

- Letting the application choose the protocol at runtime.
- Isolating protocol-specific code for easier maintenance.

### Key Goals

- **Decouple** object creation from usage.

- **Centralize** decision-making for implementation selection.

- **Simplify** adding new implementations (e.g., UART, CAN).

### Implementation

**Step 1:** Define the Abstract Product

- Create a struct representing the communication protocol interface.

```C
typedef struct{
    void (*init)(void);
    void (*send)(uint8_t *data, uint16_t len);
    void (*receive)(uint8_t *data, uint16_t len);
} CommProtocol;
```

**Step 2:** Implement concrete products

- Define I2C.

```C
static void i2c_init(void);
static void i2c_send(uint8_t *data, uint16_t len);
static void i2c_receive(uint8_t *data, uint16_t len);

CommProtocol I2C_Protocol = {
    .init = i2c_init,
    .send = i2c_send,
    .receive = i2c_receive
}
```

**Step 3:** Create the factory

Write a factory function that returns the appropriate protocol based
on input (e.g., a configuration flag).

```C
CommProtocol *CommProtocol_Factory(ProtocolType type)
{
    switch(type)
    {
        case PROTOCOL_I2C: return &I2C_Protocol;
        case PROTOCOL_SPI: return &SPI_Protocol;
        default: return NULL;
    }
}
```

### Example: Dynamic Protocol Selection

**Scenario:** a system reads from a sensor that supports both I2C
and SPI. The protocol is selected at startup based on a hardware pin
configuration EEPROM.

```C
void main(){
    // 1. detect protocol (e.g read GPIO pin)
    ProtocolType type = protocol_detect();

    // 2. Factory creates the protocol instance
    CommProtocol *protocol = CommProtocol_Factory(type);
    if(!protocol) error_handler();

    // 3. use abstract interface
    protocol->init();
    uint8_t data[] = {0x01, 0x02};
    protocol->send(data, 2);
}
```

### When to use

- System supporting multiple communication protocols.
- Code targeting different hardware variants (e.g. Product families).
- Applications requiring runtime reconfiguration.

### Why to use

1. Abstraction: Decouples object creation from its implementation. Simplifies
hardware interaction by providing a uniform interface.

2. Code Reusability: allows the same factory function to create multiple
object types with minimal changes. Encourages modularity, reducing duplication.

3. Scability: new objects (e.g., additional communication protocols or peripherals)
can be added with minimal impact on existing code.

4. Improved Maintenence: Centrelized object creation makes it easier to modify
or extend initialization logic.

5. Resource Management: In embedded systems, resouces like memory, CPU cycles,
and peripherals are scarce. Factories can manage these efficiently by reusing
or dynamically allocating resources.

## Code

**[main.c](app/Src/main.c)**

**[comm_interface.h](app/Inc/comm_interface.h)**

- **[protocol_factory.c](app/Src/protocol_factory.c)**
- **[i2c_protocol.c](app/Src/i2c_protocol.c)**
- **[spi_protocol.c](app/Src/spi_protocol.c)**
- **[uart_protocol.c](app/Src/uart_protocol.c)**
