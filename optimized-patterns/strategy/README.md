# Strategy Pattern

The same ADC reading can be processed several ways: pass it through untouched,
smooth it with a moving average, filter it some other way. Strategy pulls that
choice of algorithm out of the reader and into an interchangeable object, so the
reader calls "filter this" without knowing which filter runs.

## The idea

The strategy interface here is not a bare function pointer but a struct with a
method, and that difference is the whole point of this version: passing the
strategy to its own method gives the algorithm a `this`, so it can carry state.

```c
struct FilterStrategy_t{
    uint32_t (*filter)(FilterStrategy_t *strategy, uint32_t rawValue);
};
```

A concrete strategy embeds that base as its first member and adds whatever state
it needs. The moving-average filter carries its own ring buffer:

```c
typedef struct {
    FilterStrategy_t base;   /* must be first, so a pointer to this is a base pointer */
    uint32_t samples[4];
    uint8_t index;
    uint8_t count;
} MovingAvarageFilter_t;
```

Because `base` is first, a `MovingAvarageFilter_t*` is a valid
`FilterStrategy_t*` (C inheritance by layout). The method casts it back to reach
its state:

```c
uint32_t movingAvarageFilter(FilterStrategy_t *strategy, uint32_t rawValue)
{
    MovingAvarageFilter_t *avg = (MovingAvarageFilter_t*)strategy;
    avg->samples[avg->index] = rawValue;      /* uses this strategy's own buffer */
    avg->index = (avg->index + 1) % 4;
    ...
}
```

The context is the `ADCReader_t`, which holds the ADC source and the current
filter and delegates without knowing either concretely:

```c
uint32_t ADCReader_readFiltered(ADCReader_t *reader)
{
    uint32_t raw = reader->adc->read();
    return reader->filter->filter(reader->filter, raw);
}
```

The demo wires a moving-average filter into a reader and prints ten filtered
values. A `noFilter` pass-through strategy is also provided, and swapping to it
is just pointing the reader at a different strategy.

## Same pattern in design-patterns

[design-patterns/strategy](../../design-patterns/strategy/) is the same pattern
in its minimal, stateless form, and the pair shows the two shapes a strategy
takes in C. There the interface is a bare `typedef void (*gpioStrategy)(int)`: a
plain function pointer, concrete strategies that are standalone functions with no
state, and the choice swapped at runtime on an opaque context. That is all you
need when the algorithm is a pure function.

This version is the stateful shape. A moving average has to remember its last
samples, and a bare function pointer has nowhere to keep them. Making the
strategy a struct whose method takes `self` as the first argument is what lets it
carry state per instance, and embedding the base as the first member is the C
trick that makes the cast safe. Reach for the function-pointer form when the
strategy is stateless; reach for this struct-plus-self form the moment the
algorithm needs to remember anything between calls.

## When to use it (and when not to)

Strategy fits when the choice of algorithm is genuinely dynamic: a filter picked
by operating mode, a control law selected by measurement, a variant chosen by
which hardware was detected. Each algorithm stays a standalone unit that is
testable on its own, and adding one does not touch the reader or the other
strategies.

The costs are the vtable's. The call through `filter->filter` is indirect and
cannot be inlined, so a strategy in the innermost sample loop pays a call per
sample where a direct function or a compile-time choice would not. Function
pointers also defeat static analysis of the call graph and make stack bounding
harder, which matters in safety-critical code. And the flexibility is often
unused: if the filter is fixed at build time, a direct call to
`movingAvarageFilter` says the same thing with no indirection. Note the demo
sets one strategy and never swaps it, which is a fair sign that here the runtime
selection is latent rather than exercised. Use the pattern when the switching is
real; if the algorithm never changes, this is indirection with no payoff.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo reads the ADC ten times through the moving-average filter and
prints each filtered value on UART2 at 115200.

## Files

- [app/Inc/filter_strategy.h](app/Inc/filter_strategy.h): the strategy interface
  struct and the moving-average concrete type with its state.
- [app/Src/filter_strategy.c](app/Src/filter_strategy.c): the `noFilter` and
  `movingAvarageFilter` implementations.
- [app/Inc/adc_reader.h](app/Inc/adc_reader.h) and
  [app/Src/adc_reader.c](app/Src/adc_reader.c): the context holding a source and
  a strategy, delegating through the interface.
- [app/Src/main.c](app/Src/main.c): wiring the filter into the reader and reading
  through it.
