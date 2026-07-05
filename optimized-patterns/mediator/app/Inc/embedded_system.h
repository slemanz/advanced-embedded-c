#ifndef INC_EMBEDDED_SYSTEM_H_
#define INC_EMBEDDED_SYSTEM_H_

#include "mediator.h"
#include "sensor.h"
#include "actuator.h"
#include "driver_adc.h"
#include "button.h"
#include "led.h"

// full definition of the system context structure

typedef struct EmbeddedSystem_t
{
    Mediator_t mediator;    // mediator interface
    Sensor_t sensor;        // sensor module
    Actuator_t actuator;    // Actuator module
    // You can add additional
}EmbeddedSystem_t;

void embedded_sys_init(EmbeddedSystem_t *system);

#endif /* INC_EMBEDDED_SYSTEM_H_ */