# Hardware Proxy Pattern

- The Hardware Proxy Pattern is a structural design pattern
that acts as an intermediary between software and hardware.

- Offering benefits like access control, logging, caching,
and error handling while maintaining a consistent hardware
abstraction layer.

### What is

- The proxy pattern provides a surrogate or placeholder for
another object, controlling access to it.

- In embedded systems, the hardware proxy pattern is applied
to hardware peripherals to manage access, enforce security policies,
and provide abstraction.

### Structure

**Hardware Interface:**

- This interface declares the methods for hardware operations.

- It defines the contract that both real hardware and hardware
proxy must follow.

**Real Hardware (Concrete Implementation):**

- Implements the actual hardware operations (e.g., writing to
registers).

- For instance, set_pin() might set a bit in a GPIO register.

**Hardware Proxy:**

- Contains a reference (real HW) to a Hardware Interface instance
(typically pointing to a Real Hardware object).

- Maintains an internal list or bitmask (allowed pins) indicating
which parts are permitted for access.

- Its methods first check whether a requested operation on a specific
part(pin) is allowed before fowarding the call to the Real Hardware object.

### Key Goals

- **Decouple application logic** from hardware dependencies.
- **Centralize hardware access** management.
- **Enhance system reliability** through contolled access.
- **Simplify hardware** simulation for testing.

### Why to use

1. Encapsulate direct hardware access: prevents unintended modifications
of registers and peripherals. Abstract low-level hardware details from
application code.

2. Enhance security and access control: restricts unauthorized access to
critical peripherals (GPIOs, flash, ADC and etc). Implement privilege levels
to prevent accidental misuse.

### When to use

- **Safety-critical:** hardware interactions.
- Systems requiring hardware **simulation/mocking**.
- **Shared hardware** resource management.
- **Multi-vendor** hardware support.

### Comparison

| Pattern | Focus | Hardware proxy differentiation |
| --- | --- | --- |
| Adapter   | Interface translation   | Proxy controls access, adapter converts |
| Facade    | Simplified interface    | Proxy adds functionality, facades hides |
| Decorator | Dynamic enhancement     | Proxy manages access, decorator extends |

## Code

**[main.c](app/Src/main.c)**

- **[gpio_proxy.h](app/Inc/gpio_proxy.h)**
- **[gpio_proxy.c](app/Src/gpio_proxy.c)**