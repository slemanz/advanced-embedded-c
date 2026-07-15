# Design Patterns

A design pattern is a reusable solution to a problem that appears frequently in software development. Instead of solving the same problem from scratch every time, you recognize the pattern of the situation and apply a well-known, tested solution.

In embedded C, design patterns are especially valuable because they bring structure and predictability to systems that grow in complexity over time. They also improve communication: when you say "I used the Strategy pattern here", another programmer already understands the intent without reading every line of code.

## How this section relates to Optimized Patterns

This section and [Optimized Patterns](../optimized-patterns/) overlap on purpose.
Here each pattern appears in its canonical form: the structure, the intent, and a
clean implementation in C. The optimized section revisits several of the same
patterns with embedded constraints in mind, such as memory cost and deterministic
behavior. Start here to understand a pattern, then check the optimized version
before applying it on a real target.

## Anatomy of a Pattern

Every pattern is documented with four elements:

- **Name**: the identifier used to communicate the pattern between programmers
- **Purpose**: the problem it solves
- **Solution**: how to implement it
- **Consequence**: the trade-offs and side effects of using it

Understanding the *consequences* is just as important as understanding the solution. Every pattern has a cost, and applying it in the wrong place creates more problems than it solves.

## Patterns

1. **[ADT](adt/)**: an abstract data type behind an opaque pointer, so callers
   see operations but never the struct internals.
2. **[Bit Fields](bit-fields/)**: packing flags into exact bits, and why the
   implementation-defined layout keeps this away from hardware registers.
3. **[State](state/)**: the same state machine three times (conditional,
   table-based, state pattern), with a comparison of the trade-offs.
4. **[Hardware Proxy](hardware-proxy/)**: a struct that encapsulates all access
   to a device (a motor here), hiding its physical interface.
5. **[Strategy](strategy/)**: a family of interchangeable algorithms selected at
   runtime through function pointers.
6. **[Hardware Adapter](hardware-adapter/)**: converting between the interface
   the application expects and the one the hardware provides, with two sensor
   front ends behind one oximetry interface.
7. **[Client-Server](client-server/)**: modules decoupled into clients and a
   server, demonstrated with an ECG processing chain.
8. **[Publisher-Subscriber](publisher-subscriber/)**: consumers registering
   callbacks with a producer that never learns who they are, also known as
   observer.
