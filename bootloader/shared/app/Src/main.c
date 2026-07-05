#include <stdio.h>
#include "config_app.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_uart.h"

#define FLASH_BASE                  0x08000000
#define VECT_TAB_BASE_ADDRESS       FLASH_BASE
#define VECT_TAB_OFFSET	            0x8000

struct btl_common_apis
{
    void (*led_on)(void);
    void (*led_off)(void);
    void (*led_toggle)(void);
    void (*uart_write_byte)(uint8_t ch);
};

struct btl_common_apis *btl_common_apis = (struct btl_common_apis*)0x08004000;

void print_hello(void)
{
    btl_common_apis->uart_write_byte('h');
    btl_common_apis->uart_write_byte('e');
    btl_common_apis->uart_write_byte('l');
    btl_common_apis->uart_write_byte('l');
    btl_common_apis->uart_write_byte('o');
    btl_common_apis->uart_write_byte('\n');
}

int main(void)
 {
    SCB->VTOR = (VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET); // offset vector table
    config_drivers();
    config_bsp();
    INTERRUPT_ENABLE();
    ticks_delay(1000);

    printf("\nInit app ok...\n\r");
    print_hello();

    uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 1000)
        {
            btl_common_apis->led_toggle();
            start_time = ticks_get();
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