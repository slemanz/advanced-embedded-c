# Abstract Data Type (ADT)

An Abstract Data Type defines a data structure by its **behavior**, not by its internal representation. It specifies what operations exist and what they do, but completely hides how the data is stored in memory and how the operations are implemented.

> ADT tells you *what* you can do with the data. It does not tell you *how* it is done internally.

The key benefit is **encapsulation**: the user of the ADT only sees a clean interface and cannot accidentally depend on internal details. This makes it safe to change the implementation later without breaking any code that uses it.

## The Opaque Pointer Technique in C

C does not have classes, but you can achieve the same encapsulation using a forward-declared struct combined with an opaque pointer.

The trick: declare a pointer to a struct in the header file, but define the struct itself only in the source file. The compiler knows the type exists, but the caller never sees its fields.

**In the header file (`device.h`):**

```c
typedef struct Device* DevicePtr;
```

This says "there is a type called `DevicePtr` that is a pointer to a `Device` struct." Any caller can hold and pass a `DevicePtr`, but cannot access its fields because the struct definition is hidden from them.

**In the source file (`device.c`):**

```c
struct Device {
    const char *name;
    Address address;
    deviceID_t uuid;
};
```

The struct fields are only visible inside `device.c`. Any other file that includes `device.h` can use `DevicePtr` but cannot read or write the fields directly. This is enforced by the compiler.

## Summary

| What the caller sees | What the caller cannot see |
|---|---|
| The `DevicePtr` type | The fields inside `Device` |
| The public functions in `device.h` | How those functions work internally |

## Implementation Example

- [main.c](App/Src/main.c)
- [device.h](App/Inc/device.h)
- [device.c](App/Src/device.c)
