#include "stm32g0.h"
#include "config.h"
#include <stdio.h>
#include "oximetryDisplay.h"

int main(void)
{
    config_drivers();
    printf("Init Board!\n");

    uint64_t start_time = ticks_get();
    oximetry_diplay_init();

    while(1)
    {
        if((ticks_get() - start_time) >= 5000)
        {
            oximetry_diplay_update();
            start_time = ticks_get();
        }

    }
}