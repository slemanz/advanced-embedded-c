#include "driver_adc.h"

void adc_init(void)
{
    ADC_PCLK_EN();

    ADC->CR = 0;

    ADC->CR |= (1 << 28); // voltage regulator
    for(uint32_t i = 0; i < 1000; i++);

    ADC->CR |= (1U << 31); // calibration
    while((ADC->CR & (1U << 31)) != 0);

    ADC->CR |= (1 << 0); // enable adc
    ADC->SMPR |= (0x7 << 0);
    MMIO32(ADC_CCR_BASEADDR) |= (1 << 22);
}

uint16_t adc_read(uint8_t channel)
{
    ADC->CHSELR = (1 << channel);   // channel select
    ADC->CR |= (1 << 2);            // start conversion
    while(ADC->CR & (1 << 2));

    return ((uint16_t)ADC->DR);
}

void adc_init_temperature(void)
{
    MMIO32(ADC_CCR_BASEADDR) |= (1 << 23);
    for(uint32_t i = 0; i < 10000; i++);
}

float adc_read_temperature(void)
{
    uint16_t adc_temp = adc_read(12);
    float temperature, volt;

    volt = ((double)adc_temp/4095.0)*3.3;
    temperature = ((volt-0.76)/0.0025) + 30.0;

    return temperature;
}