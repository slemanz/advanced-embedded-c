#include <stdio.h>
#include "led.h"
#include "observer.h"

#define SENSOR_THRESH           1500

void led_observer_update(struct observer *self, int data)
{
    if(data > SENSOR_THRESH)
    {
        led_on();
        printf("LED Observer: sensor data %d exceeds threshold\n", data);
    }else
    {
        led_off();
        printf("LED Observer: sensor data %d normal\n", data);
    }
}

observer_t led_observer = {
    .update = led_observer_update
};