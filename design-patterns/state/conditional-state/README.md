# Conditional State

The baseline way to write a state machine: a `switch` on the current state
inside every event function, and the transition is a plain assignment to the
state field. No infrastructure, nothing hidden. This is the same digital
stopwatch as the other two variants in [../](../), so the only thing that
changes here is the technique.

## The idea

The state is an enum stored in the instance, behind an opaque pointer:

```c
typedef enum{
    stopped,
    started
}State;

struct digitalStopWatch{
    State state;
    TimeSource source;
    const char *name;
};
```

Each event is a function that switches on the current state, decides what to
do, and reassigns `instance->state`:

```c
void watch_start(digitalStopWatchPtr instance, long max_time, long *current_count)
{
    switch (instance->state)
    {
        case started:
            printf("Watch has already started\n");
            break;
        case stopped:
            instance->state = started;
            /* start the timer */
            break;
        default:
            printf("State does not exist.\n");
            break;
    }
}
```

The whole machine lives in the event functions. `watch_start` and
`watch_stop` each carry a copy of the "which state am I in" switch, and the
transition is the one-line `instance->state = ...` inside the matching case.

## When to use it (and when not to)

For a machine this small, this is the right choice. Two states and two events
fit in one screen, the control flow reads top to bottom, and there is no
indirection to trace: you can see every transition by reading the two event
functions. Any pattern layered on top of this would cost more than it saves.

It stops scaling when the state count grows. The switch is duplicated in every
event function, so adding a state means editing all of them, and it is easy to
handle a state in one event and forget it in another. When the transitions
themselves become the complicated part, [../table-based/](../table-based/)
moves them into a single array; when the states start having genuinely
different behavior and keep multiplying, [../state-pattern/](../state-pattern/)
replaces the switch with function pointers. The comparison of all three is in
[../README.md](../README.md).

Two things in the code here are worth knowing about. `watch_stop` is missing a
`break` after the `started` case, so it falls through into `stopped` and always
prints "already stopped"; that is a classic switch hazard, and exactly the kind
of bug the table and state-pattern variants avoid by not repeating the switch.
The `calloc(sizeof(digitalStopWatchPtr), sizeof(digitalStopWatchPtr))` in
`watch_create` also allocates by pointer size rather than struct size, the same
slip as in [../../adt/](../../adt/).

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The output goes to UART2 at 115200, where
the demo creates a watch, starts it and stops it.

## Files

- [app/Inc/digitalStopWatch.h](app/Inc/digitalStopWatch.h): the opaque handle
  and the three operations.
- [app/Src/digitalStopWatch.c](app/Src/digitalStopWatch.c): the enum state and
  the switch inside each event function.
- [app/Src/timeSource.c](app/Src/timeSource.c): the timer the watch drives.
- [app/Src/main.c](app/Src/main.c): the create, start, stop sequence.
