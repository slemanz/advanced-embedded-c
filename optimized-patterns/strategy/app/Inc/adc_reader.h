#ifndef INC_ADC_READER_H_
#define INC_ADC_READER_H_

#include "adc_interface.h"
#include "filter_strategy.h"

typedef struct{
    const ADCInterface_t *adc;
    FilterStrategy_t *filter;
}ADCReader_t;

void ADCReader_init(ADCReader_t *reader, ADCInterface_t *adc, FilterStrategy_t *filter);
uint32_t ADCReader_readFiltered(ADCReader_t *reader);

#endif /* INC_ADC_READER_H_ */