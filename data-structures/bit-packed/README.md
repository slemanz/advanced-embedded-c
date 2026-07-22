# Bit-Packed

When several small values each fit in a handful of bits, storing one per byte
wastes most of every byte. Bit-packing puts them side by side inside one word:
a mode, a flag, and a speed that need 2, 1, and 3 bits go into a single byte
instead of three. On a part with kilobytes of RAM, in a flash log, or on the
wire over SPI or I2C, that packing is the difference between fitting and not.
This module shows the two ways to do it and where each belongs.

## The idea

There are two techniques, and they trade the same way everywhere: readable
versus portable.

The first is a bitfield: you declare the widths in the struct and let the
compiler do the shifting. `bad.c` packs a sensor config this way.

```c
typedef struct {
    uint8_t mode  : 2;   /* 0-3 */
    uint8_t flag  : 1;   /* 0 or 1 */
    uint8_t speed : 3;   /* 0-7 */
} SensorConfig;          /* sizeof == 1, not 3 */
```

It reads well and `sizeof` proves the saving, but the layout is the compiler's
to decide. Which end bit 0 sits at, how fields straddle a boundary, and how much
padding gets inserted all depend on the compiler and the target, so the same
struct can lay out differently on two builds. That is why the file is named
`bad.c`: fine for internal state, wrong for anything that crosses a boundary.

The second is manual masking with bitwise operators, in `better.c`. You define a
mask per field and pack and unpack by hand.

```c
#define MODE_MASK  0x03   /* bits 0-1 */
#define FLAG_MASK  0x04   /* bit 2    */
#define SPEED_MASK 0x38   /* bits 3-5 */

unsigned char pack_data(unsigned char mode, unsigned char flag, unsigned char speed)
{
    return (mode & 0x03) | ((flag & 0x01) << 2) | ((speed & 0x07) << 3);
}
```

Now the layout is written down, not inferred, so it is identical on every
compiler and architecture. This is the form you use for a hardware register or a
protocol frame, where the bit positions are fixed by something outside your code.

`gpio_packed.c` (which `main.c` builds as the running demo) is the same masking
applied to a real peripheral: it packs GPIO mode, state, and speed into one
byte, then unpacks it to drive PC13's `MODER`, `OSPEEDR`, and `ODR` registers,
and toggles the LED by flipping just the state bit in the packed byte. It shows
that a peripheral register is itself a bit-packed structure, and reading or
writing one is exactly this mask-and-shift.

## When to use it (and when not to)

Reach for bit-packing when space or bandwidth is the constraint: many flags or
small enums held in bulk, a sensor record you want to fit more of in EEPROM, a
message where every byte on the link costs time and power. The saving is real
and the memory-versus-fields tradeoff is easy to see.

| Field | One value per byte | Packed |
| --- | --- | --- |
| mode (2 bits) | 1 byte | 2 bits |
| flag (1 bit) | 1 byte | 1 bit |
| speed (3 bits) | 1 byte | 3 bits |
| total | 3 bytes | 1 byte |

The choice between the two forms is the honest part. Prefer masks over bitfields
for anything whose exact layout matters, which on an MCU is most of the
interesting cases: registers, wire formats, anything stored and read back by
other code. Bitfields carry limits that masks do not.

| Bitfield limitation | Why it bites |
| --- | --- |
| Layout is compiler-defined | Bit order and straddling vary between builds |
| Padding is unpredictable | `sizeof` can differ from the bits you counted |
| Cannot take the address of a field | No `&field`, so no pointer to it |
| Extra instructions per access | The compiler shifts and masks anyway |

And when *not* to pack at all: packing is never free at access time. Every read
is a mask and a shift, every write is a read-modify-write, so a value touched in
a hot loop can cost more in cycles than the byte it saves. If you have RAM to
spare and the field is hit constantly, leave it in its own byte. Pack when the
pressure is on storage or bandwidth, not when it is on speed. The related tension
between saving space and paying to access it also runs through
[memory](../memory/), where the fixed-size default is the counterweight.

## Build and run

STM32F411 (black pill). `make` builds `Build/flash.elf` and `Build/flash.bin`
from `app/Src/main.c`, and `make load` flashes it through OpenOCD with a J-Link
over SWD. The running demo packs the LED's GPIO settings into one byte,
configures PC13 from it, prints the unpacked values on UART2 at 115200, and then
toggles the LED once a second by flipping the packed state bit. To run one of
the other demos, point `main.c` at `bad.c` or `better.c`.

## Files

- [app/Src/bad.c](app/Src/bad.c): the bitfield form, compact to read but with
  compiler-defined layout, named for why you avoid it across a boundary.
- [app/Src/better.c](app/Src/better.c): the same fields packed by hand with masks
  and shifts, portable and explicit.
- [app/Src/gpio_packed.c](app/Src/gpio_packed.c): masking applied to real GPIO
  registers, showing a peripheral register as a bit-packed structure. `main.c`
  is a copy of this and is what the build runs.
