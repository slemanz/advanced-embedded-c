# Hardware Proxy Pattern

## Abstract

The Hardware Proxy Pattern uses a class (or struct) to encapsulate
all access to a hardware device, regardless of its physical interface.

## Problem

If every client accesses a hardware device directly, problems due to
hardware changes are exacerbated. If the bit enconding, memory address, 
or connection technology changes, then every client must be tracked down
and modified.

## Pattern Structure

There may be many clients but a single Hardware Proxy per device being
controlled. The proxy contains both pubilc functions and private encapsulate
functions and data.

## Implementation Example

**[main.c](app/Src/main.c)**

- **[motor.h](app/Inc/motor.h)**
- **[motorData.h](app/Inc/motorData.h)**
- **[motorProxy.h](app/Inc/motorProxy.h)**
- **[motorProxy.c](app/Src/motorProxy.c)**
