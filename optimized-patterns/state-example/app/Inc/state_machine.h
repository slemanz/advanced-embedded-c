#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include <stdint.h>

// State structure defining the pointers for enter, exit and execute
typedef struct state
{
    void (*enter)(void);    // Called when entering the state
    void (*execute)(void);  // Called while in the state
    void (*exit)(void);     // Called when exiting the state
}state_t;

// State machine holding the current state
typedef struct
{
    state_t *current_state;
}state_machine_t;

extern state_machine_t g_state_machine;

void state_machine_set_state(state_machine_t *sm, state_t *new_state);

#endif /* INC_STATE_MACHINE_H_ */