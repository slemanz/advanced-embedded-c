#include <stdio.h>
#include <stdint.h>

#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000

#define RCC_AHB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))

//uint32_t sensor_value;

extern void initialise_monitor_handles(void);

int main(void)
{
    initialise_monitor_handles();

    RCC_AHB1ENR |= (1 << 0);
    GPIOA_MODER |= (1 << 10);
    GPIOA_MODER &= ~(1 << 11);

    printf("Init board!\n");

    uint32_t data = 0;

    while (1)
    {
        printf("Toggle time: %d\n", (int)data);
        data++;
        GPIOA_ODR ^= (1 << 5);
        for(unsigned int i = 0; i <= 800000; i++);
    }
}