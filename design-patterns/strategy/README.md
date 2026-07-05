# Strategy Pattern

## Abstract

Strategy is a behavioral design pattern that lets you define a family of algorithms,
put each of them into a separate class, and make their objects interchangeable.

## Problem

In software development, especially in scenarios requiring dynamic algorithm selection,
you often face the challenge of tightly coupling algorithms within client code. This
leads to difficulties in maintaining and extending the system. For instance, if a
particular algorithm needs to be replaced, it may require extensive changes across the
codebase. The Strategy Pattern addresses these issues by encapsulating algorithms into
separate classes, allowing clients to switch algorithms seamlessly at runtime without
modifying the original code.

## Pattern Structure

**Context:** This class maintains a reference to the Strategy object and is typically
responsible for executing the algorithm defined by the Strategy.

**Strategy Interface:** This provides a common interface for all concrete strategies. It
declares a method for the algorithm that will be implemented by specific strategy classes.

**Concrete Strategies:** These are classes that implement the Strategy interface, each
providing a specific implementation of the algorithm.

## Implementation Example

**[main.c](app/Src/main.c)**

- **[gpioStrategy.h](app/Inc/gpioStrategy.h)**
- **[gpioDevices.h](app/Inc/gpioDevices.h)**
- **[gpioDevices.c](app/Src/gpioDevices.c)**
- **[device.h](app/Inc/device.h)**
- **[device.c](app/Src/device.c)**



