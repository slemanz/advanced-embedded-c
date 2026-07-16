# Hardware Proxy Pattern

A proxy stands in front of a real object and controls access to it. This
module uses it as a protection layer over GPIO: every pin operation goes
through a gate that checks a permission mask first and only then forwards the
call to the real driver. Application code cannot touch a pin it was not granted.

## The idea

The real driver is a vtable, the same shape used elsewhere: three function
pointers that actually write the registers.

```c
typedef struct{
    void    (*pin_set)(uint32_t pin);
    void    (*pin_clear)(uint32_t pin);
    uint8_t (*pin_read)(uint32_t pin);
}GPIO_Proxy_t;
```

The proxy wraps that real object and adds the permission mask:

```c
typedef struct{
    GPIO_Proxy_t *real_gpio;
    uint32_t pins_allowed;   /* one bit per permitted pin */
}SecureGPIO_Proxy_t;
```

Each proxy operation is the gate: check the bit, forward on success, refuse
otherwise.

```c
void secure_gpio_set_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin)
{
    if(proxy->pins_allowed & (1 << pin))
        proxy->real_gpio->pin_set(pin);
    else
        printf("Access denied: Pin not allowed\n");
}
```

The demo starts with only pin 5 permitted (`pins_allowed = (1U << 5)`), so
`secure_gpio_set_pin(&secure_gpio, 5)` goes through and the same call on pin 8
is denied. Then `update_allowed_pins` widens the mask to pins 5 and 8 at
runtime, and the pin 8 operations start working. The mask is the whole policy,
and it can change while the program runs.

## Same name, different proxy

[design-patterns/hardware-proxy](../../design-patterns/hardware-proxy/) is also
called a hardware proxy, but it solves a different problem, and reading the
pair together is the point. There the proxy encapsulates a device's physical
interface: it hides the register layout and the marshaling of a motor behind a
clean struct, so the proxy is about hiding *how* the hardware is accessed. Here
the proxy hides nothing about the registers; it wraps a driver that already
exists and controls *whether* a given access is allowed. One is an encapsulation
proxy, the other is a protection proxy. Same word, and the classic proxy pattern
covers both, but they buy different things: abstraction of the interface versus
a gate on access.

## When to use it (and when not to)

The protection form fits when access genuinely must be restricted or audited: a
safety-critical build where application code must not reach certain pins or
peripherals, a shared resource that needs a single checkpoint, or a place where
you want every access logged. The indirection through a vtable also makes the
real driver swappable, so tests can point the proxy at a fake GPIO and check the
logic without hardware. That testability is often the strongest reason to have
the layer at all.

The costs are indirection stacked twice. A plain pin write is `GPIOA->BSRR =
(1U << pin)`; here the same write is a permission-mask test, a call into the
proxy, and a second indirect call through `real_gpio->pin_set`. That is a lot of
overhead for a GPIO toggle, and it does not belong in a hot loop or an ISR where
the pin flip is the work. The vtable itself earns its keep only if the real
implementation is actually swapped (for a mock, or a second backend); with one
real driver it is pure overhead on the target, bought for the sake of the test
build. Note too that only set, clear, and read are gated: the init functions
write `GPIOA` directly and bypass the proxy, so the "nothing touches a pin
without permission" guarantee holds for operation, not for configuration. If
there is no access policy to enforce and no mock to swap in, call the driver
directly.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The output goes to UART2 at 115200, where the demo prints each
allowed operation and each "Access denied" as the permission mask changes.

## Files

- [app/Inc/gpio_proxy.h](app/Inc/gpio_proxy.h): the real-driver vtable and the
  `SecureGPIO_Proxy_t` with its permission mask.
- [app/Src/gpio_proxy.c](app/Src/gpio_proxy.c): the real register writes, the
  real vtable, and the gated proxy functions.
- [app/Src/main.c](app/Src/main.c): the demo exercising allowed and denied
  pins and widening the mask at runtime.
