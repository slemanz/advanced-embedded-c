# Builder Pattern

Configuring a peripheral means setting a handful of parameters that mostly
have sensible defaults: baud rate, word length, parity, mode. The builder
separates describing that configuration from applying it. You start from
defaults, override only the fields that differ, and one final step pushes the
result to the hardware.

## The idea

The product is a plain configuration struct, and `uart_builder_init` hands it
back filled with defaults:

```c
UART_Builder_t uart_builder_init(void)
{
    UART_Builder_t builder;
    builder.BaudRate   = 115200;
    builder.WordLength = UART_WORDLENGTH_8B;
    builder.Parity     = UART_PARITY_NONE;
    builder.Mode       = UART_MODE_TX_RX;
    return builder;
}
```

The setters each change one field. Nothing touches the peripheral yet; they
only edit the struct, and they return the builder pointer so the calls can be
chained:

```c
UART_Builder_t uart = uart_builder_init();

uart_set_baudrate(&uart, 9600);
uart_set_wordlength(&uart, UART_WORDLENGTH_8B);
uart_set_parity(&uart, UART_PARITY_NONE);
uart_set_mode(&uart, UART_MODE_TX);

uart_build(&uart);   /* this is the step that writes registers */
```

`uart_build` is the only function that reaches the hardware. It reads the
accumulated struct and writes it to `BRR` and `CR1` in one go. So the whole
"describe it, then apply it" split is: setters fill data, build commits it.
Because init starts from defaults, the caller only has to name what it wants
to change from them.

## When to use it (and when not to)

The builder earns its place when construction has real steps: parameters that
must be validated together, an order that matters, or several variants of the
same object assembled the same way. Separating the description from the commit
also means you can build the config in one place and apply it in another, or
inspect and adjust it before it ever hits a register.

For a fixed configuration like the demo's, be honest that it is more machinery
than the job needs. A designated initializer says the same thing in one
expression, starts from defaults the same way, and has no setter functions to
maintain:

```c
UART_Builder_t uart = { .BaudRate = 9600, .WordLength = UART_WORDLENGTH_8B,
                        .Parity = UART_PARITY_NONE, .Mode = UART_MODE_TX };
uart_build(&uart);
```

This is exactly the shape of a vendor HAL's `UART_InitTypeDef`: a config struct
you fill and pass to an init function. The chained-setter form buys readability
when there are many parameters or when a setter does more than assign (clamps a
value, enables a dependent field, rejects an invalid combination). If the
setters are one-line assignments and the config is fixed, the initializer is
clearer and costs nothing at runtime. The setters here return a pointer for
chaining, but the demo calls them one per line and never uses it, which is a
fair sign the chaining is not paying for itself yet.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo builds a UART2 config at 9600 8N1 TX and then prints
"Hello!" every five seconds on it.

## Files

- [drivers/Inc/driver_uart.h](drivers/Inc/driver_uart.h): the `UART_Builder_t`
  config struct and the setter and build declarations.
- [drivers/Src/driver_uart.c](drivers/Src/driver_uart.c): `uart_builder_init`
  with the defaults, the field setters, and `uart_build` writing the registers.
- [app/Src/main.c](app/Src/main.c): init, override, build, then the print loop.
