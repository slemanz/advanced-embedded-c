# Publisher-Subscriber Pattern

Also known as observer.

A sensor produces readings, and several modules care about them. Calling each
one directly means the sensor holds a list of everybody it must inform, and
adding a consumer means editing the sensor. Publish-subscribe inverts it: the
consumers register themselves, and the publisher only knows it has a list of
callbacks to fire.

## The idea

The publisher keeps a fixed array of subscriptions, each one a callback plus
the object it belongs to:

```c
typedef void (*callback_fn)(void *pObject, env_data_t data);

typedef struct notify_handler{
    void *pObject;          /* Pointer to client object */
    callback_fn fn_handler; /* Callback fn */
}notify_handler_t;

typedef struct env_sensor{
    env_data_t data;
    uint32_t n_client;
    notify_handler_t clients[MAX_CLIENT];
}env_sensor_t;
```

The `void *pObject` next to the function pointer is what makes this work in
C: the callback is a plain function, so it has to be told which instance it
is acting on. The client casts it back on entry
(`((display_client_t *)me)->data = data`), which is what a method call does
for free in a language with objects.

Publishing is then a loop over whoever is registered, and the publisher never
learns what any of them do:

```c
void env_sensor_notify(env_sensor_t *const me)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        if(me->clients[i].pObject != NULL && me->clients[i].fn_handler != NULL)
        {
            me->clients[i].fn_handler(me->clients[i].pObject, me->data);
        }
    }
}
```

The demo is an environmental sensor (temperature, humidity, sprayed) with two
subscribers: an LCD display and a fertilizer mixer. It publishes twice with
both attached, unsubscribes the display and publishes twice more, then
resubscribes it and dumps the list, so the dynamic membership is visible on
the terminal.

## Same pattern, other implementation

[optimized-patterns/observer](../../optimized-patterns/observer/) is this same
pattern built differently, and the pair is worth reading together. There the
subject holds an array of pointers to observer structs, and attach/detach are
operations on the subject (`subject_attach`, `subject_detach`). Here the
subscription is a callback plus a context pointer, and each client implements
its own subscribe function that writes into the publisher's array.

That difference is the interesting part. Keeping registration on the
publisher side means one copy of the logic, while the callback form here
leaves `display_client_subscribe` and `fertilizer_mixer_client_subscribe` as
near-identical code repeated per client. The callback plus `void*` form is
more flexible, since a subscriber does not have to be a struct of a
particular shape, but it pays for that with duplication and with casts the
compiler cannot check.

## When to use it (and when not to)

It fits when the set of consumers is genuinely dynamic, or simply unknown to
the producer: an event bus, a sensor feeding modules that come and go, a
driver reporting completion to whoever asked. It keeps the producer closed to
modification, which is worth a lot when the producer is a stable driver and
the consumers are application code that keeps changing.

The costs on a microcontroller are specific. Notification is a synchronous
loop of indirect calls, so publishing costs the sum of every subscriber's
work, charged to whoever called publish: do it from an ISR and one slow
subscriber lengthens the interrupt. The `void *` erases the type, so a
mismatched callback and object is a runtime crash instead of a compile error.
`MAX_CLIENT` fixes the ceiling, and this implementation silently ignores a
subscribe past it. Registration also creates lifetime hazards: a subscriber
destroyed without unsubscribing leaves a dangling pointer the publisher will
happily call.

For one producer and one consumer that both live for the whole program, a
direct call is clearer and free. This pattern buys decoupling, and decoupling
is only worth paying for when something actually varies.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The output goes to UART2 at 115200.

## Files

- [app/Inc/env_sensor.h](app/Inc/env_sensor.h): the publisher and the
  subscription structure.
- [app/Src/env_sensor.c](app/Src/env_sensor.c): the notify loop.
- [app/Src/env_display_client.c](app/Src/env_display_client.c) and
  [app/Src/fertilizer_mixer_client.c](app/Src/fertilizer_mixer_client.c): the
  two subscribers, each with its own subscribe and handler.
- [app/Src/main.c](app/Src/main.c): the subscribe, publish and unsubscribe
  sequence.
