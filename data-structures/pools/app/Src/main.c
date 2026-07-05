#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    memory_pool_init();

    uint8_t msg1[] = "Hello from STM32\n";
    uint8_t msg2[] = "Slemanz here! MemPool :)\n";
    
    uart_send_message(msg1, sizeof(msg1));
    uart_send_message(msg2, sizeof(msg2));

    printf("Free Blocks Left: %lu\n", memory_pool_get_free_count());


    while (1)
    {   
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