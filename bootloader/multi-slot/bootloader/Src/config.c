#include <stdio.h>
#include "config.h"

#include "driver_fpu.h"
#include "driver_systick.h"
#include "driver_uart.h"
#include "driver_gpio.h"
#include "driver_adc.h"

#include "led.h"
#include "button.h"

void gpio_setup(void)
{
    // Set GPIOA pin 13 as output
    GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = LED_PORT;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = LED_PIN;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}


void config_drivers(void)
{
    fpu_enable();
    //gpio_setup();
    uart2_init();
    systick_init(1000);
    adc_pa1_init();
}

void config_bsp(void)
{
    led_init();
    button_init();
}

typedef void (*func_ptr)(void);

void jmp_to_app(uint32_t addr_value)
{
    uint32_t app_start_address;
    func_ptr jump_to_app;

    printf("Jump to app!\r\n");
    ticks_delay(300);

    	/*Version 1*/
#ifdef MEM_CHECKK_V1
	if(((*(uint32_t *)addr_value) & MSP_VERIFY_MASK ) ==  0x20020000)
#endif

	/*Version 2*/
#ifdef MEM_CHECKK_V2
	if((*(uint32_t *)addr_value) != EMPTY_MEM)
#endif
    {
        app_start_address = *(uint32_t*)(addr_value + 4);
        jump_to_app = (func_ptr)app_start_address;

        /* Initialize main stack pointer */
        // implement

        jump_to_app();
    }else
    {
        printf("Ops! No application found at location...\r\n");
    }
}

// printf retarget
extern int __io_putchar(int ch)
{
    uart2_write_byte((uint8_t)ch);
    return ch;

}