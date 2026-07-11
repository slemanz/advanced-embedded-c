# State Machines

Three implementations of the same state machine, so the differences are the
implementation technique and nothing else. The machine is a digital
stopwatch on the STM32G0B1 with two states (stopped, started) and two events
(start, stop), deliberately small enough that each variant fits in one
reading.

## The three variants

- [conditional-state/](conditional-state/): the baseline. A `switch` on the
  current state inside every event function, transitions as direct
  assignments to `instance->state`. Zero infrastructure, everything visible,
  but the logic of the machine is scattered across the event functions and
  every new state or event grows all of them.
- [table-based/](table-based/): the transitions move into data, a
  `transitionTable[state][event]` array that answers "given this state and
  this event, what is the next state" in one place. The whole machine is
  readable in one table, and growing it means growing the table instead of
  editing logic. The actions still live in code next to it.
- [state-pattern/](state-pattern/): each state is a struct of function
  pointers (`watchState` with `start` and `stop`), and a transition
  repoints them (`transitionToStarted` swaps in that state's handlers). The
  `switch` disappears entirely: an event is just `state->start(...)`, and
  invalid events fall into a default implementation. Adding a state is a new
  file that does not touch the existing ones.

## Choosing between them

For a machine this size, conditional wins: any indirection costs more than
it saves, and the `switch` reads top to bottom. Table-based starts paying
off when states and events multiply and the transitions are the complex
part, because the table stays reviewable long after nested switches stop
being. The state pattern fits when the states have genuinely different
behavior and the machine keeps growing, since new states arrive without
editing old ones; the price is indirection, more files, and losing the
single place where the whole machine can be seen. A reasonable rule: start
conditional, move to a table when the switch stops fitting in your head,
and reach for the state pattern only when states keep being added.

Each folder is a complete buildable project with its own README.
