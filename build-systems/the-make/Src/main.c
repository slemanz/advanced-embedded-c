#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000

#define RCC_AHB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))

int main(void)
{
    // Config PA5
    RCC_AHB1ENR |= (1 << 0);
    GPIOA_MODER |= (1 << 10);
    GPIOA_MODER &= ~(1 << 11);

    while (1) {
        // Toggle 
        GPIOA_ODR ^= (1 << 5);
        for(unsigned int i = 0; i <= 200000; i++);;
    }
}