#include <stdio.h>
#include "config_app.h"
#include "driver_systick.h"
#include "driver_uart.h"

#include "led.h"
#include "button.h"
#include "simple-timer.h"

#define FLASH_BASE                  0x08000000
#define VECT_TAB_BASE_ADDRESS       FLASH_BASE
#define VECT_TAB_OFFSET	            0x4000

uint8_t received_data = 0;

int main(void)
 {
    SCB->VTOR = (VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET); // offset vector table
    config_drivers();
    config_bsp();
    INTERRUPT_ENABLE();
    ticks_delay(1000);

    printf("\r\nInit Factory...\r\n");

    simple_timer_t timer_blinky;
    simple_timer_setup(&timer_blinky, 1000, true);

    while (1)
    {   
        if(simple_timer_has_elapsed(&timer_blinky)) led_toggle();

        if(received_data != 0)
        {
            uart2_write_byte(received_data);
            received_data = (received_data == '\r') ? '\n' : 0;
        }
    }
}

void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
    }
}