# Cpp

C++ works fine on a Cortex-M, but the build and the language subset need
care: the compiler changes, the runtime library is not free anymore, and some
features quietly pull in code that has no place in a microcontroller. This
module is a minimal blinky in C++ showing exactly what has to change.

## The idea

The C++ side is a `Led` class whose constructor initializes the hardware, and
register addresses live in a namespace instead of macros:

```cpp
namespace mcal { namespace reg {
    const std::uint32_t gpioa = 0x40020014;
    const std::uint32_t gpio_pin5 = 5;
}}

Led led5(mcal::reg::gpioa, mcal::reg::gpio_pin5);
led5.toggle();
```

Casting a literal address to a pointer becomes explicit with
`reinterpret_cast<volatile port_type*>`, which is C++ making visible what C
hides behind a cast.

In the build, three things change:

- `main.cpp` is compiled with `arm-none-eabi-g++`, while `startup.c` stays
  with `gcc`. Mixing works because both follow the same ABI.
- The link uses `-nostdlib`: no libstdc++, no C++ runtime. The program only
  gets what it wrote.
- The startup code never touches `.init_array`, so constructors of global
  objects would silently not run. The demo dodges this by keeping `led5`
  local to `main()`, where construction happens on entry like any local
  variable.

## What to avoid

With `-nostdlib` the rule is simple: any feature that needs runtime support
is out. Exceptions and RTTI drag in unwinding tables and type info, `new` and
`delete` need a heap, and global constructors need startup support that is
not wired here. What remains (classes, namespaces, templates, `constexpr`,
references) costs the same as the equivalent C and is the part worth using.

## Build and run

STM32F411 (LED on PA5). `make` builds `Build/flash.elf`, `make load` flashes
it through OpenOCD with an ST-Link. The LED blinking is the whole output.

## Files

- [Src/main.cpp](Src/main.cpp): the `Led` class and the register casts.
- [Inc/mcal_reg.h](Inc/mcal_reg.h): register addresses as namespaced
  constants.
- [Makefile](Makefile): the mixed gcc/g++ build with `-nostdlib`.
