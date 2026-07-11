# Bit Fields

Bit-fields let a struct member occupy an exact number of bits, so a set of
flags and small values packs into one word while the code keeps reading like
normal member access. This module is a small demo of the technique, and of
the reason it must stay away from hardware registers.

## The idea

The demo packs a device status into ten bits:

```c
typedef struct
{
    unsigned enable           : 1;
    unsigned errorStatus      : 1;
    unsigned sensorResolution : 4;
    unsigned currentState     : 2;
    unsigned nextState        : 2;
} statusBits_t;
```

Writing `device_status.enable = 1` replaces the manual mask-and-shift, and
the compiler generates the read-modify-write behind the scenes. For internal
state this is a clean trade: less error-prone than hand-written masks, and
the whole status fits in a single word.

## The classic warning

The C standard leaves the layout of bit-fields implementation-defined: the
allocation order inside the storage unit (LSB-first or MSB-first), whether a
field can straddle a unit boundary, and the size and alignment of the unit
itself all depend on the compiler and ABI.

For hardware registers this is disqualifying. Overlaying a bit-field struct
onto a register address assumes the compiler places each field on the exact
bit the datasheet names, and nothing guarantees it. On top of the layout
problem, the generated read-modify-write may access the register with a
width or access pattern the peripheral does not support. This is why vendor
headers define registers with masks and shift macros instead of bit-fields.
The same layout problem applies to anything that leaves the program: structs
sent over a wire or stored in flash and read back by code from another
compiler.

The safe territory is what the demo does: state that lives and dies in RAM,
read and written only by code built by one compiler.

## Build and run

STM32G0B1 (Nucleo). `make` builds `app/Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. On the serial terminal (UART2, 115200)
the demo prints the device status read back from the bit-fields.

## Files

- [app/Src/main.c](app/Src/main.c): the packed status struct and its use.
