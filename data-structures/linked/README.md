# Linked lists

A linked list is a dynamic data structure consisting of a sequence of nodes,
where each node contains data and a pointer (or link) to the next node in the
sequence.

```C
struct node
{
    int8_t data;
    struct node *next;
};
```

Unlike arrays, which store elements contiguously in memory, linked lists can
store nodes in non-contiguous locations, linked together by pointers.

This structure provides flexibility for dynamic resizing and efficient insertion
and deletion of elements.

### The Key Concepts

1. Nodes
    - Each element in a linked list is called a node.
    - Data: The information or value that the node is meant to hold.
    - Pointer/Link: A reference (or address) to the next node in the sequence.

2. Head
    - The first node in the linked list is called the head.
    - The head is essential for accessing and traversing the list.

3. Tail
    - The last node in the linked list is called the tail.
    - The tail's pointer typically points to NULL (or the equivalent) to
    indicate the end of the list.

4. Non-Contiguous Memory
    - The nodes in a linked list do not need to be stored in contiguous memory locations.
    - This allows linked lists to use fragmented memory effectively.

### Types of linked lists

1. Singly Linked List:
    - Each node has a pointer to the next node only (unidirectional).
    - Traversal is only possible in one direction (from head to tail).

2. Doubly Linked List:
    - Each node has pointers to both the next and the previous node (bidirectional).
    - Traversal is possible in both directions (from head to tail and from tail to head).

3. Circular Linked List:
    - The tail's pointer points back to the head, creating a circular structure.
    - Traversal can start from any node, and the list is traversed until the start node is encountered again.

### Advantages and Applications in Embedded

**Dynamic Memory Allocation:**

- Flexible Memory Usage: Linked lists can grow or shrink as needed, using
fragmented memory more effectively than arrays, which need contiguous blocks of
memory.
- Efficient Resizing: Inserting or deleting elements in a linked list doesn't
require re-allocating the whole list like arrays.

**Efficient Insertion and Deletion:**

- Constant Time Insertion/Deletion: Inserting or deleting a node at the
beginning or at a specific location (after locating the node) is a O(1)
operation. This can be very beneficial for real time applications.
- Avoid Data Copying: Unlike arrays, which may need to shift large amounts of
data for insertion or deletion, linked lists require only the pointers to be
updated.

**Applications: Data Organization and Management**

- Task Management: Linked lists can be used in an RTOS to keep track of running
or ready tasks, where the tasks can be dynamically added and removed, and the
list can be reordered by priority.

- Event Handling: Managing events in order of arrival, or in order of priority
can be done using a linked list.

- Device Management: Linked lists can be used to store references to device
drivers, which can be allocated and deallocated as required.

- Message Buffering: Linked lists can efficiently manage message queues for
inter-process communication.

- Data logging: Log data from peripherals can be added to the linked lists, when
more data arrives, a new node is added to the list.

- Command Queues: Commands can be stored in linked lists, allowing the embedded
system to process them in the order that they arrived.

**Resource-Constrained Environments**

- Memory Savings: Linked lists can be more memory-efficient than arrays in
scenarios where the required size is highly variable or unknown beforehand.
- Allocation Control: The overhead of allocation/deallocation can be controlled
by reusing previously allocated nodes.

**Flexibility in data processing**

- Asynchronous data handling: Data can be added to the linked list at one rate
and processed at a different rate. This allows the embedded system to handle
data at different speeds.

### Implementations

A linked list to process commands:

- [Linked List - Command](app/Src/linked_command.c)
- [Linked List - Event Simulate](app/Src/linked_event_sim.c)
- [Linked List - Event with command](app/Src/main.c)
