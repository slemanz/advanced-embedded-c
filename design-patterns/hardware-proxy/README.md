# Hardware Proxy Pattern

When every client reaches for the hardware directly, the device's details
leak into all of them. Change the bit encoding, move the register, or swap
the connection technology, and every client has to be found and fixed. The
hardware proxy puts one struct between the clients and the device, so that
knowledge lives in exactly one place.

## The idea

There are many clients but a single proxy per device. The proxy owns the
address and the encoding, and exposes operations in the vocabulary of the
device instead of bits:

```c
struct motorProxy{
    uint32_t *motorData;
    volatile uint32_t *motorAddr;
    uint32_t rotaryArmLength;
    const char *name;
};

void motorProxy_writeMotorSpeed(motorProxy *const me, Direction_e direction, uint32_t speed);
Direction_e motorProxy_accessMotorDirection(motorProxy *const me);
```

The interesting half is the pair of private functions the clients never see:
`marshal` packs a readable `motorData` struct (on_off, direction, speed, and
a set of error flags) into the single 32-bit word the device actually wants,
and `unmarshal` does the reverse when reading. That mapping between "what the
datasheet says bit 9 means" and "no power error" is the knowledge the pattern
is protecting. If the device revision moves the speed field, `marshal`
changes and nothing else does.

The demo has two clients over the same proxy, which is the point of the
structure: a dashboard that only reads state, and a controller that writes
speed and direction. Neither knows the encoding.

## When to use it (and when not to)

The proxy pays for itself when the encoding is nontrivial and more than one
client touches the device, and above all when the hardware is expected to
change (a new revision, a different part, a peripheral moved behind a bus).
It is also what makes the device testable: clients talk to the proxy, so a
fake proxy runs them on a host.

The costs: every access becomes a function call plus a marshal or unmarshal
step, so a read that was one register load turns into real work. In a tight
control loop, cache the value or read the register directly. The proxy is
also a place for state to drift out of sync with the device, since it holds
its own copy of what it thinks the hardware contains. And for a device with
one bit and one client, the whole structure is overhead: toggling a GPIO does
not need a proxy.

Note that the demo simulates the device with an allocated word rather than a
real register, which is enough to show the encoding but means the memory
comes from the heap. Real firmware points `motorAddr` at the peripheral and
allocates the proxy statically.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the demo drives two motors through their proxies, printing the encoded word
at each operation next to what the dashboard reads back.

## Files

- [app/Inc/motorProxy.h](app/Inc/motorProxy.h): the proxy struct and the
  public operations.
- [app/Src/motorProxy.c](app/Src/motorProxy.c): the implementation, including
  the private `marshal` and `unmarshal`.
- [app/Inc/motorData.h](app/Inc/motorData.h): the readable form of the device
  state, with the bit ranges it maps to.
- [app/Src/main.c](app/Src/main.c): the two clients.
