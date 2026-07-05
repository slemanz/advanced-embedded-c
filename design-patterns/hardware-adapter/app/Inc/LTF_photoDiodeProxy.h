#ifndef INC_LTF_PHOTODIODEPROXY_H_
#define INC_LTF_PHOTODIODEPROXY_H_

#include <stdint.h>


typedef struct LTF_photoDiodeProxy LTF_photoDiodeProxy;

struct LTF_photoDiodeProxy
{
    uint32_t (*accessSpO2)(void);
    uint32_t (*accessPulse)(void);
};

uint32_t accessSpO2(void);
uint32_t accessPulse(void);

#endif /* INC_LTF_PHOTODIODEPROXY_H_ */
