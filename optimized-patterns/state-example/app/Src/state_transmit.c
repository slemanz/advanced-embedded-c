#include <stdio.h>
#include "state_transmit.h"
#include "state_idle.h"

extern uint32_t valid_sensor_data;

static void state_transmit_enter(void);
static void state_transmit_execute(void);
static void state_transmit_exit(void);

// Transmit state object
state_t state_transmit = {
    .enter = state_transmit_enter,
    .execute = state_transmit_execute,
    .exit = state_transmit_exit
};


static void state_transmit_enter(void)
{
    printf("Entering Transmit State.\n");
}

static void state_transmit_execute(void)
{
    // transmit sensor data
    printf("Latest valid value: %lu\n", valid_sensor_data);
    state_machine_set_state(&g_state_machine, &state_idle);
}

static void state_transmit_exit(void)
{
    printf("Exiting Transmit State.\n");
}