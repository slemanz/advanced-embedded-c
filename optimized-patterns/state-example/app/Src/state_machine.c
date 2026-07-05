#include "state_machine.h"
#include <stdio.h>

state_machine_t g_state_machine = {NULL};

void state_machine_set_state(state_machine_t *sm, state_t *new_state)
{
    if(sm->current_state && sm->current_state->exit)
    {
        sm->current_state->exit();
    }

    sm->current_state = new_state;

    if(sm->current_state && sm->current_state->enter)
    {
        sm->current_state->enter();
    }
}