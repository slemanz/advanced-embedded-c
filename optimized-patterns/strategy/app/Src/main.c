#include "config.h"
#include <stdio.h>
#include "driver_systick.h"
#include "led.h"
#include "button.h"

#include "driver_adc.h"
#include "adc_reader.h"

int main(void)
 {
    config_drivers();
    config_bsp();
    adc_start_conversion();

    printf("\nInit board...\n\r");

    ADCReader_t reader;
    MovingAvarageFilter_t avgFilter;
    avgFilter.base.filter = movingAvarageFilter;
    avgFilter.index = 0;
    avgFilter.count = 0;
    for(int i = 0; i < 4; i++) avgFilter.samples[i] = 0;

    ADCReader_init(&reader, &BaseADC, (FilterStrategy_t*)&avgFilter);

    /* Read 10 ADC Value */
    for(int i = 0; i < 10; i++)
    {
        uint32_t filteredValue = ADCReader_readFiltered(&reader);
        printf("%2d - Filtered ADC Value: %lu\n", i+1, filteredValue);
    }

    while (1)
    {   
    }
}