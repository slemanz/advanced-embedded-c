# Singleton Pattern

Some resources have exactly one instance by nature: the UART2 peripheral, the
system clock, an ADC. The singleton makes that "one and only one" explicit in
code, so every caller reaches the same instance and nobody can accidentally
create a second one that fights over the same hardware.

## The idea

The whole pattern here is a function-local `static` and a flag. The instance
lives inside the accessor, so it has one address for the life of the program
and there is no way to make another:

```c
UART_Singleton_t *uart_get_instance(void)
{
    static UART_Singleton_t uart_singleton = {UART2, 0};

    if(!(uart_singleton.is_initialized))
    {
        /* configure pins, clock, baud rate on first call */
        uart_singleton.is_initialized = 1;
    }

    return &uart_singleton;
}
```

`is_initialized` gives it lazy initialization: the peripheral is set up on the
first `uart_get_instance()` call and every call after that just returns the
pointer. The demo leans on this through the `printf` retarget, which calls
`uart_get_instance()` on every character and never has to worry about whether
the UART was brought up yet.

## Why it is usually just a static variable

On a microcontroller you almost always know at compile time that there is one
UART2 and that it lives for the whole program. That removes the reasons the
textbook singleton exists. You are not deferring a decision about how many
instances to create, and you are not managing a lifetime, so the getInstance
ceremony often collapses into a plain file-scope `static` plus an `init`
function called once at startup. That is simpler, it costs no branch on every
access, and the "only one" guarantee comes from the variable being static, not
from any pattern.

The accessor form in this module buys one specific thing over that: lazy
initialization, so the peripheral configures itself on first use instead of
needing an explicit init call in the right place at boot. That is the honest
reason to reach for it. If you are going to call an `init` at startup anyway,
the `static` in the module and a couple of module functions give you the same
single instance with less machinery.

## When to use it (and when not to)

It fits a genuinely single hardware resource that several unrelated modules
touch: a UART shared by a logger and a shell, a clock, an ADC. It keeps them
from each holding their own copy of the handle and reconfiguring it out from
under each other.

The costs are worth naming. The lazy-init check is not atomic: if
`uart_get_instance()` can be entered from both an interrupt and the main loop,
two callers can both see `is_initialized == 0` and both run the setup. On a
single-threaded bare-metal loop that never happens, but under an RTOS or from
an ISR it is a real race, and the fix is to initialize once at startup before
any of that can run. The pattern also encourages global access, which is
convenient right up until you want to test a module in isolation or run it
against a second UART, and the hardcoded single instance is exactly what
stands in the way. Reach for it when the resource really is one and global;
otherwise pass a pointer.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The output goes to UART2 at 115200, where the retargeted `printf`
prints a few lines through the singleton while an LED blinks.

## Files

- [drivers/Inc/driver_uart.h](drivers/Inc/driver_uart.h): the
  `UART_Singleton_t` type and the accessor declaration.
- [drivers/Src/driver_uart.c](drivers/Src/driver_uart.c): `uart_get_instance`,
  the static instance and the lazy-init guard.
- [app/Src/main.c](app/Src/main.c): the `printf` retarget that reaches the
  singleton on every character.
