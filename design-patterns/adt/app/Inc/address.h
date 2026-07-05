#ifndef INC_ADDRESS_H_
#define INC_ADDRESS_H_

#include "stm32g0.h"

typedef struct{
    GPIO_RegDef_t *Port;
    Pin_Type Pin;
}Address;

#endif /* INC_ADDRESS_H_ */