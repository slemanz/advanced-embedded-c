#include <stdio.h>
#include <string.h>
#include "embedded_system.h"

void concrete_notify(EmbeddedSystem_t *system, const char *event)
{
    if(event && strcmp(event, "SensorUpdate") == 0)
    {
        Sensor_t *sensor = &system->sensor;
        if(sensor->sensorValue > 1500)
        {
            printf("Mediator: Sensor value high %u, activating actuator\n", sensor->sensorValue);
            system->mediator.notify(system, "Activate");
        }
    }else if(event && strcmp(event, "Activate") == 0)
    {
        system->actuator.state = 1;
        led_on();
        printf("Mediator: Actuator activated.\n");
    }
}

void embedded_sys_init(EmbeddedSystem_t *system)
{
    // set mediator function
    system->mediator.notify = concrete_notify;
    
    // initialize sensor and actuator
    system->sensor.mediator = &system->mediator;
    system->sensor.sensorValue = 0;

    system->actuator.mediator = &system->mediator;
    system->actuator.state = 0;
}