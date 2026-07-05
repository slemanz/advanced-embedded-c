#include "device.h"
#include "driver_uart.h"

#include <stdio.h>
#include <stdlib.h>

typedef uint32_t deviceID_t;

struct Device{
    const char *name;
    Address address;
    deviceID_t uuid;
};

uint32_t noOfdevices = 0;

DevicePtr device_create(const char *name, const Address *address)
{
    DevicePtr device = (DevicePtr)calloc(sizeof(DevicePtr), sizeof(DevicePtr));

    if(device)
    {
        device->name = name;
        noOfdevices++;
        device->address.Port = address->Port;
        device->address.Pin = address->Pin;
        device->uuid = noOfdevices;

        /* Enable clock access to device Port */
        switch((int)device->address.Port)
        {
            case (int)GPIOA: RCC->IOPENR |= GPIOA_EN; break;
            case (int)GPIOB: RCC->IOPENR |= GPIOB_EN; break;
            case (int)GPIOC: RCC->IOPENR |= GPIOC_EN; break;
        }
    }else
    {
        printf("Low memory, cannot create device\n");
    }

    return device;

}


void device_turnOn(DevicePtr device)
{
    /* 1. configure device as an output device */

    uint16_t _pin = device->address.Pin;
    device->address.Port->MODER |=  (1U << (_pin*2));
    device->address.Port->MODER &= ~(1U << (_pin*2 + 1));

    /* 2. Turn on device */

    device->address.Port->ODR |= (1U << _pin);
    printf(" %s is on\n", device->name);
}

void device_turnOff(DevicePtr device)
{
    uint16_t _pin = device->address.Pin;

    /* 1. Turn off device */
    device->address.Port->ODR &= ~(1 << _pin);
    printf(" %s is off\n", device->name);
}

void device_toggle(DevicePtr device)
{
    uint16_t _pin = device->address.Pin;

    /* 1. Toggle device */
    device->address.Port->ODR ^= (1U << _pin);
    printf(" %s has toggled\n", device->name);
}

State_t device_read(DevicePtr device)
{
    State_t bitStatus;

    /* 1. Configure as input pin */
    uint16_t _pin = device->address.Pin;
    device->address.Port->MODER &= ~(0x3U << (2*_pin));

    /* 2. Read device */
    if((device->address.Port->IDR & (1U << _pin)))
    {
        bitStatus = 1;
    }else
    {
        bitStatus = 0;
    }

    return bitStatus;
}

void device_destroy(DevicePtr device)
{
    printf("*** %s destroyed***\n\r", device->name);
    free(device);
    noOfdevices--;
}


void device_displayInfo(DevicePtr device)
{
    const char* type;
    uint32_t _pin = device->address.Pin;
    if(device->address.Port->MODER & (1 << 2*_pin))
    {
        type = "output device";
    }else
    {
        type = "input device";
    }

    printf("************************************************************\n");
    printf("Device name: %s\n", device->name);
    printf("Device type: %s\n", type);
    printf("The device uuid is %ld\n", device->uuid);
    printf("************************************************************\n");
}