# Testing Your Way

### Completing the LED Driver Through Incremental TDD

We continue developing the LedDriver from where we left off: with a skeletal
structure, a defined interface, and three passing tests. The goal is to grow the
implementation incrementally, one test at a time, ensuring each step is verified
before moving forward. This steady rhythm is the essence of TDD.

The next test, TurnOnMultipleLeds, turns on LEDs 8 and 9 and expects virtualLeds
to be 0x180. This fails because the current implementation only handles a single
LED. The solution involves bit manipulation: *ledsAddress |= (1 << (ledNumber -
1));. However, an off-by-one error (shifting too much) causes failures in
existing tests. This error is caught immediately, demonstrating TDD’s power to
detect issues early. Fixing it (subtracting 1 from ledNumber) restores
stability.

With tests passing, we refactor the bit manipulation into a helper function,
convertLedNumberToBit(), to improve readability. This follows the TDD cycle:
after making a test pass, we improve the code without changing behavior.

The test TurnOffAnyLed initially fails because the simple TurnOff implementation
turns off all LEDs. To properly test masking (turning off one LED without
affecting others), we first implement TurnAllOn (using 0xffff) and refactor
magic numbers into enums (ALL_LEDS_ON, ALL_LEDS_OFF). Then, TurnOff uses bitwise
AND with the complement of the LED bit: `*ledsAddress &= ~(convertLedNumberToBit(ledNumber));`.

We learn the hardware LEDs are write-only, meaning the driver cannot read their
state. To simulate this, we introduce ledsImage, a private variable that mirrors
the LED states. All operations now update ledsImage and write it to virtualLeds
via a new updateHardware() function. This ensures the driver works correctly
regardless of hardware readability.

Tests for upper/lower bounds (TurnOn(1) and TurnOn(16)) pass easily. However,
out-of-bounds values (e.g., -1, 0, 17) cause unexpected behavior due to bit
shifting quirks. We add **guard clauses** in TurnOn and TurnOff to ignore invalid
inputs, ensuring safety.

We discover that the guard clause in TurnOff was untested. We rename tests to be
specific (e.g., OutOfBoundsTurnOnDoesNoHarm) and add
OutOfBoundsTurnOffDoesNoHarm, which turns all LEDs on first to verify that
TurnOff doesn’t alter valid states. This reinforces the rule: never let
production code get ahead of tests. Always write a test for each new behavior.

For better error handling, we use a `RUNTIME_ERROR()` macro to log out-of-bounds
accesses. During tests, a stub captures the error message and parameters,
allowing verification. The test OutOfBoundsProducesRuntimeError checks that
calling TurnOn(-1) triggers the expected error.

For unresolved questions, we use `IGNORE_TEST` to create executable reminders.
These tests compile but don’t run, serving as TODOs that appear in test outputs.
For example, `IGNORE_TEST(LedDriver, OutOfBoundsToDo)` prompts future action
without breaking the build.

### Keep Code Clean

Always refactor **only when all tests are passing**. This is your safety net.
Refactoring on green ensures that any structural changes you make don’t
accidentally break existing functionality. If tests are failing, you lack the
stability to safely improve the code.

Refactoring addresses code "smells" like duplication and magic numbers early,
preventing them from evolving into larger problems. In the LedDriver, functions
like `TurnOn` and `TurnOff` had duplicated logic for bounds checking and bit
manipulation. By refactoring, we eliminate this duplication, making the code
more maintainable and less error-prone.

When extracting a new helper function (e.g., `IsLedOutOfBounds`), **copy the
code first—don’t cut it**. Define the new function, paste the code, and adjust
parameters and return types. Compile to ensure syntax correctness. Once it
works, replace the original code with a call to the new function. This approach
keeps you one undo away from working code if something goes wrong.

Magic numbers (like `1` and `16` for LED bounds) obscure meaning. Replace them
with named constants (e.g., `FIRST_LED`, `LAST_LED`) to improve readability and
centralize changes. This makes the code self-documenting and easier to modify.

Extract helper functions to match the abstraction level of the calling code. For
example, `setLedImageBit` and `clearLedImageBit` hide the complex bit
manipulation details, making `TurnOn` and `TurnOff` more readable and focused on
their high-level goals.

Refactoring in small, incremental steps reduces risk. Change one caller at a
time to a new helper function, and verify tests pass after each change. If a
test fails, **undo immediately** rather than debugging. This minimizes confusion
and keeps you in a known good state.

Duplicate code is a primary source of bugs. When the same logic appears in
multiple places, a change in one spot must be replicated everywhere—a
error-prone process. By centralizing logic into single functions, you ensure
consistency and reduce future maintenance effort.

Tips:

- Use `static` helper functions to avoid polluting the global namespace.
- Compile frequently to catch syntax errors early.
- If a refactoring breaks tests, revert and reassess rather than pressing forward.
- Keep functions small and focused on a single responsibility.

**LED Driver Tests:**

- ~~All LEDs are off after the driver is initialized.~~
- ~~A single LED can be turned on.~~
- ~~A single LED can be turned off.~~
- Multiple LEDs can be turned ~~on~~/off.
- ~~turn on all LEDs~~
- Turn off all LEDs
- Query LED state
- ~~Check boundary values~~
- Check out-of-bounds values
    - ~~Beyond max breaks nothing~~
    - ~~Under min breaks nothing~~
    - ~~Runtime Error~~
    - What should really happen?
- ~~Hardware interaction~~

### Repeat until Done

As you progress in TDD, your test list evolves. Completed tests are checked off,
and new tests are added as your understanding deepens. This is natural—TDD is a
learning process. The goal is to systematically address each requirement until
the module is complete.

The next feature is querying LED states with `LedDriver_IsOn()`. Since the
hardware is write-only, the driver internally tracks state via `ledsImage`. The
test first checks that an LED is off, turns it on, and verifies it is on. After
adding the function prototype and a failing implementation (`return FALSE;`),
you implement the logic: `return ledsImage & (convertLedNumberToBit(ledNumber));`.

Duplicate code violates the **DRY (Don’t Repeat Yourself)** principle. For
example, bounds checking appeared in multiple functions. Centralizing this into
`IsLedOutOfBounds()` reduces maintenance risk and improves readability.
Performance concerns are secondary; prioritize clean design unless profiling
proves otherwise.

For `LedDriver_IsOn()`, out-of-bounds LEDs should return `FALSE` (off). To
validate the test, temporarily hardcode `return TRUE;` and watch it fail. Then
add the guard clause: `if (IsLedOutOfBounds(ledNumber)) return FALSE;`. This
ensures robustness.

Instead of duplicating logic, implement `LedDriver_IsOff()` by reusing
`LedDriver_IsOn()`: `return !LedDriver_IsOn(ledNumber);`. However,
**always write tests first**, even for seemingly simple functions. Test both
normal and out-of-bounds cases to ensure correctness.

The tests `TurnOffMultipleLeds` and `AllOff` leverage existing functions.
`TurnOffMultipleLeds` turns on all LEDs, turns off two, and checks the result.
`AllOff` turns all LEDs on and then off, verifying the state. These tests pass
without new code because the implementation is already generalized—a sign of
good design.

After implementing all tests, step back and review. Ensure:
- All requirements are met.
- Tests cover normal, edge, and error cases.
- Code is clean and free of duplication.
- Documentation (via test names) is clear.

TDD isn’t just about passing tests—it’s about creating maintainable,
well-documented code. By methodically addressing each test, you build a reliable
system incrementally. The LedDriver is now complete, with all features
implemented and verified.

### The Final Review

Before declaring a module complete, always step back to review the code and
tests for cleanliness and completeness. In the LedDriver, the production code is
in good shape: functions are short, names are clear, and magic numbers have been
eliminated. However, some magic numbers remain in the test code. This is a
conscious trade-off—keeping these values visible in tests can enhance
readability and serve as direct documentation of the expected behavior. The
decision to refactor further is a judgment call based on whether the code's
clarity or maintainability is at risk.

As the design evolved, so did the testing strategy. Early tests relied on
checking the raw `virtualLeds` variable, while later tests used the higher-level
query functions like `IsOn` and `IsOff`. This shift suggests an opportunity to
refactor tests for consistency, perhaps using query functions more broadly.
However, it remains crucial to retain some tests that verify the exact bit
patterns written to the hardware, ensuring low-level correctness. The balance
between these approaches depends on the project's needs and the team's
standards. 

This LedDriver example provided a hands-on look at TDD in action. The test list
evolved naturally, with new tests added as understanding deepened and others
completed or adjusted. This adaptability is a strength of TDD, allowing you to
respond to insights gained during development. 

TDD requires discipline, but over time, the rapid feedback and confidence it
provides become addictive, transforming how you approach coding and design.

### Code

- **[LedDriver.h](inc/LedDriver.h)**
- **[LedDriver.c](src/LedDriver.c)**
- **[LedDriverTests.c](tests/LedDriverTests.c)**
- **[AllLedDriverTests.c](tests/AllTestRunner.c)**

Others:

- **[RuntimeError.h](inc/util/RuntimeError.h)**
- **[RuntimeErrorStub.h](mocks/RuntimeErrorStub.h)**
- **[RuntimeErrorStub.c](mocks/RuntimeErrorStub.c)**