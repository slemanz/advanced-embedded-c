#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "device.h"

State_t btn, btnOld = 0;

int main(void)
{
    config_drivers();
    printf("Init\n");
    //test_setup();

    // PA5 - LED
    DevicePtr device1;

    // PC14 - Button
    DevicePtr device2;

    const char* name1  = "User LED";
	Address addr1 = {GPIOA, 5};

    const char* name2  = "User Button";
	Address addr2 = {GPIOC, 13};

    device1 = device_create(name1, &addr1);
    device2 = device_create(name2, &addr2);

    device_turnOn(device1); // set as output

    device_displayInfo(device1);
    device_displayInfo(device2);

    while(1)
    {
        btn = device_read(device2);

        if(btn && btn != btnOld)
        {
            device_turnOff(device1);
            btnOld = btn;
        }else if(btn != btnOld)
        {
            device_turnOn(device1);
            btnOld = btn;
        }
    }
}

