#include "config.h"
#include "stm32f411xx.h"
#include "led.h"
#include "button.h"

void config_drivers(void)
{
    fpu_enable();
    systick_init(1000);
    adc_pa1_init();
}

void config_bsp(void)
{
    led_init();
    button_init();
}
