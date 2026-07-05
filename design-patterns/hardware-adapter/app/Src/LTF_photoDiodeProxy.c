#include "driver_adc.h"

uint32_t accessSpO2(void)
{
    return (uint32_t)(adc_read(0));
}

uint32_t accessPulse(void)
{
    return (uint32_t)(adc_read(0));
}