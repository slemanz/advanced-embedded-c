#include <stdio.h>
#include "config.h"
#include "driver_gpio.h"
#include "driver_systick.h"

int main(void)
{
    config_drivers();
    printf("Init the board\n\r");

    uint64_t start_time = ticks_get();

    while(1)
    {
        if((ticks_get() - start_time) >= 1000)
        {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
            start_time = ticks_get();
        }
    }
}