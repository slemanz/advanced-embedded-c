# State Pattern

The heaviest of the three variants and the one that scales furthest. Each
state becomes a set of function pointers, and a transition repoints them, so
the `switch` on the current state disappears completely. This is the same
digital stopwatch as the other two in [../](../); only the technique changes.

## The idea

A state is a struct of one function pointer per event:

```c
typedef void (*eventStartFunc)(watchStatePtr);
typedef void (*eventStopFunc)(watchStatePtr);

struct watchState
{
    eventStartFunc start;
    eventStopFunc stop;
};
```

The watch embeds one of these as its state, and an event is just a call
through the pointer, with no branch on which state is current:

```c
void watch_start(digitalStopWatchPtr instance, long max_time, long *current_count)
{
    instance->state.start(&instance->state);
    /* drive the timer */
}
```

A transition is a function that overwrites those pointers with a new state's
handlers. `defaultImplementation` fills both slots with no-ops so an event
that is invalid in the current state does nothing instead of needing a
default case:

```c
void transitionToStarted(watchStatePtr state)
{
    defaultImplementation(state);
    state->stop = stopWatch;   /* stop is valid while started */
}
```

Adding a state is a new pair of files (`xState.h` / `xState.c`) with its own
`transitionToX` and handlers. It does not touch the existing states, which is
the whole point of the pattern: the states stop knowing about each other's
internals and the machine grows by addition rather than by editing.

## When to use it (and when not to)

This shape earns its cost when states have genuinely different behavior and
the machine keeps growing. New states arrive as new files, invalid events are
absorbed by the default no-ops instead of scattered `default` cases, and no
single function has to know the whole transition table. That is real value in
a machine with many states that changes often.

The price is everything the [../conditional-state/](../conditional-state/)
version does not pay. Every event is an indirect call the compiler cannot
inline; the logic is spread across several files, so there is no one place to
read the whole machine; and for two states this is far more machinery than the
problem needs. The full comparison is in [../README.md](../README.md); the
short rule is to reach for this only when states keep being added.

One thing to know before reading the code as a reference: the stopped state's
`startWatch` handler calls `defaultImplementation(state)` where it should call
`transitionToStarted(state)`, so pressing start from stopped lands in the
no-op default state instead of started. The started to stopped edge is wired
correctly through `stopWatch`. The timer set and reset in `watch_start` and
`watch_stop` also run unconditionally, outside the state handlers, so the
state object does not actually gate the hardware here. Same as the sibling,
`watch_create` calloc's by pointer size rather than struct size.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The output goes to UART2 at 115200, where
the demo creates a watch, starts it and stops it.

## Files

- [app/Inc/watchState.h](app/Inc/watchState.h): the state struct, one function
  pointer per event, and `defaultImplementation`.
- [app/Src/stoppedState.c](app/Src/stoppedState.c) and
  [app/Src/startedState.c](app/Src/startedState.c): the two concrete states,
  each with its `transitionTo` and handlers.
- [app/Src/digitalStopWatch.c](app/Src/digitalStopWatch.c): the watch that
  calls events through the current state.
- [app/Src/main.c](app/Src/main.c): the create, start, stop sequence.
