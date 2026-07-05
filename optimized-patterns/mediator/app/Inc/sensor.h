#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

// Define the sensor colleague object

#include "mediator.h"

typedef struct
{
    Mediator_t *mediator;
    int sensorValue;
}Sensor_t;

#endif /* INC_SENSOR_H_ */