#include "stm32g0.h"
#include "gpioDevices.h"
#include <stdio.h>

void gpioADeviceStrategy(int device_number)
{
    RCC->IOPENR |= (1U << 0);
    GPIOA->MODER |=  (1U << (device_number*2));
    GPIOA->MODER &= ~(1U << (device_number*2 + 1));
    GPIOA->ODR |= (1U << device_number);
    printf("GPIOA_DEVICE device number %d is ON\n", device_number);
}

void gpioBDeviceStrategy(int device_number)
{
    RCC->IOPENR |= (1U << 1);
    GPIOB->MODER |=  (1U << (device_number*2));
    GPIOB->MODER &= ~(1U << (device_number*2 + 1));
    GPIOB->ODR |= (1U << device_number);
    printf("GPIOB_DEVICE device number %d is ON\n", device_number);
}

void gpioCDeviceStrategy(int device_number)
{
    RCC->IOPENR |= (1U << 2);
    GPIOC->MODER |=  (1U << (device_number*2));
    GPIOC->MODER &= ~(1U << (device_number*2 + 1));
    GPIOC->ODR |= (1U << device_number);
    printf("GPIOC_DEVICE device number %d is ON\n", device_number);
}