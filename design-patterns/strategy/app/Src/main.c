#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "device.h"
#include "gpioDevices.h"

int main(void)
{
    config_drivers();
    printf("Init\n");

    const char* device1_name = "System LED";
    devicePtr device1 = device_create(device1_name, gpioADeviceStrategy);

    device_set(device1, 5);

    device_change(device1, gpioBDeviceStrategy);
    device_set(device1, 1);


    while(1)
    {
    }
}