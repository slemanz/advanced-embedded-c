#ifndef INC_PULSEOXIMETRYSENSOR_H_
#define INC_PULSEOXIMETRYSENSOR_H_

#include <stdint.h>


typedef struct pulseOximetrySensor pulseOximetrySensor;

struct pulseOximetrySensor
{
    uint32_t (*readSpO2)(void);
    uint32_t (*readPulse)(void);
};

#endif /* INC_PULSEOXIMETRYSENSOR_H_ */