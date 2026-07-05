# Optimised Design Patterns

This section revisits design patterns under embedded constraints: memory cost,
determinism, and direct interaction with hardware. Some patterns also appear in
[Design Patterns](../DESIGN_PATTERNS/), which presents the canonical form and
intent; the versions here focus on what changes when resources are tight.

Design patterns are **reusable solutions** to common problems encountered
in software design.

These patterns are **not specific code implementations but are instead templates**
or blueprints that can be adapted to a wide range of situations.

By offering standardized solutions, they promote **consistency**, enhance
**maintability**, and improve **colaboration** among developers.


## What are Design Patterns?

Design patterns can be thought of as **best practices codified into templates**
that address recurring design challenges in software systems. They:

- Define a standard way of solving a problem.
- Provide a common language among developers to discuss system architecture.
- Serve as a tool to encapsulate an document expertise in system design.

## Key characteristics of Design Pattern

- **Reusable:** patterns are adaptable to different problems and scenarios.
- **Proven:** patterns are derived from tried-and-tested solutions
- **Scalable:** they are applicable across various scales of development, from
small to large projects.

## Differences between Embedded and General Design Patterns

1. **Constraints:** 
    - General software: typically runs on systems with ample recources.
    - Embedded: operatein resource-constrained environments with limited processing
    power, memory and energy.

Impact: embedded design patterns must prioritize efficiency and minimal resource usage.


2. **Real-Time:** 
    - General software: perform is important but often non-critical.
    - Embedded: many applications have strict real-time deadlines
    (e.g., industrial automation, medical devices).

Impact: Patterns must ensure deterministic behavior and low-latency operations. power, memory and energy.


3. **Hardware Interaction:** 
    - General software: focuses on high-level abstractions and rarely interacts directly with hardware.
    - Embedded: require direct hardware interaction, such as configuring registers, handling interrupts, and managing peripherals.

Impact: Patterns must integrate seamlessly with low-level hardware


4. **Memory Management:** 
    - General software: can rely on dynamic memory allocation and garbage collection.
    - Embedded: Often avoid dynamic allocation due to the risk of fragmentation and prefer static or stack-based memory.

Impact: patterns need to be optimized for deterministic memory usage.

5. **Fault Tolarance and Safety:** 
    - General software: may tolerate occasional failures (e.g., restarting a crashed application).
    - Embedded: Often operate in safety-critical domains where failures can have severe consequences.

Impact: Patterns must account for fault tolerance and ensure system reliability.

6. **Lifecycle and deployment:** 
    - General software: frequent updates and patches are common.
    - Embedded: May be deployed for years or decades with minimal updates.

Impact: Patterns must emphasize long-term maintainability and robustness.

## List of design patterns

1. [Singleton Pattern](singleton/)
2. [Builder Pattern](builder/)
3. [Factory Pattern](factory/)
4. [Hardware Proxy Pattern](hw-proxy/)
5. [Decorator Pattern](decorator/)
6. [Mediator Pattern](mediator/)
7. [Mediator Example](mediator-example/)
8. [Strategy Pattern](strategy/)
9. [Observer Pattern](observer/)
10. [State Pattern](state/)
11. [State Example](state-example/)