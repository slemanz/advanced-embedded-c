# Decorator Pattern

You have a working ADC read and you want to add logging around it without
touching the ADC code and without every caller learning about the log. A
decorator wraps the original behind the same interface: it holds a reference to
what it wraps, adds its own behavior, and delegates the rest. Callers use the
decorated object exactly as they used the plain one.

## The idea

The interface is one function pointer, and `BaseADC` is the plain
implementation that reads the hardware:

```c
typedef struct
{
    uint32_t (*read)(void);
}ADCInterface_t;

extern const ADCInterface_t BaseADC;
```

The decorator implements that same interface as its first member and keeps a
pointer to the thing it wraps:

```c
typedef struct
{
    ADCInterface_t interface;        /* what callers see and call */
    const ADCInterface_t *wrapped;   /* what it delegates to */
    void (*uart_transmit)(const char *);
}ADCLogger_t;
```

Its `read` delegates first, then adds the extra behavior on the way back:

```c
static uint32_t logged_read(void)
{
    uint32_t value = self.wrapped->read();   /* call the wrapped ADC */

    if(!button_get_state())                  /* on button press, log it */
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "LOG - ADC VALUE: %lu\n", value);
        self.uart_transmit(buffer);
    }

    return value;                            /* return the value unchanged */
}
```

`ADCLogger_Init` points the decorator's `interface.read` at `logged_read` and
stores the wrapped ADC. The demo then reads through
`adc_logger.interface.read()` and never calls the base ADC directly: same
interface, extra behavior, and the ADC code untouched. Because the decorator is
itself an `ADCInterface_t`, in principle another decorator could wrap it in
turn, which is how decorators stack (read plus log plus average plus range
check) from small pieces.

## When to use it (and when not to)

It fits when you want to add an orthogonal responsibility, logging, averaging,
range-checking, retry, to an existing operation without editing it and without
the callers knowing. Each concern stays a small separate wrapper, and you
compose the ones you need. That is genuinely useful when the concerns are
optional or vary between builds.

The costs start with the same indirect-call overhead every vtable pattern has,
paid once per layer: a read through three stacked decorators is three indirect
calls before the real work. On an ADC read that is minor; in a hot path it is
not.

The bigger catch here is a C-specific one worth understanding, because it is the
whole reason decorators are awkward in plain C. `logged_read` is a bare function
with no `this`, so it cannot know which decorator instance it belongs to. This
module works around that with a file-scope `static ADCLogger_t self` that
`ADCLogger_Init` fills in, and `logged_read` reads from that global. The
consequence is that there can only be one decorated object: initialize a second
`ADCLogger_t` and it overwrites `self`, so both end up delegating to whichever
was set up last. You cannot actually stack two loggers or decorate two ADCs with
this code, even though the pattern is supposed to allow exactly that. Doing it
properly means giving the callback an instance parameter to carry its context,
the same `void*`-context trick used in [observer](../observer/) and the
publish-subscribe module. If you only ever need one decorated object, the global
is fine; if you need the composability that is the point of the pattern, the
callback has to carry its instance. For a single fixed extra step, calling the
log inline is simpler than the wrapper.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo reads the ADC through the logger on a timer and, while the
user button is pressed, prints each value over UART2 at 115200.

## Files

- [app/Inc/adc_interface.h](app/Inc/adc_interface.h): the one-function
  interface and the `BaseADC` declaration.
- [app/Src/adc_interface.c](app/Src/adc_interface.c): the plain ADC read.
- [app/Inc/adc_logger.h](app/Inc/adc_logger.h) and
  [app/Src/adc_logger.c](app/Src/adc_logger.c): the decorator, its
  `logged_read`, and the global `self` it binds to.
- [app/Src/main.c](app/Src/main.c): wraps the ADC and reads through the
  decorator.
