# Shared

Bootloader and application are two separate programs, so by default each one
carries its own copy of every driver it uses, even when both need the same
LED and UART code. This module shows how the bootloader can export functions
to the application through a table at a fixed address, so the code exists
only once, inside the bootloader.

## The idea

The bootloader builds a struct of function pointers and pins it at
`0x08004000` through a dedicated linker section:

```c
struct btl_common_apis common_apis __attribute__((section(".COMMON_APIS"))) = {
    led_on,
    led_off,
    led_toggle,
    uart2_write_byte
};
```

```ld
COMMON_APIS 0x08004000 :
{
    KEEP(*(.COMMON_APIS))
} >CUSTOM_MEMORY
```

The application never links those drivers. It declares the same struct layout
and casts the fixed address:

```c
struct btl_common_apis *btl_common_apis = (struct btl_common_apis*)0x08004000;

btl_common_apis->led_toggle();
btl_common_apis->uart_write_byte('h');
```

This is the same mechanism vendors use for ROM APIs: a jump table at a known
address is a stable contract between two programs that were built and flashed
independently.

## When to use it (and when not to)

It pays off when the bootloader is permanent and the application updates
often: shared drivers stop being duplicated in every image, and the
application shrinks. The costs are real, though. The struct layout is defined
twice (one on each side) and nothing checks they match; reordering a field on
one side silently corrupts every call. Appending new functions at the end is
the only safe evolution. And the application becomes unrunnable without a
flashed, compatible bootloader, which makes standalone debugging harder.

## Build and run

Same recipe as [bootloader-v1](../bootloader-v1/): `make` in `bootloader/`
(the pad script runs automatically), then `make` in `app/`, which embeds the
bootloader binary into the app image, then `make load` (OpenOCD, J-Link over
SWD). On the serial terminal (UART2, 115200) the app prints `hello` byte by
byte through the bootloader's own UART function, and the LED blinks through
the bootloader's `led_toggle`.

## Files

- [bootloader/Src/bootloader.c](bootloader/Src/bootloader.c): the exported
  API table in `.COMMON_APIS`.
- [linkers/STM32F411xC_BOOT.ld](linkers/STM32F411xC_BOOT.ld): pins the table
  at `0x08004000`.
- [app/Src/main.c](app/Src/main.c): the application calling the bootloader's
  functions through the fixed address.
