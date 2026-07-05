#include "sensor.h"
#include "embedded_system.h"

void sensor_read(Sensor_t *sensor, struct EmbeddedSystem_t *system)
{
    sensor->sensorValue = adc_read();
    sensor->mediator->notify(system, "SensorUpdate");
}