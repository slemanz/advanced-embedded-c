#include "adc_logger.h"
#include "button.h"
#include <stdio.h>

static ADCLogger_t self;

static uint32_t logged_read(void)
{
    uint32_t value = self.wrapped->read();

    if(!button_get_state())
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "LOG - ADC VALUE: %lu\n", value);
        self.uart_transmit(buffer);
    }

    return value;
}

void ADCLogger_Init(ADCLogger_t *logger, const ADCInterface_t *adc, void (*uart)(const char *))
{
    logger->wrapped = adc;
    self.wrapped = adc;

    logger->interface.read = logged_read;

    logger->uart_transmit = uart;
    self.uart_transmit = uart;

    printf("Adc logger init\n");
}