#include <stdio.h>
#include "embedded_system.h"

void actuator_activate(Actuator_t *actuator)
{
    actuator->state = 1;
    led_on();
    printf("Actuator: activated directly\n");
}