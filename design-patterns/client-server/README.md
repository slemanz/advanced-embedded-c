# Client-Server Pattern

One module produces data and several others consume it, each at its own pace
and for its own purpose. Wiring the producer directly to every consumer means
it has to know all of them, and adding a consumer means editing the producer.
The pattern puts a server between them: the producer writes there, and the
clients read from there, none of them aware of the others.

## The idea

The demo is an ECG chain. The server is a queue of time-marked samples,
holding a fixed buffer and the write position:

```c
struct TMDQueue{
    uint32_t head;
    uint32_t size;
    timeMarkedData buffer[QUEUE_SIZE];
};
```

`ECG_Module` is the producer: it acquires values from the leads and calls
`TMDQueue_insert`. Three clients read from the same queue, each for a
different job: `QRSDetector` computes heart rate, `histogramDisplay` shows
the distribution, and `arrythmiaDetector` looks for irregularities.

The detail that makes the pattern work is that each client carries its own
read index:

```c
struct QRSDetector{
    uint32_t index;
    struct TMDQueue *itsTMDQueue;
    uint32_t heartRate;
};

void histogramDisplay_getValue(histogramDisplay *const me)
{
    timeMarkedData tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    me->index = TMDQueue_getNextIndext(me->itsTMDQueue, me->index);
}
```

So `TMDQueue_remove` does not actually remove anything; it reads the sample
at the client's index and leaves the buffer alone. Each client walks the
shared data at its own speed, and a slow client never starves a fast one.
That is why the demo can interleave calls freely: six acquisitions, five
histogram reads, two QRS reads, another histogram read. Everyone sees a
consistent view of what they have not consumed yet.

`systemManager` owns all five objects as members and wires each client's
queue pointer at init, so the composition lives in one place.

## When to use it (and when not to)

This is the right shape when data has one producer and several independent
consumers, especially when they run at different rates: an ADC filling a
buffer while a display, a logger, and a control loop each read what they
need. It decouples them completely, so a new client is a new module and the
producer never changes. Buffering also absorbs bursts, which is what lets an
ISR produce and a main loop consume.

The costs start with the buffer itself: `QUEUE_SIZE` fixes how far behind the
slowest client may fall, and if it falls further the producer overwrites data
the client has not read. Nothing in this implementation detects that, and
sizing the queue means knowing the worst-case lag of every client. The shared
buffer also becomes a concurrency problem the moment producer and consumer
live in different contexts: an insert from an ISR while a client reads needs
protection this demo does not have. And each client holding its own index
means the state of "who has read what" is scattered rather than centralized.

For one producer and one consumer, a plain circular queue is simpler and says
the same thing. The pattern earns its keep from the third client onward.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the demo runs a fixed sequence of inserts and reads, printing each store and
each client read with its own index, so the independent walk through the
buffer is visible.

## Files

- [app/Inc/TMDQueue.h](app/Inc/TMDQueue.h) and
  [app/Src/TMDQueue.c](app/Src/TMDQueue.c): the server.
- [app/Src/ECG_Module.c](app/Src/ECG_Module.c): the producer.
- [app/Src/QRSDetector.c](app/Src/QRSDetector.c),
  [app/Src/histogramDisplay.c](app/Src/histogramDisplay.c) and
  [app/Src/arrythmiaDetector.c](app/Src/arrythmiaDetector.c): the three
  clients, each with its own index.
- [app/Src/systemManager.c](app/Src/systemManager.c): composition and wiring.
- [app/Src/main.c](app/Src/main.c): the interleaved demo sequence.
