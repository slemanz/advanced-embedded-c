# Hardware Adapter Pattern

Hardware that performs the same function rarely offers the same interface.
Two photodiode front ends both measure blood oxygen, but one reports a
frequency and the other raw ADC counts, with different function names and
different math to get a real reading. The adapter converts between the
interface the application wants and the one each device provides.

## The idea

The pattern builds on the [hardware proxy](../hardware-proxy/): the proxy
encapsulates one device, and the adapter converts that device's interface
into the one clients expect. The client interface is declared explicitly:

```c
struct pulseOximetrySensor
{
    uint32_t (*readSpO2)(void);
    uint32_t (*readPulse)(void);
};
```

Below it sit two different sensors, each with its own proxy speaking its own
vocabulary:

```c
struct LTF_photoDiodeProxy      // light to frequency
{
    uint32_t (*accessSpO2)(void);
    uint32_t (*accessPulse)(void);
};

struct TIA_photoDiodeProxy      // transimpedance amplifier
{
    uint32_t (*getSpO2)(void);
    uint32_t (*getPulse)(void);
};
```

The adapters are where the difference is absorbed. The LTF device returns a
frequency, so its adapter scales it (`accessSpO2() / 9.6`). The TIA device
returns ADC counts, so its adapter converts to volts first and then applies
its own curve:

```c
temp = me->itsTIA_photoDiodeProxy->getSpO2();
volts = ((temp * 3.3) / 4095);
computed_spo2 = volts * 30;
```

Different names, different units, different math, one interface out. The
display reads both sensors the same way and prints them side by side, which
is the whole demonstration: swapping the hardware would mean writing a new
adapter, not touching the display.

## When to use it (and when not to)

The adapter earns its place when the hardware is expected to be replaced or
to coexist in variants, which is common in products that ship with a second
sourced part, or in devices where a sensor is chosen per build. It also
isolates the ugly conversion math from the application, and keeps that math
testable on its own.

The costs are the usual for indirection, plus one specific to this pattern.
Every read goes through a function pointer into another function, so the
compiler cannot see through the call and a hot path pays for it. Each device
now needs two layers written and maintained (proxy and adapter) instead of
one driver. And the specific cost: the adapter can only export what the
common interface can express. If one sensor offers something the other cannot
(a calibration mode, a higher rate), the interface either grows to a lowest
common denominator or leaks the device back into the client. When there is
one device and no plan to change it, a plain driver is the right answer.

Note that this demo allocates every proxy and adapter with `malloc` at init.
Firmware that cannot afford a heap would make them static instances instead;
the pattern does not depend on dynamic allocation.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the display prints SpO2 and pulse from both sensors every 5 seconds.

## Files

- [app/Inc/pulseOximetrySensor.h](app/Inc/pulseOximetrySensor.h): the
  interface the application expects.
- [app/Src/LTF_pulseOximetryAdapter.c](app/Src/LTF_pulseOximetryAdapter.c)
  and [app/Src/TIA_pulseOximetryAdapter.c](app/Src/TIA_pulseOximetryAdapter.c):
  the two adapters, where the conversion lives.
- [app/Inc/LTF_photoDiodeProxy.h](app/Inc/LTF_photoDiodeProxy.h) and
  [app/Inc/TIA_photoDiodeProxy.h](app/Inc/TIA_photoDiodeProxy.h): the two
  device interfaces being adapted.
- [app/Src/oximetryDisplay.c](app/Src/oximetryDisplay.c): the client reading
  both sensors through the same interface.
