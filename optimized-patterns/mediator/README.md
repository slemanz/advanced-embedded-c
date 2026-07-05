# Mediator Pattern

The mediator pattern is a behavioral design pattern that centralizes
complex communications and control logic between releted objects.

In embedded systems, where multiple hardware components and software
modules often need to interact with each other, the Mediator Pattern
offers a way to decouple these interactions by introducing a central
controller.

This **controller**, or **mediator**, manages communication, coordination,
and data exchange between modules, reducing direct dependencies and
simplifying system maintenance.

### Core concepts

1. **Mediator Interface**

    - An interface that defines methods for communication between colleague
    objects.
    - Ensures that all communication follows a well-defined protocol. In
    embedded systems, this might involve functions to dispatch events, relay
    sensor data, or coordinate peripheral actions.

2. **Concrete Mediator**

   - A module that implements the mediator interface and encapsulates how
    colleague objects interact
   - Centralizes control logic and interactions between components. It handles
    communication between multiple subsystems, such as sensor data processing,
    actuator control, and system status updates.

3. **Colleague Objects**

    - The individual components or modules that interact with each other through
    the mediator.
   - They perform their own tasks but delegate interaction and coordination to the
    mediator, thereby reducing coupling. In embedded systems, colleagues could be
    various drivers (UART, ADC, GPIO) or modules (communication, power management,
    and control loops).

### Implementing 

- In an embedded system, the mediator pattern is often implemented as a central 
event dispatcher or control hub.
- Consider a system where multiple peripherals such as sensors, communication interfaces,
and actuators interact to perform coordinated tasks.

1. Define the mediator Interface: create an interface (in C, typically a set of function
pointers) that declares how messages and events are passed between modules.

2. Define the colleague objects: colleague objects (modules) use the mediator to
communicate. For example, a sensor and an actuator may be defined.

3. Implement concrete mediator: the concrete mediator implements the logic for routing
events between colleague objects. It maintains references to various modules.

4. Implement colleague methods: implement the sensor and actuator functions that use
the mediator for communication.

### Challenges and Considerations

**Potential Drawbacks**

- Single Point of Failure: The mediator becomes a central component; if it fails,
the entire communication chain can be disrupted.
- Complexity in Large Systems: As the number of modules increases, the mediator's logic can
become complex and harder to maintain.
- Performance Overhead: Introducing an extra layer for communication may incur slight overhead,
which must be managed carefully in time-critical applications.

### Applications

Home Automation: The Mediator Pattern is ideal for home automation systems where multiple 
devices (lights, thermostats, security systems) need to coordinate their behavior.

Industrial Control Systems: In industrial settings, the Mediator Pattern can manage interactions
between sensors, actuators, and controllers.

Communication Protocols: The Mediator Pattern can simplify the implementation of communication
protocols like UART, SPI, or I2C by centralizing message routing.

## Code

**[main.c](app/Src/main.c)**

Inc:

- **[embedded_system.h](app/Inc/embedded_system.h)**
- **[mediator.h](app/Inc/mediator.h)**
- **[actuator.h](app/Inc/actuator.h)**
- **[sensor.h](app/Inc/sensor.h)**

Src:

- **[concrete_mediator.c](app/Src/concrete_mediator.c)**
- **[actuator.c](app/Src/actuator.c)**
- **[sensor.c](app/Src/sensor.c)**