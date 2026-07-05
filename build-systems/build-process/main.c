#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000

#define RCC_AHB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))

int main(void) {
    // Habilita o clock do GPIOA
    RCC_AHB1ENR |= (1 << 0);

    // Configura PA11 como saída
    GPIOA_MODER |= (1 << 22);
    GPIOA_MODER &= ~(1 << 23);

    while (1) {
        // Toggle PA11
        GPIOA_ODR ^= (1 << 11);

        // Delay
        for(unsigned int i = 0; i <= 4194303; i++);;
    }
}