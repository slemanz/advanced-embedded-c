#include "device.h"
#include <stdio.h>
#include <stdlib.h>

struct Device
{
    const char *name;
    gpioStrategy deviceStrategy;
};


devicePtr device_create(const char *name, gpioStrategy deviceStrategy)
{
    devicePtr new_device = calloc(sizeof(devicePtr), sizeof(devicePtr));

    if(new_device)
    {
        new_device->name = name;
        new_device->deviceStrategy = deviceStrategy;
        printf("Device created succesfully!\n");
    }else
    {
        printf("Low memory, device not created\n");
    }

    return new_device;
}

void device_set(devicePtr device, int device_num)
{
    device->deviceStrategy(device_num);
}

void device_change(devicePtr device, gpioStrategy newDeviceStrategy)
{
    device->deviceStrategy = newDeviceStrategy;
}

void device_destroy(devicePtr device)
{
    free(device);
}