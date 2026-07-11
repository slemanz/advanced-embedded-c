# Optimized Design Patterns

This section revisits design patterns under embedded constraints: memory cost,
determinism, and direct interaction with hardware. Some patterns also appear in
[Design Patterns](../design-patterns/), which presents the canonical form and
intent; the versions here focus on what changes when resources are tight.

## What changes under embedded constraints

The canonical pattern descriptions assume a desktop-class environment. On a
microcontroller, a few assumptions break, and every module in this section is
shaped by them:

- **Memory is static.** Dynamic allocation risks fragmentation on a heap
  measured in kilobytes, so instances tend to be static and object creation
  happens at init, not on demand.
- **Timing is part of correctness.** Many targets have real-time deadlines,
  so a pattern that adds unbounded or variable latency in the wrong place is
  a bug, not a style choice.
- **The hardware is right there.** Patterns wrap registers, interrupts and
  peripherals directly, so indirection layers must earn their cost in every
  call path.
- **Deployment is long.** Firmware can run for years without updates, which
  raises the value of structures that isolate change and keep failures
  contained.

Each module states what the pattern costs, so the decision to use it stays
honest.

## Patterns

All modules run on the STM32F411.

1. [Singleton](singleton/): a module guaranteed to have one instance,
   statically allocated.
2. [Builder](builder/): constructing a complex configuration step by step
   through one build process.
3. [Factory](factory/): selecting a communication protocol (UART, SPI or I2C)
   behind a single creation interface.
4. [Hardware Proxy](hw-proxy/): a proxy mediating every GPIO access, adding
   control without exposing registers.
5. [Decorator](decorator/): wrapping an ADC interface with a logger without
   touching the wrapped code.
6. [Mediator](mediator/): a sensor and an actuator coordinated by a central
   mediator instead of talking directly.
7. [Mediator Example](mediator-example/): the applied counterpart, a home
   automation simulation with three devices.
8. [Strategy](strategy/): interchangeable filter algorithms applied to ADC
   readings at runtime.
9. [Observer](observer/): a subject notifying LED and UART observers when its
   state changes.
10. [State](state/): a traffic light where each state is a function pointer
    handler.
11. [State Example](state-example/): the applied counterpart, an
    idle/read/transmit/error machine with each state in its own file.
