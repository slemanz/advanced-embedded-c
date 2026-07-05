#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"
#include "driver_rtc.h"

static void get_current_timestamp(void)
{
    uint32_t hour   =  rtc_time_get_hour();
	uint32_t minute =  rtc_time_get_minute();
	uint32_t second =  rtc_time_get_second();

    printf("%02lx:%02lx:%02lx\r\n", hour, minute, second);
}

int main(void)
 {
    config_drivers();
    config_bsp();
    rtc_init();

    printf("\r\nInit board...\r\n");

    uint32_t adc_value = 0;

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) >= 5000)
        {
            get_current_timestamp();
            start_time2 = ticks_get();
        }

        if(!button_get_state())
        {
            adc_start_conversion();
            adc_value = adc_read();
            printf("Adc: %ld\n", adc_value);
            while(!button_get_state());
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
        if(received_data == '\r')
        {
            received_data = '\n';
            uart2_write_byte(received_data);
        }
    }
}