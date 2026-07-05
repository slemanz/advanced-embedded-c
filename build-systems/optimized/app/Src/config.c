#include "config.h"
#include "driver_fpu.h"
#include "driver_gpio.h"
#include "driver_systick.h"
#include "driver_uart.h"

void gpio_setup(void)
{
    GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
}

void config_drivers(void)
{
    fpu_enable();
    gpio_setup();
    uart2_init();
    systick_init(1000);
}

extern int __io_putchar(int ch)
{
    uart2_write_byte((uint8_t)ch);
    return ch;
}