#include "adc_interface.h"
#include "driver_adc.h"

/* Our concrete implementation */
static uint32_t adc_concrete_read(void)
{
    return (uint32_t)adc_read();
}

/* Instantiate the ADC interface with our concrete implementation */
ADCInterface_t BaseADC = {
    .read = adc_concrete_read
};