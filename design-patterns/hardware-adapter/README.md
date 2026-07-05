# Hardware Adapter Pattern

## Abstract

Useful when the application requires or uses one interface, but the
actual hardware provides another. The pattern creates an element that
convertes between the two interfaces.

## Problem

While hardware that performs similar functions tend to have similar
interfaces, often the information they need and the set of services
differ.

## Pattern Structure

The pattern extends the hardware proxy pattern by adding a hardware
adapter and explicitly showing the interface the client expects the
hardware support.

## Implementation Example

**[main.c](app/Src/main.c)**

- **[pulseOximetrySensor](app/Inc/pulseOximetrySensor.h)**

**Light To frequency:**

- **[LTF_photoDiodeProxy.h](app/Inc/LTF_photoDiodeProxy.h)**
- **[LTF_photoDiodeProxy.c](app/Src/LTF_photoDiodeProxy.c)**
- **[LTF_pulseOximetryAdapter.h](app/Inc/LTF_pulseOximetryAdapter.h)**
- **[LTF_pulseOximetryAdapter.c](app/Src/LTF_pulseOximetryAdapter.c)**

**Transimpedance Amplifier:**

- **[TIA_photoDiodeProxy.h](app/Inc/TIA_photoDiodeProxy.h)**
- **[TIA_photoDiodeProxy.c](app/Src/TIA_photoDiodeProxy.c)**
- **[TIA_pulseOximetryAdapter.h](app/Inc/TIA_pulseOximetryAdapter.h)**
- **[TIA_pulseOximetryAdapter.c](app/Src/TIA_pulseOximetryAdapter.c)**

**Display:**

- **[oximetryDisplay.h](app/Inc/oximetryDisplay.h)**
- **[oximetryDisplay.c](app/Src/oximetryDisplay.c)**