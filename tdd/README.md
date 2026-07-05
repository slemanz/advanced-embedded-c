# Test-Driven Development (TDD)

### The Importance

Traditional software development often treated testing as an afterthought—code
was written first, then debugged in an unpredictable and time-consuming process.
Developers spent significant effort fixing bugs, with some errors lingering
undetected for months or even slipping into production. Over time, industry
experts recognized that short development cycles and automated testing reduced
defects and improved predictability. Test-Driven Development (TDD) emerged as a
solution, integrating testing into the core development process rather than
leaving it as a final step. By writing tests before code, TDD helps catch errors
early, reduces debugging time, and leads to more reliable software. 

### Why do we need?

A glaring example of why testing matters is the Zune bug, which froze
Microsoft's media players on December 31, 2008—the last day of a leap year. The
issue stemmed from a faulty clock driver function that mishandled leap year
calculations, entering an infinite loop when processing the 366th day. While
many assumed the fix was as simple as changing `(days > 366)` to `(days >= 366)`,
testing revealed this "solution" introduced a new bug—incorrectly setting the
date to January 0, 2009.

This incident highlights three key lessons:

1. Code reviews alone aren’t enough—even experts misdiagnosed the problem
without executing tests.

2. Edge cases demand explicit testing—a single test simulating the leap year’s
last day would have caught the bug.

3. TDD forces proactive problem-solving—by writing tests first, developers
identify flaws before they reach production.

TDD isn’t about testing every possible scenario but focusing on "what can
break".  Bugs are inevitable, but TDD provides a safety net by turning
assumptions into verified behavior.

“Why do we need TDD?” We need TDD because we’re human and we make mistakes.
Among other reasons, TDD is needed to systematically get our code working as
intended and to produce the automated test cases that keep the code working.

### What is TDD?

Test-Driven Development is a disciplined approach to coding where you write
tests before writing production code. The process follows a simple rhythm:

1. Write a small, failing test that defines the desired behavior.

2. Write the minimal code to make the test pass.

3. Refactor to improve design while keeping tests green.

Unlike manual testing (slow, error-prone) or "test-later" approaches (where bugs
pile up), TDD prevents defects upfront. The test suite becomes a living
specification, growing alongside the code.

### Topics

- [Intro](intro/)
- [Tools](tools/)
- [Starting](starting/)
- [Testing your Way](testing_way/)
- [Strategy](strategy/)
- [Doubts](doubts/)
- [Test Doubles](test_doubles/)
- [Production Code](production_code/)