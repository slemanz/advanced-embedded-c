#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "driver_systick.h"
#include "led.h"
#include "button.h"
#include "driver_adc.h"

#include "mediator.h"
#include "colleague.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");
    adc_start_conversion();

    
    /* 1. Create colleague objects with a temporary NULL mediator */
    Light_t *light = light_create(NULL);
    Thermostat_t *thermostat = thermostat_create(NULL);
    SecuritySystem_t *securitySystem = securitySystem_create(NULL);


    /* 2. Ensure memory was allocated successfully */
    if (!light || !thermostat || !securitySystem)
    {
        printf("Error: Failed to allocate memory for colleagues.\n");
        free(light);
        free(thermostat);
        free(securitySystem);
        return -1;
    }


    /* 3. Create the mediator and assign the colleagues */
    HomeAutomationMediator_t* mediator = HomeAutomationMediator_create(light, thermostat, securitySystem);


    /* 4. Ensure memory was allocated successfully for mediator */
    if (!mediator) {
        printf("Error: Failed to allocate memory for mediator.\n");
        free(light);
        free(thermostat);
        free(securitySystem);
        return -1;
    }


    /* 5. Update colleagues with the proper mediator reference */
    light->base.mediator = (Mediator_t*)mediator;
    thermostat->base.mediator = (Mediator_t*)mediator;
    securitySystem->base.mediator = (Mediator_t*)mediator;
    printf("System Ready. Simulating Events...\n");


    /* 6. Simulate events and mediator interaction */
    ticks_delay(3000);
    light->base.sendEvent((void*)light, "security_on");
    thermostat->base.sendEvent((void*)thermostat, "thermostat_adjusted");


    /* 7. Direct mediator action simulation */
    ticks_delay(3000);
    printf("\nMediator triggers direct actions:\n");
    light->base.performAction((void*)light, "dim");
    thermostat->base.performAction((void*)thermostat, "adjust_low");
    securitySystem->base.performAction((void*)securitySystem, "activate");


    /* Cleanup resources */
    ticks_delay(2000);
    printf("\nShutting down system. Freeing resources...\n");
    free(light);
    free(thermostat);
    free(securitySystem);
    free(mediator);


    while (1)
    {   
    }
}