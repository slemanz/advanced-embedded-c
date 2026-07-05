#include "adc_interface.h"
#include "driver_adc.h"

uint32_t adc_concrete_read(void)
{
    return adc_read();
}

const ADCInterface_t BaseADC = {
    .read = adc_concrete_read
};