#ifndef INC_ADC_LOGGER_H
#define INC_ADC_LOGGER_H

#include "driver_uart.h"
#include "adc_interface.h"

typedef struct
{
    ADCInterface_t interface;
    const ADCInterface_t *wrapped;
    void (*uart_transmit)(const char *);
}ADCLogger_t;

void ADCLogger_Init(ADCLogger_t *logger, const ADCInterface_t *adc,
                                         void (*uart)(const char *));

#endif /* INC_ADC_LOGGER_H */