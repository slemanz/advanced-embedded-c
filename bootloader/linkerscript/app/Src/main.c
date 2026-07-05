#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_gpio.h"
#include "driver_uart.h"

// defines to place in linker sections
#define CUSTOM_FUNC      __attribute__((section(".custom_section")))
#define RAM_FUNC        __attribute__((section(".RamFunc")))

unsigned char __attribute__((section(".custom_ram_block"))) custom_ram_buff[10]; // 10 bytes
unsigned char __attribute__((section(".custom_flash_block"))) custom_flash_buff[10]; // 10 bytes

void RAM_FUNC _led_toggle(void)
{
    led_toggle();
    ticks_delay(100);
}

void CUSTOM_FUNC _led_toggle2(uint32_t dly_ms)
{
    led_toggle();
    ticks_delay(dly_ms);
}


int main(void)
 {
    config_drivers();
    config_bsp();
    printf("\nInit board...\n\r");

    custom_ram_buff[0] = 10;
    (void)custom_ram_buff[0];

    while (1)
    {   
        // blinky
        //_led_toggle(); // works
        _led_toggle2(1000); // works
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