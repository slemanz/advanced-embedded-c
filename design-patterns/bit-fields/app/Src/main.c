#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

typedef struct
{
    unsigned enable : 1;
    unsigned errorStatus : 1;
    unsigned sensorResolution : 4;
    unsigned currentState : 2;
    unsigned nextState : 2;
}statusBits_t;

statusBits_t device_status;

int main(void)
{
    config_drivers();
    printf("Init\n");
    
    device_status.enable = 1;
    device_status.errorStatus = 0;
    device_status.sensorResolution = 3;

    if(device_status.enable)
    {
        printf("Device enabled\n");
    }else
    {
        printf("Device is currenctly disabled\n");
    }


    while(1)
    {
        
    }
}

