# Strategy Pattern

- The Strategy design pattern defines a family of interchangeable
algorithms and encapsulates each one, enabling runtime selection
based on system requirements.

- In embedded systems, this pattern is crucial for manging varying
processing requirements, hardware constraints, and operational modes
while maintaining code clarity and flexibility.

### Key Goals

- **Decouple algorithms** from their usage context
- Enable runtime **algorithm swapping**
- **Simplify maintenance** of multiple algorithm variants

### Components

1. Strategy Interface: declares a common interface for all supported
algorithms. Defines the operation that each concrete strategy must
implement.

2. Context: maintains a reference to a strategy object. Delegates the
execution of an algorithm to the currently assigned strategy. Provides
a setter to change the strategy at runtime.

3. Concrete Strategies: implement the strategy interface with specific
algorithms. These modules encapsulates different behaviors or algorithms.

### Importance

Embedded Systems frequenly require adaptive behavior:

- Different sensor filtering algorithms (Kalman vs. Moving avarage)
- Multiple motor control strategies (PID vs. Fuzzy Logic)
- Various power management approaches (Dynamic vs. static scaling)

Direct implementation leads:

- Complex conditional Logic (nested switch/if statements)
- Code bloat (multiple algorithm versions in firmware)
- Maintenance challenges (difficulty adding/removing strategies)

The **Strategy Pattern** solves these by:

- Isolating algorithm implementations
- Providing clear interface contracts
- Enabling how-swapping of strategies

### Implementation

| Component         | Implementation                | Responsability                |
|---|---|---|
| Strategy          | Struct with function pointers | Defines algorithm interface   |
| Concrete Strategy | Struct                        | Implements specific algorithm |
| Context           | Main application logic        | Maintains and uses strategy reference |

- **Step 1:** define strategy interface
- **Step 2:** implement concrete strategies
- **Step 3:** configure context

## Code

**[main.c](app/Src/main.c)**

Inc:

- **[filter_strategy.h](app/Inc/filter_strategy.h)**
- **[adc_interface.h](app/Inc/adc_interface.h)**
- **[adc_reader.h](app/Inc/adc_reader.h)**

Src:

- **[filter_strategy.c](app/Src/filter_strategy.c)**
- **[adc_interface.c](app/Src/adc_interface.c)**
- **[adc_reader.c](app/Src/adc_reader.c)**