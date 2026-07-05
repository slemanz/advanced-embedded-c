#include "config.h"

#include <stdio.h>

static const GPIO_Config_t gpioConfigs[] = {
    //{GPIOA, GPIO_PIN_NO_5, GPIO_MODE_OUT,   GPIO_SPEED_LOW,     GPIO_OP_TYPE_PP, GPIO_PIN_NO_PUPD, GPIO_PIN_NO_ALTFN},
    {GPIOA, GPIO_PIN_NO_2, GPIO_MODE_ALTFN, GPIO_SPEED_FAST,    GPIO_OP_TYPE_PP, GPIO_PIN_NO_PUPD, GPIO_PIN_ALTFN_1},
    {GPIOA, GPIO_PIN_NO_3, GPIO_MODE_ALTFN, GPIO_SPEED_FAST,    GPIO_OP_TYPE_PP, GPIO_PIN_NO_PUPD, GPIO_PIN_ALTFN_1}
    // Add more configurations as needed
};

static void config_gpio(void)
{
    for (uint32_t i = 0; i < sizeof(gpioConfigs) / sizeof(gpioConfigs[0]); i++)
    {
        GPIO_Init((GPIO_Config_t *)&gpioConfigs[i]);
    }
}

void config_drivers(void)
{
    config_gpio();
    uart2_init();
    systick_init(1000, 16000000);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
}


extern int __io_putchar(int ch)
{
    return uart2_write(ch);
}

extern int __io_getchar(void)
{
    int c;

    c = uart2_read();
    
    if(c == '\r')
    {
        uart2_write(c);
        c = '\n';
    }

    uart2_write(c);

    return c;
}


void test_setup(void)
{
    int n;

    printf("Please enter a number: ");
    scanf("%d", &n);
    printf("The number entered is: %d\r\n", n);

    char str[50];

    printf("Please type a character string: ");

    gets(str);
    gets(str);
    printf("The character string entered is: ");
    puts(str);
}