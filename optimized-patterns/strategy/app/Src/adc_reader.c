#include "adc_reader.h"

void ADCReader_init(ADCReader_t *reader, ADCInterface_t *adc, FilterStrategy_t *filter)
{
    reader->adc = adc;
    reader->filter = filter;
}

uint32_t ADCReader_readFiltered(ADCReader_t *reader)
{
    uint32_t raw = reader->adc->read();

    return (reader->filter->filter(reader->filter, raw));
}