#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "driver_uart.h"
#include "led.h"
#include "button.h"


// printf retarget
extern int __io_putchar(int ch)
{
    UART_Singleton_t *uart = uart_get_instance();

    /*
     * Singleton ensures that that wont have redudant initialization
     */
	if(uart && uart->is_initialized)
	{
	    uart_write(uart, ch);
	}
	return ch;
}

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");
    printf("Singleton working 1!!!\n");
    printf("Singleton working 2!!!\n");
    printf("Singleton working 3!!!\n");

    uint64_t start_time = ticks_get();
    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            start_time = ticks_get();
        }
    }
}