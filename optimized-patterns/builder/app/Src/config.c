#include "config.h"

#include "driver_fpu.h"
#include "driver_systick.h"
#include "driver_gpio.h"
#include "driver_adc.h"

#include "led.h"
#include "button.h"

void gpio_setup(void)
{
    GPIO_Handle_t UartPin;
    UartPin.pGPIOx = GPIOA;
    UartPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    UartPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    UartPin.GPIO_PinConfig.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;

    GPIO_Init(&UartPin);
}


void config_drivers(void)
{
    fpu_enable();
    gpio_setup();
    systick_init(1000);
    adc_pa1_init();
}

void config_bsp(void)
{
    led_init();
    button_init();
}
