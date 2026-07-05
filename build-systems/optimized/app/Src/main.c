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
        if((ticks_get() - start_time) >= 100)
        {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
            start_time = ticks_get();
        }
    }
}