#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "driver_adc.h"
#include "led.h"

#include "observer.h"
#include "subject.h"

extern observer_t uart_observer;
extern observer_t led_observer;

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");
    adc_start_conversion();

    /* 1. Create and initialize the subject instance */
    subject_t temperature_sensor;
    temperature_sensor.observer_count = 0;
    temperature_sensor.sensor_data = 0;

    /* 2. Attach the observers */
    subject_attach(&temperature_sensor, &uart_observer);
    subject_attach(&temperature_sensor, &led_observer);

    /* 3. Get ticks*/
    uint64_t start_time = ticks_get();

    while (1)
    {   
        if((ticks_get() - start_time) >= 5000)
        {
            /* 4. Get sensor value and notify */
            temperature_sensor.sensor_data = adc_read();
            subject_notify(&temperature_sensor);
            start_time = ticks_get();
        }
    }
}