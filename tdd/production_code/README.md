# Production Code

### Test Doubles Variations

- Test Dummy: Keeps the linker from rejecting your build. A dummy is a simple
stub that is never called.  It is provided to satisfy the complier, linker, or
runtime dependency.

- Test Stub: Returns some value, as directed by the current test case.

- Test spy: Captures the parameters passed from the CUT so the test can verify
that the correct parameters have been passed to the CUT. The spy can also feed
return values to the CUT just like a test stub.

- Mock object: Verifies the functions called, the call order, and the parameters
passed from the CUT to the DOC. It also is programmed to return spe- cific
values to the CUT. The mock object is usually dealing with a situation where
multi- ple calls are made to it, and each call and response are potentially
different.

- Fake object: Provides a partial implementation for the replaced component. The
fake usually has a simplified implementation when compared to the replaced
implementation.

- Exploding fake: Causes the test to fail if it is called.

### Testing Hardware-Dependent Code

Modules like the LightScheduler in home automation systems typically have
transitive dependencies on hardware and operating systems through abstraction
layers. These dependencies make testing difficult because they tie the code to
specific execution environments. The solution involves creating defined
interfaces that all environment access must pass through, allowing test doubles
to intercept and control these interactions.

The test case and test doubles together form a software test fixture that
surrounds the Code Under Test (CUT). The test case acts as the client driving
direct inputs, while test doubles impersonate the Depended Upon Components
(DOCs), monitoring outputs and providing controlled indirect inputs. This
approach allows comprehensive testing without actual hardware or OS
dependencies.

Hardware abstraction layers (HAL) and OS abstraction layers (OSAL) serve dual
purposes: they provide portability between environments and enable testability.
By routing all hardware and OS access through these thin layers, we can
substitute test doubles during testing while maintaining the same interface for
production use.

For the LightScheduler example, we use link-time substitution to completely
eliminate OS and hardware dependencies in the test executable. This technique
replaces entire problem modules with test doubles at link time, creating a clean
testing environment while preserving the module interfaces.

The LightScheduler receives instructions from an AdminConsole to control lights
at specific times. Every minute, it gets pinged through a TimeService callback
(OS abstraction) and commands LightController (hardware abstraction) to turn
lights on/off. By testing the scheduler logic separately from its dependencies
using test doubles, we can verify the core functionality without requiring
actual hardware or real-time OS interactions.

Each component has distinct responsibilities: LightScheduler handles application
logic, LightController manages hardware interactions, and TimeService provides
OS time services. This separation enables effective testing by allowing
independent verification of each layer's functionality through appropriate test
doubles.

### Understanding Link-Time Substitution

Link-time substitution works by separating interface from implementation. The
LightScheduler depends only on interface headers, while the actual
implementation is determined at link time. This creates what Michael Feathers
calls a "link seam" - a point where we can flexibly substitute different
implementations. The production code binds to real implementations, but tests
can leverage this seam to provide alternatives.

In practice, we compile production code into a library while keeping test
doubles as object files. The test build's makefile explicitly links the test
double objects before linking the production library. This ordering allows test
versions to override production functions with the same names, effectively
breaking dependencies on hardware and OS components during testing.

### Light Scheduler Tests

- Lights are not changed at initialization
- Time is wrong, day is wrong, no lights are changed
- Day is right, time is wrong, no lights are changed
- Day is wrong, time is right, no lights are changed
- Day is right, time is right, the right light is turned on
- Day is right, time is right, the right light is turned off
- Schedule every day
- Schedule a specific day
- Schedule all weekdays
- Schedule weekend days
- Remove scheduled event
- Remove non-existent event
- Multiple scheduled events at the same time
- Multiple scheduled events for the same light
- Remove non scheduled light schedule
- Schedule the maximum supported number of events (128)
- Schedule too many events

### Using Test Spies 

Test spies act as covert operatives that intercept communications between the
code under test and its dependencies. They capture parameters and return values
without the production code's knowledge. In the LightScheduler example, the
LightControllerSpy secretly records which lights were controlled and their
states, while the FakeTimeService allows precise control over time reporting for
reproducible tests.

The LightControllerSpy implementation uses static variables (lastId and
lastState) as a "dead drop" to store intercepted information. It implements the
same interface as the real LightController, with `On()` and `Off()` functions that
capture the parameters instead of controlling actual hardware. After test
execution, special spy functions (GetLastId() and GetLastState()) retrieve the
captured data for verification.

This approach allows development to proceed even when hardware details are
unknown. By defining clear interfaces for dependencies like time services and
light controllers, we can create test doubles that simulate the eventual
implementation. This leads to cleaner, more abstract interfaces that aren't
polluted with low-level details and remain flexible for different hardware
implementations.