# Test Doubles

### Collaborators

So far, we've focused on testing self-contained code without dependencies.
However, most real-world code consists of modules that depend on other
functions, modules, or hardware devices. These dependencies make testing more
challenging because the code under test must work through collaborators to
perform its functions.

A collaborator is any external dependency that the code under test interacts
with. Even seemingly standalone modules like the LedDriver have collaborators -
in this case, the memory-mapped I/O address. During testing, we replace actual
hardware with test doubles like virtualLeds, which impersonate the real
collaborator while allowing us to monitor the code's behavior.

Test doubles (such as stubs) temporarily replace production collaborators during
testing. While developers often view stubs as temporary solutions, in TDD they
become permanent fixtures that enable automated unit testing throughout the
code's lifecycle. The code under test interacts with these doubles exactly as it
would with real collaborators, making comprehensive testing possible without
actual dependencies.

### Stub or Mock

In software testing, a stub provides pre-determined responses for methods or
objects to control the test's flow and simplify it, while a mock verifies that
specific interactions (like method calls with correct parameters) occurred
during the test. You use a stub when you need a component to return specific
data to test your code's behavior, and a mock when you need to check how your
code interacted with a dependency. 

### Breaking Dependencies

Real-world code typically depends on other modules, operating systems, or
hardware devices, making automated testing difficult. These dependencies can
resist testing when they're hard to control or unpredictable. The solution lies
in designing testable code through rigorous use of interfaces, encapsulation,
and data hiding, rather than relying on unprotected global data.

We should use the real production collaborators when possible, but test doubles
become necessary when collaborators interfere with automated testing. This
occurs when we need precise control over behavior - such as simulating network
failures at specific moments during message sequences. Test doubles allow us to
create repeatable test scenarios that would be impossible or impractical with
real collaborators.

Without test doubles, testing becomes complex as test cases must manage all
direct and transitive dependencies, leading to fragile tests that break with
design changes. Test doubles act as substitutes for real collaborators,
simplifying tests by eliminating dependency chains. They provide controlled
inputs to the code under test and capture outputs for verification, while
remaining much simpler than the actual components they replace.

### Use of Test Doubles

The fundamental rule for test doubles is to use real production code whenever
possible, and only resort to test doubles when necessary. For example, if your
code uses a linked list, test with the actual linked list implementation rather
than creating a fake one. The test can then verify that the code correctly
manipulates the real data structure.

Test doubles become essential in specific situations: 

1) Achieving hardware independence for testing without physical devices.
2) Injecting difficult-to-produce inputs to trigger rare execution paths.
3) Replacing slow collaborators like databases to maintain test speed. 
4) Controlling volatile dependencies like system clocks for reproducible tests. 
5) Working with unfinished components during concurrent development. 
6) Avoiding complex configuration requirements of certain dependencies.

Using test doubles isn't an all-or-nothing decision. Most tests will use a
combination of real collaborators and test doubles, and the same code might use
different configurations for different test scenarios. This flexible approach
allows for comprehensive testing while maintaining practical constraints.

### Faking It in C

C offers only three fundamental techniques for implementing test doubles: linker
substitution, function pointer substitution, and preprocessor substitution. Each
method serves different purposes and has specific use cases. Understanding when
to apply each technique is crucial for effective testing in C environments.

Link-time substitution replaces an entire module for testing purposes. This
approach is ideal when you need to substitute hardware-dependent modules,
third-party libraries, or operating system dependencies for off-target testing.
It's particularly useful when you don't control the interface of the module
being replaced. However, if you need to test the actual module itself, you'll
require a separate test executable without the test double.

Function pointer substitution provides precise control by allowing you to
replace specific functions for individual test cases. While this method offers
great flexibility, it comes with trade-offs: increased complexity, RAM usage,
and potential impacts on function declaration readability. This technique works
best when you control the interface and need selective replacement of functions
rather than whole modules.

Preprocessor substitution should be used sparingly, only when other methods
won't work. It can break unwanted include chains or temporarily override
function names, as demonstrated by CppUTest's memory allocation monitoring.
However, this technique fundamentally changes the compiled code and has
widespread effects. Whenever possible, consider wrapping problematic code with a
controllable interface instead of using preprocessor substitution.

You can combine link-time and function pointer substitution for enhanced
flexibility. This hybrid approach uses link-time stubs containing function
pointers that can be dynamically overridden by test cases. This provides the
control of function pointers without requiring interface changes to the
depended-on components, offering a powerful solution for complex testing
scenarios.