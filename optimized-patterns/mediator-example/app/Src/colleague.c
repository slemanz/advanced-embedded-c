#include "colleague.h"
#include "led.h"
#include "button.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void colleagueSendEvent(Colleague_t *colleague, const char *event)
{
    if(colleague && colleague->mediator && colleague->mediator->vtable && colleague->mediator->vtable->notify)
    {
        colleague->mediator->vtable->notify(colleague->mediator, event);
    }
}

/* Light specific behavior */
void lightPerformAction(Colleague_t *colleague, const char *action)
{
    if(strcmp(action, "turn off") == 0)
    {
        printf("Ligth: turning off.\n");
        led_on();
    }else if(strcmp(action, "dim"))
    {
        printf("Light dimming lights.\n");
        led_off();
    }else
    {
        printf("Light: Unknown action '%s'.\n", action);
    }
}

Light_t* light_create(Mediator_t* mediator) {
    Light_t* light = (Light_t*)malloc(sizeof(Light_t));
    if (light) {
        light->base.mediator = mediator;
        light->base.sendEvent = colleagueSendEvent;
        light->base.performAction = lightPerformAction;
    }
    return light;
}

/* Thermostat specific behavior */

void thermostatPerformAction(Colleague_t* colleague, const char* action) {
    if (strcmp(action, "adjust_low") == 0) {
        printf("Thermostat: Lowering temperature.\n");
        //do something....
    } else if (strcmp(action, "adjust_high") == 0) {
        printf("Thermostat: Raising temperature.\n");
    } else {
        printf("Thermostat: Unknown action '%s'.\n", action);
    }
}


Thermostat_t *thermostat_create(Mediator_t *mediator) {
    Thermostat_t* thermostat = (Thermostat_t*)malloc(sizeof(Thermostat_t));
    if (thermostat) {
        thermostat->base.mediator = mediator;
        thermostat->base.sendEvent = colleagueSendEvent;
        thermostat->base.performAction = thermostatPerformAction;
    }
    return thermostat;
}

/* Security system specific behavior */

void securitySystemPerformAction(Colleague_t *colleague, const char *action)
{
    if(strcmp(action, "activate") == 0)
    {
        printf("Security System: activating security.\n");
    }else if(strcmp(action, "deactivate") == 0)
    {
        printf("Security System: deactivating security.\n");
    }else
    {
        printf("Security System: Unknown action '%s'\n", action);
    }
}

SecuritySystem_t *securitySystem_create(Mediator_t *mediator)
{
    SecuritySystem_t *securitySystem = (SecuritySystem_t*)malloc(sizeof(SecuritySystem_t));
    if(securitySystem)
    {
        securitySystem->base.mediator = mediator;
        securitySystem->base.sendEvent = colleagueSendEvent;
        securitySystem->base.performAction = securitySystemPerformAction;
    }
    return securitySystem;
}