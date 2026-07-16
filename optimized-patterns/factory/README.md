# Factory Pattern

A sensor might talk over UART, I2C, or SPI, and the rest of the code should
not care which. The factory centralizes the one decision of which
implementation to use, hands back a uniform handle, and every caller after
that works through the same interface without a protocol name in sight.

## The idea

The product is a vtable: a struct of function pointers that is the interface
every protocol implements.

```c
typedef struct
{
    void (*init)(void);
    void (*send)(uint8_t *data, uint32_t len);
    void (*receive)(uint8_t *buffer, uint32_t len);
    void (*deinit)(void);
}CommProtocol_t;
```

Each concrete protocol is one `const` instance of that struct, filled with its
own functions. Being `const`, these live in flash, not RAM:

```c
const CommProtocol_t UART_Protocol = {
    .init = uart_init,
    .send = uart_send,
    .receive = NULL,
    .deinit = uart_deinit
};
```

The factory is a `switch` that maps a type to the matching vtable pointer. It
allocates nothing; it just selects one of the three tables that are already in
flash:

```c
CommProtocol_t *CommProtocol_create(CommProtocolType_e type)
{
    switch(type)
    {
        case PROTOCOL_UART: return (CommProtocol_t*)&UART_Protocol;
        case PROTOCOL_SPI:  return (CommProtocol_t*)&SPI_Protocol;
        case PROTOCOL_I2C:  return (CommProtocol_t*)&I2C_Protocol;
        default: return NULL;
    }
}
```

The demo picks a type from `detect_protocol` (standing in for a strap pin or
an EEPROM byte), asks the factory for it, then only ever calls through the
interface: `protocol->init()`, `protocol->send(...)`. The `main` never mentions
UART again.

## Factory versus strategy

This looks almost identical to [strategy](../strategy/), and the machinery is:
both are a vtable of function pointers behind an opaque handle. The difference
is what each is for. Strategy swaps the algorithm on an existing object at
runtime, potentially many times. The factory answers "which implementation do I
build" once, at creation, and centralizes that decision so adding a protocol
touches one switch instead of every call site. Same tool, different question.

## When to use it (and when not to)

It fits when one abstract job has several concrete implementations chosen by
configuration: a comms protocol picked by a strap pin, a display driver picked
by which panel was detected, a sensor family sharing one read interface. The
callers stay closed to the choice, and a new implementation is a new vtable
plus one case in the factory.

The costs are the vtable's costs. Every call is indirect and cannot be inlined,
so this does not belong in a hot path where the call is the work. Nothing
checks a slot before calling it: `UART_Protocol.receive` is `NULL`, and
`protocol->receive(...)` would jump to zero, so the caller has to know which
operations each protocol actually provides. The factory also casts away
`const` when it returns the pointer, so a caller that writes through the handle
is writing into a `const` object in flash, which faults or is silently dropped;
the handle is meant to be read and called, never modified. And all three
vtables are linked in whether or not they are used, so unless the linker
garbage-collects the unreferenced ones the factory costs flash for options you
did not pick. If the protocol is fixed at build time, skip the factory and
reference the one vtable directly; the indirection only pays when the choice is
real and made at runtime.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. With `PROTO_ID` at 0 the demo selects the UART protocol and sends
"Hello from comm protocol!" on UART2 (115200) every five seconds.

## Files

- [app/Inc/comm_interface.h](app/Inc/comm_interface.h): the `CommProtocol_t`
  vtable, the type enum, and the factory declaration.
- [app/Src/protocol_factory.c](app/Src/protocol_factory.c): the factory switch.
- [app/Src/uart_protocol.c](app/Src/uart_protocol.c),
  [app/Src/i2c_protocol.c](app/Src/i2c_protocol.c) and
  [app/Src/spi_protocol.c](app/Src/spi_protocol.c): the three concrete vtables.
- [app/Src/main.c](app/Src/main.c): detect, create, then use through the
  interface.
