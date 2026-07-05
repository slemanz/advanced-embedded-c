#include "stm32f401xe.h"
#include <stdint.h>

#define GPIOAEN     (1U << 0)
#define PIN5        (1U << 5)
#define LED_PIN     (PIN5)

int main(void)
{
    // Config PA5
    RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    while (1)
    {
        GPIOA->ODR ^= LED_PIN;
        for(uint32_t i = 0; i < 1000000; i++);
    }
}