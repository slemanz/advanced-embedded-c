#include <stdio.h>
#include "state_idle.h"
#include "state_read_adc.h"

static void state_idle_enter(void);
static void state_idle_execute(void);
static void state_idle_exit(void);

// Idle state object
state_t state_idle =
{
    .enter = state_idle_enter,
    .execute = state_idle_execute,
    .exit = state_idle_exit
};


static void state_idle_enter(void)
{
    printf("Entering Idle State.\n");
}

static void state_idle_execute(void)
{
    state_machine_set_state(&g_state_machine, &state_read_adc);
}

static void state_idle_exit(void)
{
    printf("Exiting Idle State.\n");
}
