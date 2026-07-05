# Tools

### The Power of Automation and Unit Testing

Automating manual procedures not only eliminates the boredom and errors of
repetitive tasks but also enhances creativity by freeing your mind to focus on
more innovative work. Test-Driven Development (TDD) leverages automation by
allowing tests to run independently once defined. Unity (for C) and CppUTest
(C++-based but usable without C++ knowledge), These frameworks help structure
test cases, define expected results, and generate detailed reports, ensuring
reliable and repeatable validation of production code.

### Understanding Unit Test Harnesses

A unit test harness is a tool that helps programmers define and execute test
cases efficiently. Key features include:

- A standardized way to write tests and expected outcomes.
- Integration with the production code’s programming language.
- Batch execution of tests with clear success/failure reports.
- Support for test fixtures (setup/teardown environments) and test cases (specific
behavior checks).

For example, testing a simple function like sprintf() (a stand-alone function
with no hidden state) illustrates core concepts:

- Code under test: The function being tested (e.g., sprintf).
- Production code: The actual code shipped to users.
- Test code: The validation logic (not shipped).

By automating these tests, developers ensure consistent behavior while
minimizing manual effort.

### Unity Framework

A unit test harness like Unity provides the structure and tools to write
automated tests for your C code. The core building block is the `TEST` macro,
which defines an individual test case. Each test uses assertion macros like
`TEST_ASSERT_EQUAL` or `TEST_ASSERT_EQUAL_STRING` to verify that the code under test
behaves as expected; if any assertion fails, the test fails and reports the
specific error. To write effective tests, you must not only check for correct
behavior but also for potential errors, such as buffer overruns. This is done by
initializing memory with a known value (e.g., `0xaa`) and then checking that bytes
outside the expected output remain unchanged.

As the number of tests grows, code duplication (like repeated setup and checks)
becomes a problem. This is solved by using a test fixture, created with the
`TEST_GROUP`, `TEST_SETUP`, and `TEST_TEAR_DOWN` macros. The `TEST_SETUP` function runs
before each test in the group, initializing a common environment (like a shared
output buffer), which eliminates duplication and makes each test "lean, mean,
and to the point." Tests are organized into a Test Runner (`TEST_GROUP_RUNNER`)
that calls each test case, and a `main()` function that executes all runners. When
all tests pass, the output is succinct ("OK"), but any failure produces a
detailed report showing the exact test, line number, and reason for the failure,
which is crucial for quickly diagnosing problems.

Key Terminology Cheat Sheet:

- `TEST(group, name)`: The macro to define a single test case.

- `Assertion Macros`: Tools to check conditions (e.g., TEST_ASSERT_EQUAL(expected,
actual)).

- `Test Fixture`: The environment for a test, including shared data and
setup/teardown routines (TEST_GROUP, TEST_SETUP, TEST_TEAR_DOWN).

- `Buffer Overrun`: A critical error where code writes past the end of allocated
memory; tests should guard against this.

- `Test Runner (TEST_GROUP_RUNNER)`: The code that orchestrates and executes all the
test cases in a group.

- `Test Output`: A concise report ("OK") for success and a detailed, helpful
message for any failures.

**Example:**

- [SprintfTest.c](unity_example/tests/SprintfTest.c)
- [SprintfTestRunner.c](unity_example/tests/SprintfTestRunner.c)
- [Makefile](unity_example/Makefile)

### CPPUTest Framework

CppUTest is a versatile unit test harness designed for both C and C++
development, with a specific focus on embedded systems. Its key advantage is
that it uses a simple subset of C++, allowing programmers to write tests using
clear macros **without needing to know C++**. This makes it highly accessible
for C developers. While the macros have different names (e.g., `LONGS_EQUAL`
instead of `TEST_ASSERT_EQUAL`), the structure and logic of writing test cases
and fixtures are nearly identical to Unity, making it easy to switch between the
two.

The most significant practical advantage of CppUTest is that it
**self-installs**. Unlike Unity, which requires you to manually wire tests into
a runner, CppUTest automatically discovers and runs your tests. This eliminates
the tedious and error-prone process of maintaining `TEST_GROUP_RUNNER` and
`RUN_TEST_GROUP` code, reducing the risk of tests being compiled but not
executed.

### **Key Comparisons and Concepts:**

| Feature | Unity (C) | CppUTest (C++) | Didactic Note |
| --- | --- | --- | --- |
| **Test Case**         | `TEST(group, name)`           | `TEST(group, name)`           | The structure is identical.                           |
| **Assertion**         | `TEST_ASSERT_EQUAL`           | `LONGS_EQUAL`                 | Functionally the same, different names.               |
| **Fixture Setup**     | `TEST_SETUP(group)`           | `void setup()`                | `setup()` is automatically called before each test.   |
| **Fixture Teardown**  | `TEST_TEAR_DOWN(group)`       | `void teardown()`             | `teardown()` is automatically called after each test. |
| **Test Registration** | Manual (in Runner)            | **Automatic**                 | **CppUTest's biggest advantage:** no manual wiring.   |
| **Output on Success** | `OK`                          | `OK`                          | Both are succinct.                                    |
| **Output on Failure** | Detailed (file, line, reason) | Detailed (file, line, reason) | Both provide excellent debugging info.                |

**Core Idea:** The principles of unit testing—writing focused tests, using
assertions, and organizing code with fixtures to avoid duplication—are
universal. CppUTest implements these principles in a way that is more automated
and convenient, especially for larger projects. Choosing between Unity and
CppUTest often comes down to personal preference or project constraints, but
CppUTest's automatic test registration is a major productivity booster.

### Unit Tests Can Crash

Unit tests don't just fail with a clear error message; they can also crash or
fail silently. This is especially true in C, where undefined behavior (like a
buffer overrun in sprintf) can cause the test runner to exit unexpectedly. When
this happens, the output is often useless because the crash prevents the harness
from reporting the failure.

**How to Debug a Crashing Test:**

1.  **Use Verbose Mode:** Run the test harness with the `-v` (verbose)
command-line option. This makes each test print its name *before* it runs. The
last test name you see is the one that crashed.

2.  **Filter Tests:** Use command-line options like `-g [groupname]` to run a
specific test group or `-n [testname]` to run a single test. This isolates the
problem, making it much easier to find.

### **The Four-Phase Test Pattern: A Blueprint for Clarity**

To write tests that are easy to read, understand, and maintain, follow the
**Four-Phase Test** pattern. This structure acts as a recipe for every test you
write:

| Phase | Goal | What It Does |
| --- | --- | --- |
| **1. Setup**      | Create the preconditions  | Initialize variables, create objects, set up the test environment. |
| **2. Exercise**   | Interact with the system  | Call the function or method you are testing. |
| **3. Verify**     | Check the outcome         | Use assertion macros to confirm the result is what you expected. |
| **4. Cleanup**    | Restore the initial state | Deallocate memory, close files, reset globals. (Often handled automatically by the test fixture's `teardown`). |

**Why it matters:** Following this pattern makes your tests self-documenting.
Anyone reading your test can immediately see what is being tested and what the
expected behavior is. Breaking this pattern makes tests harder to debug and
understand.


