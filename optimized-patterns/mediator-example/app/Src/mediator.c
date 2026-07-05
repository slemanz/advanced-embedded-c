#include "mediator.h"
#include "colleague.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the vtable for the home automation mediator */
static MediatorInterface_t homeAutomationVTable = {
    .notify = homeAutomationNotify
};

void homeAutomationNotify(Mediator_t * mediator, const char* event)
{
    HomeAutomationMediator_t *self = (HomeAutomationMediator_t*)mediator;

    if(strcmp(event, "security_on") == 0)
    {
        printf("Mediator: Security system activated. Turning off lights and adjusting thermostat.\n");

        /* Explicitly cast before accessing members */
        Light_t* light = (Light_t*)self->light;
        Thermostat_t* thermostat = (Thermostat_t*)self->thermostat;
        SecuritySystem_t* securitySystem = (SecuritySystem_t*)self->securitySystem;

        /* Trigger actions on colleagues */
        light->base.performAction((void*)light, "turn_off");
        thermostat->base.performAction((void*)thermostat, "adjust_low");
        securitySystem->base.performAction((void*)securitySystem, "activate");
    }else  if (strcmp(event, "security_off") == 0) {
        //...do something
    }
    //Add more
}

HomeAutomationMediator_t *HomeAutomationMediator_create(void* light, void* thermostat, void* securitySystem)
{
    HomeAutomationMediator_t *mediator = (HomeAutomationMediator_t*)malloc(sizeof(HomeAutomationMediator_t));
    if(mediator)
    {
        mediator->base.vtable = &homeAutomationVTable;
        mediator->light = light;
        mediator->thermostat = thermostat;
        mediator->securitySystem = securitySystem;
    }
    return mediator;
}