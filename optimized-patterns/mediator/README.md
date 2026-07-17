# Mediator Pattern

When several modules have to coordinate, wiring them to each other directly
means every module knows every other one, and the interactions multiply. The
mediator puts one hub in the middle: modules report events to it and it decides
what happens next, so the modules stay unaware of each other and only the hub
holds the coordination logic.

## The idea

The mediator interface is one function pointer, notify, and the whole system is
a context struct that holds the mediator and its colleagues together:

```c
typedef struct
{
    void (*notify)(EmbeddedSystem_t *system, const char *event);
}Mediator_t;

typedef struct EmbeddedSystem_t
{
    Mediator_t mediator;   /* the hub */
    Sensor_t sensor;       /* colleague */
    Actuator_t actuator;   /* colleague */
}EmbeddedSystem_t;
```

Each colleague keeps a back-pointer to the mediator and never references the
other colleague. The sensor reads its value and reports an event; it does not
know an actuator exists:

```c
void sensor_read(Sensor_t *sensor, struct EmbeddedSystem_t *system)
{
    sensor->sensorValue = adc_read();
    sensor->mediator->notify(system, "SensorUpdate");
}
```

All the coordination lives in the concrete mediator. It reacts to an event,
applies the policy (here a threshold), and drives the other colleague by sending
itself the next event:

```c
void concrete_notify(EmbeddedSystem_t *system, const char *event)
{
    if(strcmp(event, "SensorUpdate") == 0)
    {
        if(system->sensor.sensorValue > 1500)
            system->mediator.notify(system, "Activate");   /* re-enters */
    }
    else if(strcmp(event, "Activate") == 0)
    {
        system->actuator.state = 1;
        led_on();
    }
}
```

So the sensor to actuator link exists only inside the mediator: the sensor says
"SensorUpdate", the mediator decides the value is high enough and says
"Activate", and that branch turns the actuator on. Add a third colleague and its
interactions are new branches in this one function, not new wires between
modules.

## Minimal versus the example

This is the pattern at its smallest, and [mediator-example](../mediator-example/)
is the same idea scaled up, so the two are worth reading as a pair. Here
everything is one static `EmbeddedSystem_t`: the mediator lives inside the
context struct, the colleagues are plain members, and there is no allocation.
The example instead gives colleagues a shared `Colleague_t` base (C inheritance
by embedding), a `MediatorInterface_t` vtable, and heap-allocated devices, which
is what the pattern grows into when there are many colleagues and richer events.
Start here for the shape, read the example to see it carry weight.

## When to use it (and when not to)

The mediator earns its place when several modules have genuinely many-to-many
interactions. Wiring N modules pairwise trends toward N-squared links that all
have to change together; routing everything through one hub turns that into N
modules that each know only the hub. It is the right call for coordination logic
that would otherwise be smeared across every module, and it gives you one place
to see and change the system's behavior.

The costs are the flip side of that centralization. The hub is a single point:
if it is wrong or it fails, every interaction is affected, and there is no
coordination left anywhere else to fall back on. It also tends to grow into a
god object, since every new interaction is another branch in one function, and a
large mediator can be harder to follow than the direct calls it replaced. This
implementation routes on strings with `strcmp`, which is both slower than it
needs to be and stringly-typed: a misspelled `"Activate"` is not a compile error,
it is an event that silently never matches, and an event enum would be cheaper
and checkable. Notify also re-enters itself here (`SensorUpdate` triggers
`Activate` through the same pointer); it is bounded in this demo, but a mediator
that calls itself needs its recursion kept obviously finite. For two modules with
one interaction, a direct call is clearer; the hub pays off from the point where
the interactions, not the modules, are the complicated part.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo reads the ADC every two seconds and reports it to the
mediator; when the value crosses the threshold the mediator activates the
actuator and lights the LED, printing each routed step on UART2 at 115200.

## Files

- [app/Inc/mediator.h](app/Inc/mediator.h): the one-function mediator
  interface.
- [app/Inc/embedded_system.h](app/Inc/embedded_system.h): the context struct
  holding the mediator and both colleagues.
- [app/Src/concrete_mediator.c](app/Src/concrete_mediator.c): the routing logic
  and the system init.
- [app/Src/sensor.c](app/Src/sensor.c) and
  [app/Src/actuator.c](app/Src/actuator.c): the colleagues, each with only a
  back-pointer to the mediator.
- [app/Src/main.c](app/Src/main.c): the read-and-report loop.
