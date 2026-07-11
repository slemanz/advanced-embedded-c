# Mediator Example

The applied counterpart of [mediator/](../mediator/): where that module shows
the pattern at its minimum (one sensor, one actuator, a concrete mediator
routing between them), this one builds a larger simulation to see how the
pattern behaves with more colleagues and richer events. The scenario is home
automation: a light, a thermostat and a security system that never talk to
each other, only to the mediator.

## The idea

Every device shares a `Colleague_t` base carrying a pointer to the mediator
and two operations:

```c
struct Colleague_t
{
    Mediator_t *mediator;
    void (*sendEvent)(Colleague_t *colleague, const char *event);
    void (*performAction)(Colleague_t *colleague, const char *action);
};
```

Concrete devices embed the base as their first member (`Light_t`,
`Thermostat_t`, `SecuritySystem_t`), which is the C way of inheriting: a
pointer to the device is a valid pointer to its base. The mediator side
mirrors it with a vtable (`MediatorInterface_t` holding `notify`), and the
concrete `HomeAutomationMediator_t` keeps opaque references to all three
devices and routes string events with `strcmp`: `"security_on"` arriving
from any device fans out to actions on the others.

Compared to the minimal module, two things stand out. The wiring has a
chicken-and-egg step: colleagues are created with a `NULL` mediator, then
the mediator is created holding the colleagues, then each colleague gets the
real reference. And everything lives on the heap (`create` functions with
allocation checks and a final `free` pass), which fits a simulation but is a
cost most firmware would replace with static instances.

## Build and run

STM32F411. `make` builds `app/Build/final.elf`, `make load` flashes it
through OpenOCD with a J-Link over SWD. On the serial terminal (UART2,
115200) the demo wires the system up, simulates events, triggers direct
actions on each device and shuts down, printing every routed step.

## Files

- [app/Inc/colleague.h](app/Inc/colleague.h): the colleague base and the
  three device types.
- [app/Src/mediator.c](app/Src/mediator.c): the home automation mediator and
  its event routing.
- [app/Src/main.c](app/Src/main.c): the wiring sequence and the simulated
  events.
