# Abstract Data Type (ADT)

An Abstract Data Type defines a data structure by its **behavior**, not by its internal representation. It specifies what operations exist and what they do, but completely hides how the data is stored in memory and how the operations are implemented.

> ADT tells you *what* you can do with the data. It does not tell you *how* it is done internally.

The key benefit is **encapsulation**: the user of the ADT only sees a clean interface and cannot accidentally depend on internal details. This makes it safe to change the implementation later without breaking any code that uses it.

## The Opaque Pointer Technique in C

C does not have classes, but you can achieve the same encapsulation using a forward-declared struct combined with an opaque pointer.

The trick: declare a pointer to a struct in the header file, but define the struct itself only in the source file. The compiler knows the type exists, but the caller never sees its fields.

**In the header file (`device.h`):**

```c
typedef struct Device* DevicePtr;
```

This says "there is a type called `DevicePtr` that is a pointer to a `Device` struct." Any caller can hold and pass a `DevicePtr`, but cannot access its fields because the struct definition is hidden from them.

**In the source file (`device.c`):**

```c
struct Device {
    const char *name;
    Address address;
    deviceID_t uuid;
};
```

The struct fields are only visible inside `device.c`. Any other file that includes `device.h` can use `DevicePtr` but cannot read or write the fields directly. This is enforced by the compiler.

## Summary

| What the caller sees | What the caller cannot see |
|---|---|
| The `DevicePtr` type | The fields inside `Device` |
| The public functions in `device.h` | How those functions work internally |

## When to use it (and when not to)

The encapsulation is not free, and on a microcontroller the costs are worth
naming.

Because the caller only ever holds a pointer, the struct cannot be allocated
by the caller: the size is unknown outside `device.c`. Something has to
provide the memory, and the usual answer is the heap, which is what this demo
does (`device_create` calls `calloc`, `device_destroy` calls `free`). That
brings fragmentation risk and nondeterministic allocation timing into a
system that may not tolerate either. The way out is a static pool of
instances inside the source file, with `device_create` handing out one of
them: encapsulation stays, the heap goes away, at the cost of a fixed
maximum.

Every field access also becomes a pointer dereference through a function
call, so the compiler cannot inline what it cannot see across translation
units. For an LED toggled a few times a second this is irrelevant. For a
struct touched inside a tight ISR, the indirection is a real cost to
measure.

Use it when the type has genuine invariants worth protecting and several
callers, and when the implementation is likely to change behind them. Skip it
for a struct of three plain fields that one module owns: an opaque pointer
there buys nothing and costs an allocation and a call.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The demo creates two devices (the LED on
PA5 and the button on PC13) through the same interface, and prints their
state to UART2 at 115200.

## Files

- [app/Inc/device.h](app/Inc/device.h): the opaque type and the public
  operations, all the caller ever sees.
- [app/Src/device.c](app/Src/device.c): the hidden struct and the
  implementation.
- [app/Src/main.c](app/Src/main.c): the demo using the devices.
