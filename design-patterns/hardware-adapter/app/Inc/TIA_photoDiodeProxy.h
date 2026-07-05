#ifndef INC_TIA_PHOTODIODEPROXY_H_
#define INC_TIA_PHOTODIODEPROXY_H_

#include <stdint.h>


typedef struct TIA_photoDiodeProxy TIA_photoDiodeProxy;

struct TIA_photoDiodeProxy
{
    uint32_t (*getSpO2)(void);
    uint32_t (*getPulse)(void);
};

uint32_t getSpO2(void);
uint32_t getPulse(void);

#endif /* INC_TIA_PHOTODIODEPROXY_H_ */