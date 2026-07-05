# State Pattern

- The state design pattern enables an object to change its
behavior based on its internal state.

- Instead of using large conditional statements (if-else or
switch-case) to handle different states, the State Pattern
encapsulates state-specific logic into separate functions
or structures.

- This approach promotes modularity, reduces complexity,
and improves code maintainability.

### Components

- **State (Interface):** declares common operations (e,g
handleEvent(), enter() and exit()) that each state must implement.
This abstraction allows the context to interact with the state
without knowing its concrete type.

- **Concrete States (IdleState, TransmitState, ErrorState):** these
modules implement the StateInterface with behavior specific to each
state. For example, in an embedded communication module:
    - IdleState: Might simply wait for an event.
    - TransmitState: initiates data transmission and manages the
    transmission process.
    - ErrorState: handles error conditions and performs revocery.

- **Context:** Represents the object whose behavior changes with its
state. It maintains a reference to the current state and delegates
requests to it. The `setState()` method changes the current state, and
`request()` is used to handle events by forwarding them to the current
state.

### Key Characteristics

- **Encapsulation of State Logic:** Each state is represented by a function
or structure, encapsulating all behavior associated with that state.

- **Dynamic Behavior:** The system can dynamically switch between states
at runtime.

- **Separation of Concerns:** The main object (context) delegates
state-specific behavior to state handlers, reducing complexity in the main logic.

- **Open/Closed Principle:** New states can be added without modifying existing
code, adhering to the Open/Closed Principle of SOLID design.

### Example

Consider a traffic light system with three states: Red, Yellow, and Green. 
The behavior of the traffic light depends on its current state.

**Step 1: Define the State Interface**

```C
typedef void (*StateHandler) (void);

// Function prototypes for state handlers
void redStateHandler (void);
void yellowStateHandler(void);
void greenStateHandler (void);
```

**Step 2: Implement Concrete State**

```C
#include <stdio.h>

void redStateHandler (void)
{
    printf("Red Light: Stop vehicles.\n");
    // Transition to Green after a delay
    setNextState(greenStateHandler);
}

void yellowStateHandler(void)
{
    printf("Yellow Light: Prepare to stop.\n");
    // Transition to Red after a delay
    setNextState(redStateHandler);
}

void greenStateHandler (void)
{
    printf("Green Light: Allow vehicles to proceed.\n");
    // Transition to Yellow after a delay
    setNextState(yellowStateHandler);
}
```

**Step 3: Define the Context**

```C
StateHandler currentState = redStateHandler; // Initial state
void setNextState(StateHandler nextState)
{
    currentState = nextState;
}

void runStateMachine (void)
{
    if (currentState != NULL) 
    {
        currentState(); // Execute the current state's behavior
    }
}
```

**Step 4: main function**

```C
int main(void)
{
    while (1)
    {
        runStateMachine();
        delay(1000);
    }
    return 0;
}
```

### Advantages

- **Improved Code Organization and Maintainability:** Each state
encapsulates its behavior, making the system easier to understand and modify.

- **Scalability and Extensibility:** Adding new states or modifying transitions
does not require rewriting large portions of the code.

- **Clear Separation of Concerns:** State-specific logic is separated from
the context, reducing complexity in the main application.

- **Testability:** Each state can be individually tested, and the transitions
can be simulated in a controlled environment.

### Applications

| Application Area | Example |
| --- | --- |
| Communication Protocols |  Managing states of a UART or CAN interface: idle, transmitting, error, and reconnecting. |
| Power Management | Transitioning between active, sleep, and deep-sleep modes based on battery level or workload. |
| Motor Control | Switching control algorithms (e.g., startup, running, braking, fault detection) for a motor driver. |
| User Interface (UI) Handling |  Managing screen states in embedded displays: welcome screen, menu navigation, error display, etc. |
| Sensor Data Processing |  States representing calibration, normal operation, and error handling for sensor arrays. |

## Code

**[main.c](app/Src/main.c)**