# Design Patterns

A design pattern is a reusable solution to a problem that appears frequently in software development. Instead of solving the same problem from scratch every time, you recognize the pattern of the situation and apply a well-known, tested solution.

In embedded C, design patterns are especially valuable because they bring structure and predictability to systems that grow in complexity over time. They also improve communication: when you say "I used the Strategy pattern here", another programmer already understands the intent without reading every line of code.

## How this section relates to Optimised Patterns

This section and [Optimised Patterns](../OPTIMISED_PATTERNS/) overlap on purpose.
Here each pattern appears in its canonical form: the structure, the intent, and a
clean implementation in C. The optimised section revisits several of the same
patterns with embedded constraints in mind, such as memory cost and deterministic
behavior. Start here to understand a pattern, then check the optimised version
before applying it on a real target.

## Anatomy of a Pattern

Every pattern is documented with four elements:

- **Name**: the identifier used to communicate the pattern between programmers
- **Purpose**: the problem it solves
- **Solution**: how to implement it
- **Consequence**: the trade-offs and side effects of using it

Understanding the *consequences* is just as important as understanding the solution. Every pattern has a cost, and applying it in the wrong place creates more problems than it solves.

## Patterns

1. **[ADT](adt/)** - Abstract Data Type
2. **[Bit Fields](bit_fields/)**
3. **[State](state/)**
4. **[Hardware Proxy](hardware_proxy/)**
5. **[Strategy](strategy/)**
6. **[Hardware Adapter](hardware_adapter/)**
7. **[Client-Server](client_server/)**
