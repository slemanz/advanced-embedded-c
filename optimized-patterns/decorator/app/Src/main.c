#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "driver_uart.h"

#include "driver_adc.h"
#include "adc_logger.h"

uint32_t g_sensor_value;

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    adc_start_conversion();

    ADCLogger_t adc_logger;
    ADCLogger_Init(&adc_logger, &BaseADC, uart2_transmit);
    const ADCInterface_t *current_adc = &adc_logger.interface;

    uint64_t start_time = ticks_get();

    g_sensor_value = adc_logger.interface.read();

    while (1)
    {   
        if((ticks_get() - start_time) >= 500)
        {
            // have to press user button to log
            g_sensor_value = current_adc->read();
            start_time = ticks_get();
        }
    }
}