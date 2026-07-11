# Table-Based State Machine

The table-based variant of the [state machine comparison](../): the
transitions of the digital stopwatch move out of the control flow and into a
data table indexed by current state and incoming event.

## The idea

The whole transition logic is one array:

```c
static State transitionTable[NO_OF_STATES][NO_OF_EVENTS] = {
    /* stopped */ {stopped, started},
    /* started */ {stopped, started}
};
```

Rows are the current state, columns are the events (stop, start), and each
cell answers "what is the next state". An event handler ends with a lookup
instead of an assignment chosen by logic:

```c
instance->state = transitionTable[currentState][startEvent];
```

The actions (starting and stopping the timer, the prints) still live in code
next to the lookup, in the same `switch` the conditional variant uses. The
table replaces the transition decisions, not the work. A fuller version of
the technique also puts action function pointers in the cells, so the table
holds the entire machine.

With two states and two events the table is small enough to look trivial,
and both rows even come out identical, since here the next state depends
only on the event. The shape is the point: when a real machine grows to ten
states and eight events, this same table stays a readable grid while nested
switches stop being reviewable. The trade-offs against the other two
variants are in the [comparison page](../).

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the demo creates a stopwatch, starts it and stops it, printing each
transition.

## Files

- [app/Src/digitalStopWatch.c](app/Src/digitalStopWatch.c): the transition
  table and the event handlers.
- [app/Src/timeSource.c](app/Src/timeSource.c): the timer backends (TIM2 and
  SysTick) the watch drives.
- [app/Src/main.c](app/Src/main.c): the demo sequence.
