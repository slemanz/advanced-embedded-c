# Strategy Pattern

When a client hardcodes the algorithm it uses, replacing that algorithm means
editing the client. Strategy pulls the algorithm out into an interchangeable
unit, so the client keeps one reference and the choice can change at runtime
without touching the code around it.

## The idea

In C the strategy interface is a function pointer type, and this module shows
it at its most stripped down:

```c
typedef void (*gpioStrategy)(int device_number);
```

That is the whole interface. The concrete strategies are just functions with
that signature, one per GPIO port (`gpioADeviceStrategy`,
`gpioBDeviceStrategy`, `gpioCDeviceStrategy`), each driving a pin on its own
port.

The context is a device holding the current strategy behind an opaque pointer
(the same technique as [adt](../adt/)):

```c
struct Device
{
    const char *name;
    gpioStrategy deviceStrategy;
};

void device_set(devicePtr device, int device_num)
{
    device->deviceStrategy(device_num);
}
```

`device_set` never knows which port it drives, it just calls through the
pointer. The demo creates a device with the GPIOA strategy, uses it, then
calls `device_change` to swap in GPIOB and uses it again: the same device,
same call, different hardware, decided at runtime.

The optimized section revisits this pattern with a more realistic case,
interchangeable filters applied to ADC readings:
[optimized-patterns/strategy](../../optimized-patterns/strategy/).

## When to use it (and when not to)

Strategy fits when the choice is genuinely dynamic: an algorithm selected by
configuration, by a runtime measurement, or by which hardware was detected at
boot. It is also how you keep a family of algorithms testable, since each one
is a standalone function with no client attached. Compared to a `switch` over
a mode enum, adding a strategy does not touch existing code.

The costs are worth being clear about. An indirect call through a function
pointer cannot be inlined, and the compiler loses the ability to optimize
across it, so the pattern is a poor fit inside a hot loop or an ISR where the
call is the work. Function pointers also defeat static analysis of the call
graph, which matters in safety-critical code, and they make stack usage
harder to bound. And the flexibility is often unused: if the strategy is
chosen once at init and never changes, a compile-time choice costs nothing at
runtime and keeps the call direct.

Use it when the switching is real. If the algorithm is fixed at build time,
this is indirection with no payoff.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the demo prints which port and pin each strategy drove, before and after the
swap.

## Files

- [app/Inc/gpioStrategy.h](app/Inc/gpioStrategy.h): the strategy interface,
  one function pointer type.
- [app/Src/gpioDevices.c](app/Src/gpioDevices.c): the three concrete
  strategies, one per GPIO port.
- [app/Src/device.c](app/Src/device.c): the context holding and calling the
  current strategy.
- [app/Src/main.c](app/Src/main.c): the demo swapping strategies at runtime.
