#ifndef INC_DRIVER_ADC_H_
#define INC_DRIVER_ADC_H_

#include "stm32g0.h"

void adc_init(void);
uint16_t adc_read(uint8_t channel);

void adc_init_temperature(void);
float adc_read_temperature(void);

#endif /* INC_DRIVER_ADC_H_ */