#ifndef INC_ADC_INTERFACE_H_
#define INC_ADC_INTERFACE_H_

#include <stdint.h>

typedef struct
{
    uint32_t (*read)(void);
}ADCInterface_t;

extern const ADCInterface_t BaseADC;

#endif /* INC_ADC_INTERFACE_H_ */
