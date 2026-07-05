#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "led.h"
#include "button.h"

#include "state_machine.h"
#include "state_idle.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    state_machine_set_state(&g_state_machine, &state_idle);

    while (1)
    {   
        if((ticks_get() - start_time) >= 1000)
        {
            if(g_state_machine.current_state && g_state_machine.current_state->execute)
            {
                g_state_machine.current_state->execute();
            }
            start_time = ticks_get();
        }
    }
}