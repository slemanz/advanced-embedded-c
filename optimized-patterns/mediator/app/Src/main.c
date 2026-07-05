#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "driver_adc.h"
#include "led.h"
#include "button.h"

#include "embedded_system.h"

extern void sensor_read(Sensor_t *sensor, struct EmbeddedSystem_t *system);

EmbeddedSystem_t system;

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");
    led_off();

    uint64_t start_time = ticks_get();

    adc_start_conversion();
    
    embedded_sys_init(&system);

    while (1)
    {   
        if((ticks_get() - start_time) >= 2000)
        {
            sensor_read(&system.sensor, &system);
            start_time = ticks_get();
        }
    }
}