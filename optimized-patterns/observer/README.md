# Observer Pattern

A sensor changes and several modules need to react: an LED, a UART logger. The
observer pattern sets up a one-to-many link where the subject holds a list of
observers and, when its state changes, calls each one. The subject never learns
what the observers do, only that it has a list to notify.

## The idea

An observer is a struct with an `update` method that takes `self`, so an
observer can carry its own state:

```c
typedef struct observer{
    void (*update)(struct observer *self, int data);
}observer_t;
```

The subject owns a fixed array of observer pointers plus its own state, and the
registration functions act on that array:

```c
typedef struct subject{
    observer_t *observer_list[MAX_OBSERVERS];
    int observer_count;
    int sensor_data;
}subject_t;

void subject_attach(subject_t *self, observer_t *obs);   /* append */
void subject_detach(subject_t *self, observer_t *obs);   /* find and shift down */
```

Notifying is a loop over whoever is attached, calling each observer through its
pointer:

```c
void subject_notify(subject_t *self)
{
    for(uint8_t i = 0; i < self->observer_count; i++)
        if(self->observer_list[i] && self->observer_list[i]->update)
            self->observer_list[i]->update(self->observer_list[i], self->sensor_data);
}
```

The demo makes a temperature-sensor subject, attaches a UART observer and an LED
observer, and every five seconds reads the ADC and calls `subject_notify`. Both
observers get the new value; the subject never mentions either by name.

## Same pattern, other implementation

[publisher-subscriber](../../design-patterns/publisher-subscriber/) is this same
pattern built the other way, and the pair is the interesting comparison. Here
registration lives on the subject: `subject_attach` and `subject_detach` are one
copy of the logic, and an observer is a struct with an `update(self)` method.
There registration is a callback plus a `void*` context, and each client
implements its own subscribe function that writes into the publisher's array,
which means the subscribe logic is duplicated per client. This form keeps one
copy of the registration and pays for it by requiring each observer to be a
struct of a fixed shape; the callback form is more flexible about what a
subscriber is but repeats the wiring. Same behavior, opposite trade of
duplication against uniformity.

## When to use it (and when not to)

It fits when the set of reactors to an event is dynamic or simply unknown to the
source: a sensor feeding modules that come and go, a state change several UIs
must reflect, a driver reporting completion to whoever registered. The subject
stays closed to change, and a new observer is a new module plus one `attach`.

The costs on a microcontroller are concrete. The `observer_list` is a fixed
array of `MAX_OBSERVERS` pointers sitting in the subject's RAM whether or not it
is full, and `subject_attach` silently drops any observer past that ceiling, so
the limit is real and unreported. Every notify is a synchronous loop of indirect
calls that cannot be inlined, so publishing costs the sum of every observer's
`update`, charged to whoever called `subject_notify`. That last point is sharp
if `subject_notify` runs in an ISR: every observer's work then runs in interrupt
context, and this demo's UART observer calls `printf`, a blocking UART write, so
notifying from an ISR would stall the interrupt for the whole transmission. The
subject also holds raw pointers, so an observer that goes out of scope without
detaching leaves a dangling pointer `notify` will happily call; and attaching the
same observer twice, or attaching or detaching from inside an `update` while the
loop is running, are all unguarded here. For one source and one reactor that
both live forever, a direct call is clearer. The pattern buys decoupling, and
that is only worth its RAM and indirection when the set of observers actually
varies.

## Build and run

STM32F411 (black pill). `make` builds `app/Build/final.elf` and
`app/Build/flash.bin`; `make load` flashes it through OpenOCD with a J-Link
over SWD. The demo reads the ADC every five seconds and notifies both observers,
printing the UART observer's line on UART2 at 115200 while the LED observer
reacts on the board.

## Files

- [app/Inc/observer.h](app/Inc/observer.h): the observer interface, an `update`
  method taking `self`.
- [app/Inc/subject.h](app/Inc/subject.h) and
  [app/Src/subject.c](app/Src/subject.c): the subject with its observer array,
  attach, detach and notify.
- [app/Src/uart_observer.c](app/Src/uart_observer.c) and
  [app/Src/led_observer.c](app/Src/led_observer.c): the two concrete observers.
- [app/Src/main.c](app/Src/main.c): the subject, the attaches, and the notify
  loop.
