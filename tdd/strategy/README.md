# Strategy

### Hardware Bottleneck and Dual-Targeting

Embedded development often faces significant delays due to dependencies on
target hardware. Issues like late hardware availability, high costs, scarcity,
hardware bugs, long build/upload times, and expensive compiler licenses can halt
progress. These bottlenecks lead to accumulated unverified code, making
integration and debugging a nightmare when hardware finally arrives.

Dual-targeting involves designing code to run on both the final embedded target
and the host development system from day one. This strategy allows developers to
write and test code continuously, even without hardware. By isolating software
testing from hardware uncertainties, teams avoid the "debugging chaos" that
arises when hardware and software issues intertwine.

Dual-targeting forces a modular design with clear boundaries between
hardware-specific and hardware-independent code. This improves software quality
and maintainability. Additionally, it future-proofs the code: porting to new
hardware becomes easier, and existing unit tests ensure behavior remains
consistent across platforms. This approach transforms potential blockers into
opportunities for robust, portable design.

Teams using dual-targeting report faster development cycles and reduced
debugging time. By testing on host systems first, they catch software bugs
early, leaving only hardware-specific issues for target testing. This practice
not only accelerates development but also enhances collaboration between
hardware and software teams.

Start by identifying hardware-dependent code (e.g., direct register access) and
abstracting it behind interfaces. Use dependency injection (as in the LedDriver)
to substitute hardware interactions with test doubles on the host. Maintain a
strict separation between pure logic and hardware glue code, ensuring most tests
run off-target without sacrificing reliability.

Dual-targeting isn’t just a workaround—it’s a strategic practice that builds
resilience. As hardware evolves, your code adapts effortlessly, supported by a
comprehensive test suite. This approach turns embedded development constraints
into strengths, fostering agility and innovation.

### Risks of Dual-Target Testing

While dual-target testing (running code on both host and target) accelerates
development, it introduces risks due to environmental differences: compiler
variations, library disparities, data type sizes, byte ordering, and alignment
issues. These can cause tests to pass on the host but fail on the target.
Awareness of these pitfalls is crucial—not to discourage dual-targeting, but to
approach it with vigilance and strategies to mitigate risks.

### The Embedded TDD Cycle

To balance speed and reliability, the embedded TDD cycle extends the core TDD
microcycle into five stages. This structured approach ensures code works
correctly across environments while maintaining rapid feedback.

**Stage 1: TDD Microcycle on Host Development System:**
This is the most frequent stage, run every few minutes. Code is written and
tested natively on the host, providing fast feedback without hardware delays.
The focus is on platform-independent code, decoupling logic from hardware
dependencies. Tools can be used for deeper analysis. This stage builds the
foundation but must be complemented by later stages to catch
environment-specific issues.

**Stage 2: Compiler Compatibility Check:**
Periodically compile code with the target cross-compiler to detect
incompatibilities early—such as missing headers or unsupported language
features. This stage should be automated in nightly or continuous integration
builds. It ensures code portability and helps evaluate compiler choices during
toolchain selection.

**Stage 3: Unit Tests on Evaluation Board:**
Run unit tests on an eval board to identify behavioral differences between host
and target processors. This stage catches issues like runtime library bugs or
hardware quirks. Even with reliable target hardware, eval boards can isolate
hardware vs software problems. Automate this in CI to run daily, ensuring
ongoing compatibility.

**Stage 4: Unit Tests on Target Hardware:**
Execute tests on the actual target hardware to validate real-world behavior.
This stage may reveal memory constraints, requiring tests to be split into
suites. It also allows for hardware-specific tests to characterize target
behavior. This step is critical but may be limited by hardware availability
early in the project.

**Stage 5: Acceptance Tests on Target:**
Validate full system functionality with automated and manual acceptance tests on the target. This ensures features work as expected in the final environment. Hardware-dependent code that couldn’t be fully tested automatically must be verified manually here.

Stages 4 and 5 may be impossible early due to hardware unavailability. As the
project progresses, eval board testing (Stage 3) might be reduced if the target
is reliable. However, Stage 1 (host-based TDD) remains the core throughout,
enabling continuous progress regardless of hardware constraints. This flexible,
risk-aware approach ensures robust, portable embedded software.

### Dual-Target Incompatibilities

> The world is real, not ideal.

The embedded world is far from ideal; differences between development and target
environments are inevitable. These disparities—compiler bugs, library
inconsistencies, header file variations, and data handling quirks, can cause code
to behave differently across platforms. Acknowledging and addressing these
issues is crucial for reliable dual-target testing.

A real-world example involved a target compiler’s `strstr()` function, which
incorrectly handled empty strings, a deviation from the standard behavior. This
caused tests to pass on the host but fail on the target. The solution was to
create a platform-specific adapter function, `PlatformSpecificStrStr()`, which
encapsulated the workaround. This approach isolated the fix, maintained clarity
through comments, and ensured consistent behavior across environments.

Header files often differ between platforms, such as the safer `sprintf`
variants: `snprintf` in Unix and `_snprintf` in Windows. Conditional compilation
(e.g., `#ifdef`) can clutter code and reduce readability. Instead, use
platform-specific directories and headers to map functions, leveraging the
compiler and linker rather than preprocessor directives. This keeps code clean
and maintainable.

The adapter pattern is a powerful tool for resolving platform differences. By
defining a common interface (e.g., `PlatformSpecificSprintf`) and implementing
it for each platform, you decouple your code from platform-specific details.
This pattern transforms incompatible interfaces into consistent ones, ensuring
behavior aligns across environments. Tests define the expected behavior, driving
the adapter’s implementation.

Write platform-independent tests to validate adapter functions. For example,
tests for `PlatformSpecificSprintf` should check both success and edge cases
(e.g., buffer overflows). Differences in implementation details (like return
values for truncated output) must be reconciled to meet test expectations, even
if it means modifying one platform’s behavior to match the other.

CI automates builds and tests across platforms, catching issues early. It
requires a single-command build process for both host and target. CI servers
monitor code repositories, trigger builds on changes, and notify teams of
failures. For embedded systems, this means running host tests first, followed by
target tests, ensuring compatibility at every step.

### Testing with Hardware

While TDD and off-target testing build confidence in software logic, hardware
interaction must ultimately be validated on real hardware. Automated tests alone
cannot catch all hardware-related issues, such as incorrect memory mapping,
signal inversion, or physical defects. Testing with hardware ensures the entire
system—software and hardware—works together as intended.

Automated tests can verify hardware functionality when the hardware supports
self-interrogation. For example, a CFI-compliant flash memory device responds to
specific commands with known values. Writing tests that send these commands and
check responses provides a quick sanity check. These tests can be integrated
into CI pipelines and even shipped as built-in diagnostics.

As in Randy Coulman’s story, writing hardware acceptance tests before hardware
is available fosters collaboration between software and hardware teams. These
tests, run against simulations initially and later on real hardware, catch
misinterpretations of specs, compiler issues, and FPGA regressions. Automated
builds that run these tests give hardware engineers confidence in their changes,
even during off-hours.

Some tests require human observation, such as verifying that the correct LED
lights up. Partially automated tests prompt operators to check physical outputs.
These tests are costly but necessary for validating hardware-dependent code.
They should be run sparingly—triggered by hardware changes or major software
updates—to minimize manual effort while ensuring correctness.

Specialized test equipment can automate complex hardware validation. Dee’s story
shows how controlling instruments via scripts (e.g., serial commands to a T1
signal generator) enables comprehensive testing of error conditions and
real-world scenarios. This approach transforms tedious manual tests into
repeatable, automated regressions, catching defects early and improving overall
quality.

### The Long-Term Value of TDD

Adopting Test-Driven Development in embedded systems presents unique challenges,
from hardware dependencies to cross-platform issues. However, these hurdles are
outweighed by the long-term benefits. TDD encourages a methodical, disciplined
approach that ultimately accelerates development and enhances quality, even if
it initially feels slower.

TDD may seem to slow progress initially, as it requires careful planning, test
writing, and refactoring. However, this deliberate pace prevents costly
debugging sessions, rework, and integration nightmares later. By catching errors
early and maintaining clean code.

TDD prioritizes quality through continuous verification. Each test validates a
small behavior, creating a comprehensive documentation suite that remains
relevant through hardware and software changes. This focus on quality reduces
defects, enhances reliability, and builds trust in the system.