# State Pattern

An object whose behavior depends on a mode, and a set of transitions between
those modes, is a state machine. The state pattern makes each state a piece of
code and the current state a pointer, so an event is a call through that pointer
and a transition is just repointing it. No `switch` on a mode variable anywhere.

## The idea

This is the pattern at its smallest: a state is a bare function pointer, and one
global holds the current one. The classic traffic light shows it in three lines
of infrastructure.

```c
typedef void (*StateHandler)(void);

StateHandler currentState = redStateHandler;   /* the whole "context" */

void runStateMachine(void)
{
    if(currentState != NULL)
        currentState();          /* an event is a call through the pointer */
}

void setNextState(StateHandler nextState)
{
    currentState = nextState;    /* a transition is a reassignment */
}
```

Each state does its work and names its successor. There is no table and no
branch on "which state am I": the knowledge of what comes next lives inside each
state.

```c
void redStateHandler(void)
{
    printf("Red Light: stop vehicle\n");
    setNextState(greenStateHandler);   /* red -> green */
}
```

The demo ticks `runStateMachine` every four seconds, so it cycles red, green,
yellow on the terminal, each state handing off to the next.

## Minimal, richer, and the design-patterns version

Three views of this idea are worth reading together. This module is the minimal
one: a state is a single function, and the context is one global pointer.
[state-example](../state-example/) is the same idea with a lifecycle: a state is
a struct of `enter`, `execute`, and `exit`, held in a small state-machine
context, so entering and leaving a state can run their own code, which is what
you want for a real acquisition or protocol machine. Start here for the shape,
read the example for the version that carries weight.

[design-patterns/state](../../design-patterns/state/) is the other axis. It puts
the same stopwatch behind three different techniques, conditional, table-based,
and this state pattern, and gives the rule for choosing between them. Both
modules here are the state-pattern technique specifically; if you are deciding
whether the state pattern is even the right tool rather than a `switch` or a
table, that comparison is the place to start. The short version of its rule:
reach for the state pattern only when states keep being added.

## When to use it (and when not to)

The state pattern fits when states have genuinely different behavior and the
machine keeps growing, because a new state is a new function that does not touch
the existing ones, and there is no central `switch` to keep in sync. It is a good
fit for protocol and mode machines that gain states over a project's life.

The costs are the usual ones for indirection, plus some specific to this minimal
form. Every tick is an indirect call the compiler cannot inline. More
importantly, the machine here is one file-scope `currentState`, so there is
exactly one state machine in the whole program; a second instance would need its
own context rather than a global, which is what [state-example](../state-example/)
moves toward with its `state_machine_t`. There is also no place to run
entry/exit code, so anything that must happen on entering or leaving a state has
to be bolted onto the handlers by hand, which the example solves with its
`enter`/`exit` slots. And for a machine of two or three states that rarely
changes, a plain `switch` reads top to bottom and costs nothing; the pattern
earns its keep from the point where states multiply.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo cycles the three traffic-light states every four seconds,
printing each on UART2 at 115200.

## Files

- [app/Src/main.c](app/Src/main.c): the `StateHandler` type, the global current
  state, the runner, and the three state handlers with their transitions.
