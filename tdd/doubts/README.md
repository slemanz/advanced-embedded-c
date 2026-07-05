# Doubts

### We Dont Have Time

A common objection to TDD is the perceived lack of time. Developers worry that
writing tests will slow them down, especially when production code already feels
behind schedule. However, this view often overlooks the time spent on debugging
and fixing bugs later. TDD may require more initial code (like the LedDriver,
which had more test lines than production code), but it reduces overall effort
by catching errors early.

Proficient TDD practitioners report that it speeds them up by reducing debug
time and maintaining a cleaner codebase. If you currently spend about 50% of
your time testing and debugging (as many conference attendees report), TDD
offers a proactive alternative. Instead of reacting to bugs, you prevent them,
trading reactive debug time for proactive test writing.

Manual testing has a low initial investment but offers almost no future return.
Every code change requires re-running manual tests, which is time-consuming and
often incomplete. TDD automates this process, ensuring tests are run
consistently and thoroughly with each change, saving time in the long run.

Many developers write custom test harnesses (e.g., a test `main()` with stubs)
for new code. While helpful initially, these tests often fall into disrepair
after integration. They become incompatible and are discarded, offering a poor
return on investment. Structured test harnesses like CppUTest or Unity require
less effort and provide lasting value.

Debugging by single-stepping through code is slow, non-repeatable, and tedious.
Any code change invalidates previous efforts, requiring you to start over. This
method is error-prone and unsustainable as the codebase grows, leading to missed
bugs and increased future effort.

Some organizations have elaborate, documented unit test processes with reviews
and plans. While this feels rigorous, it is often inefficient. Tests are manual,
repetitive, and boring, leading to shortcuts and bugs. Automation, as in TDD,
provides better documentation and continuous value with less overhead.

You are already investing time in unit testing—whether through ad hoc methods,
custom harnesses, or manual processes. These approaches have high costs and
limited payback. TDD shifts this investment into automated, evolving tests that
run with every change, offering repeated returns and reducing debug time.

TDD may seem slower initially, but it accelerates development by ensuring
quality and reducing bugs. By automating tests, you save time otherwise spent on
debugging and manual re-testing, making TDD a wise long-term investment.

### Write Tests After the Code

Test-Driven Development (TDD) requires writing tests *before* production code,
fundamentally shaping the design process. In contrast, Test-After Development
writes tests *after* the code is complete. While Test-After still provides some
benefits, it misses key advantages that TDD offers. TDD is not just about
testing; it is a design and development discipline that influences the entire
software structure.

TDD leads to better-designed code with improved APIs, more cohesive modules, and
looser coupling because the tests act as the first user of the code. This design
influence is minimal in Test-After Development. Additionally, TDD catches small
mistakes immediately during development, preventing defects from ever reaching
the bug database. Test-After may find some issues, but it allows more errors to
escape detection, leading to future debugging efforts.

With TDD, test failures are immediately linked to the most recent change, making
root cause analysis straightforward. In Test-After Development, failures require
hunting through existing code to find the source, wasting valuable time. TDD
also naturally results in comprehensive and rigorous test coverage tailored to
the code's requirements, whereas Test-After often leads to gaps in coverage and
less effective tests.

### Unit Tests Don’t Find All the Bugs

TDD ensures that each individual unit of code—each "building block", behaves
exactly as intended. While it cannot catch every possible bug, it creates a
reliable foundation by verifying that every line of code meets expectations.
This precision at the unit level is crucial for constructing complex systems
that function correctly.

TDD is not a substitute for other testing types. Integration tests, acceptance
tests, exploratory tests, and load tests are still essential. These higher-level
tests focus on broader issues: integration problems, requirement validation, and
system performance. TDD reduces unit-level defects, allowing these other tests
to uncover more appropriate and complex issues rather than being bogged down by
simple coding errors.

Small errors, like a single typo, can lead to significant and hard-to-find bugs
in complex systems. TDD catches these mistakes immediately during development,
preventing them from evolving into larger issues. While not foolproof, TDD is
highly effective at minimizing wasted effort and ensuring that changes have only
their intended consequences.

### We Have a Long Build Time

A core requirement for Test-Driven Development is a rapid edit/build/test cycle,
ideally measured in seconds. However, large embedded projects often suffer from
build times that take hours, which is incompatible with the TDD rhythm. This
doesn't mean abandoning TDD but rather adapting the build process to support it.

The solution is to avoid building the entire system for TDD. Instead, create
multiple smaller unit test builds that compile only specific parts of the
system. This approach leverages the existing modular structure of your project
(libraries, components, subsystems) and uses tailored makefiles or build targets
to generate focused test executables quickly.

The main obstacle to creating these smaller test builds is often the codebase
itself. A common antipattern where data structures and function calls are
tightly entangled across the system ("free-for-all") makes isolation difficult.
Overcoming this requires techniques for breaking dependencies, which will be
essential for enabling effective TDD in complex embedded systems.

### We Have Existing Code

Most developers work with existing code that has few or no automated unit tests.
This does not prevent you from starting TDD. The key insight is that you don't
need to write tests for the entire codebase at once—this would be impractical
and halt development.

The recommended strategy is to incrementally add tests while continuing to
deliver new functionality. This involves four practical techniques: using TDD
for all new code you write, adding tests whenever you modify existing code,
writing tests to cover bug fixes, and proactively investing in strategic tests
for critical components.

This approach allows you to gradually improve your codebase's test coverage
without disrupting ongoing development. By focusing on areas you're actively
working on, you systematically build a safety net that makes future changes
safer and more predictable.

### We Have Constrained Memory

Embedded systems often have severe memory constraints that aren't present in
development environments. To effectively practice TDD under these conditions,
use dual-targeting to test most code off-target, select a minimal test harness
like Unity, create a lab version with expanded memory, and organize tests into
multiple smaller runners that fit within memory limits.

Track target memory usage systematically. For example, if your system has 1MB of
flash, use your continuous integration system to build the binary and generate a
map file. A simple script can extract memory consumption data from this file,
allowing you to monitor usage patterns over time.

Display memory usage trends on a Big Visible Chart (BVC) that the entire team
can see. This visual tracking helps identify unexpected spikes 
and enables quick investigation of changes that caused increased
memory consumption. You can also set memory budgets for each iteration and
configure builds to fail when exceeding these limits, ensuring immediate
attention to resource issues. This approach works for tracking any critical
resource like RAM, CPU idle time, or I/O data rates.

### Interact with Hardware

Tests that interact with hardware can be effectively written and run off-target.
The LedDriver example demonstrated how to verify that code meets our
understanding of hardware specifications without requiring actual hardware.
While this doesn't guarantee hardware compatibility, it ensures the logic is
sound. Any hardware misunderstandings discovered during integration can then be
corrected in both production code and tests.

Many drivers involve more complex hardware interactions than the LedDriver. For
these cases, we use test doubles (stubs and mocks) to simulate hardware
behavior. This approach allows comprehensive testing of software-hardware
interactions without physical hardware, making it practical to test complex
scenarios thoroughly.

We can treat time as a function call, allowing us to control and test
time-dependent code effectively. When working close to hardware (like device
drivers), we use mocks to simulate specific interaction sequences rather than
building full simulators. This targeted simulation approach is far less complex
than full hardware simulation while remaining highly effective for testing
critical hardware interactions.

### C++ Test Harness for Testing C

C-only test harnesses like Unity require a multi-step process to install test
cases, making it easy to forget to install tests. This creates a risk where
tests appear to pass simply because they weren't run. The manual installation
process also makes test refactoring difficult, as changes require updates in
multiple places.

CppUTest uses C++ features to automatically install tests through file-scope
object initialization. The TEST() macro creates a C++ object whose constructor
installs the test into a global list before main() runs. This eliminates manual
test registration and ensures no tests are accidentally omitted.

Using a C++ test harness for C code provides additional advantages: it helps
identify portability issues when compiling with different compilers, reduces
resistance to C++ adoption, and offers conversion tools to Unity for target
execution if needed. The automated approach encourages better testing practices
and reduces maintenance overhead.