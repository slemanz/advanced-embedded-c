# State Pattern Example

The applied counterpart of [state](../state/): where that module shows the state
pattern at its minimum (a bare function pointer per state, one global holding the
current one), this one is the version with a lifecycle and a real pipeline. Each
state has `enter`, `execute`, and `exit`, and the machine runs a small ADC
acquisition loop: idle, read the ADC, transmit or error, back to idle.

## The idea

A state is a struct of three function pointers, one per phase of being in that
state:

```c
typedef struct state
{
    void (*enter)(void);     /* runs once when the state becomes current */
    void (*execute)(void);   /* runs each tick while in the state */
    void (*exit)(void);      /* runs once when leaving */
}state_t;

typedef struct
{
    state_t *current_state;
}state_machine_t;
```

Transitioning is one function that fires the lifecycle in order: the old state's
`exit`, the swap, the new state's `enter`. `execute` is left for the main loop to
call each tick.

```c
void state_machine_set_state(state_machine_t *sm, state_t *new_state)
{
    if(sm->current_state && sm->current_state->exit)
        sm->current_state->exit();

    sm->current_state = new_state;

    if(sm->current_state && sm->current_state->enter)
        sm->current_state->enter();
}
```

Each concrete state is one file with a `state_t` instance and its three static
handlers. The pipeline is: `state_idle` moves to `state_read_adc`, whose `enter`
brings up the ADC over DMA and whose `execute` reads a channel and branches on a
threshold, going to `state_error` if the value is too high or `state_transmit`
otherwise; transmit prints the value and returns to idle; error blinks the LED
and returns to idle. The main loop just calls `current_state->execute()` on a
one-second tick and never names a state itself.

## Minimal, richer, and the design-patterns version

Read this next to [state](../state/), which is the same pattern without the
lifecycle: there a state is a single function and the context is a global
pointer, here a state is an `enter`/`execute`/`exit` struct held in a
`state_machine_t`. The `enter`/`exit` slots are the reason to use this form: the
ADC state can bring the peripheral up on entry and tear it down on exit, which
the bare-function version has nowhere to put.

[design-patterns/state](../../design-patterns/state/) is where the choice of
technique is made. It compares conditional, table-based, and state-pattern
implementations of one stopwatch and gives the rule for picking. This module is
the state-pattern technique at a realistic size; if you are still deciding
whether the state pattern beats a `switch` or a table for your machine, start
from that comparison.

## When to use it (and when not to)

This form fits a machine whose states have real setup and teardown and genuinely
different behavior: an acquisition pipeline, a communication protocol with idle,
transmit, and error phases, a mode machine that gains states over time. The
`enter`/`exit` lifecycle keeps resource handling paired with the state that owns
it, and each state is a separate file that can be read and changed on its own.

The costs are indirection plus the price of the ceremony. Every tick and every
transition is an indirect call the compiler cannot inline, and a full machine is
several files, so there is no single place to see all of it at once, which is the
tradeoff against the table-based form where the whole machine is one array. There
are a couple of things to know about this specific code: `state_read_adc_enter`
calls `adc_dma_init` every time the state is entered, re-initializing the
peripheral each cycle rather than once, and `state_read_adc_execute` assigns
`valid_sensor_data` after it has already called `set_state` to transmit, which
happens to be fine only because `execute` runs on the next tick, not inside the
transition. For a two-state or three-state machine that never grows, this is far
more structure than the job needs; a `switch` says the same thing. The lifecycle
pays off when states have setup and teardown worth isolating.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo walks the idle, read, transmit and error states on a
one-second tick, printing each enter, execute and exit on UART2 at 115200.

## Files

- [app/Inc/state_machine.h](app/Inc/state_machine.h) and
  [app/Src/state_machine.c](app/Src/state_machine.c): the `state_t` lifecycle
  struct, the machine context, and the transition that fires exit then enter.
- [app/Src/state_idle.c](app/Src/state_idle.c),
  [app/Src/state_read_adc.c](app/Src/state_read_adc.c),
  [app/Src/state_transmit.c](app/Src/state_transmit.c) and
  [app/Src/state_error.c](app/Src/state_error.c): the four concrete states.
- [app/Src/adc_dma.c](app/Src/adc_dma.c): the DMA-driven ADC the read state uses.
- [app/Src/main.c](app/Src/main.c): the initial state and the execute tick.
