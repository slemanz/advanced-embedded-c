#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"


#define APPLICATION_ADDRESS         0x08008000
#define MSP_VERIFY_MASK			    0x2FFE0000
#define EMPTY_MEM					0xFFFFFFFF


typedef void (*func_ptr)(void);

#define MEM_CHECKK_V2

void jmp_to_default_app(void)
{
    uint32_t app_start_address;
    func_ptr jump_to_app;

    printf("Jump to app!\n");
    ticks_delay(300);

    	/*Version 1*/
#ifdef MEM_CHECKK_V1
	if(((*(uint32_t *)APPLICATION_ADDRESS) & MSP_VERIFY_MASK ) ==  0x20020000)
#endif

	/*Version 2*/
#ifdef MEM_CHECKK_V2
	if((*(uint32_t *)APPLICATION_ADDRESS) != EMPTY_MEM)
#endif
    {
        app_start_address = *(uint32_t*)(APPLICATION_ADDRESS + 4);
        jump_to_app = (func_ptr)app_start_address;

        /* Initialize main stack pointer */
        // implement

        jump_to_app();
    }else
    {
        printf("Ops! No application found at location...\n");
    }
}

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit bootloader...\n\r");

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();
    uint64_t jump_time = 5000;

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 100)
        {
            led_toggle();
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) >= jump_time)
        {
            INTERRUPT_DISABLE();
            jmp_to_default_app();

            jump_time = 900000;
            start_time2 = ticks_get();
        }
    }
}

uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
        uart2_write_byte(received_data);
    }
}