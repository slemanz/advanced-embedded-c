#include <stdio.h>
#include "state_error.h"
#include "state_idle.h"
#include "led.h"

static void state_error_enter(void);
static void state_error_execute(void);
static void state_error_exit(void);

// Error state object
state_t state_error = 
{
        .enter = state_error_enter,
        .execute = state_error_execute,
        .exit = state_error_exit
};

static void state_error_enter(void)
{
    printf("Entering Error State.\n");
    led_off();
}

static void state_error_execute(void)
{
    led_on();
    state_machine_set_state(&g_state_machine, &state_idle);
}

static void state_error_exit(void)
{
    printf("Exiting Error State.\n");
}