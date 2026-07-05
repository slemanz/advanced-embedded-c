# Observer Pattern

- The observer design pattern, also known as the **Publisher-Subscriber Patter**,
is a behavioral pattern that establishes a one-to-many dependency
between objects.

- When one object (the subject or publisher) changes its state,
all its dependents (the observers or subscribers) are notified
and updated automatically.

### Components

- **Observer (Interface):** declares the update (data) method that all
observers must implement. This method is called by the subject when its 
state changes.

- **Concrete Observers:** these modules implement the observer interface.
Each concrete observer defines its own version of update (data) to react
to notifications from the subject.

- **Subject:** maintains a list (or another collection) of observers and
provides methods to add or remove them. When the subject's state changes,
it calls notify (data), which in turn calls update (data) on each registered
observer.

### Key Characteristics

Direct event handling leads to:

- **Tight coupling:** hardcoded dependencies beetween components.
- **Code Duplication:** repeated event-checking logic.
- **Maintenance challenges:** difficulty adding/removing event handlers.
- **Resource contention:** unmanaged ISR/thread interactions.

The observer pattern solves these by:

- **Centralizing** event notification logic.
- Allowing **dynamic** subscription to events.
- **Standardizing** event propagation.

## Code

**[main.c](app/Src/main.c)**

Inc:

- **[subject.h](app/Inc/subject.h)**
- **[observer.h](app/Inc/observer.h)**

Src:

- **[subject.c](app/Src/subject.c)**
- **[led_observer.c](app/Src/led_observer.c)**
- **[uart_observer.c](app/Src/uart_observer.c)**
