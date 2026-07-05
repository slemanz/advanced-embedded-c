#include "config.h"
#include <stdio.h>

#include "driver_systick.h"
#include "driver_uart.h"

// printf retarget
extern int __io_putchar(int ch)
{
    uart2_write_byte((uint8_t)ch);
    return ch;
}

int main(void)
 {
    config_drivers();
    config_bsp();

    // Uart builder
    UART_Builder_t uart = uart_builder_init();

    uart_set_baudrate(&uart, 9600);
    uart_set_wordlength(&uart, UART_WORDLENGTH_8B);
    uart_set_parity(&uart, UART_PARITY_NONE);
    uart_set_mode(&uart, UART_MODE_TX);

    // Apply configuration
    uart_build(&uart);

    printf("\nInit board...\n\r");
    uint64_t start_time = ticks_get();

    while (1)
    {   
        // Send Hello!
        if((ticks_get() - start_time) >= 5000)
        {
            printf("Hello!\n");
            start_time = ticks_get();
        }

    }
}