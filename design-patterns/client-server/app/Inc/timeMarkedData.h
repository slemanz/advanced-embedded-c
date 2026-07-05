#ifndef INC_TIMEMARKEDDATA_H_
#define INC_TIMEMARKEDDATA_H_

#include <stdint.h>

typedef struct timeMarkedData timeMarkedData;

struct timeMarkedData{
    uint32_t timeInterval;
    uint32_t dataValue;
};

#endif /* INC_TIMEMARKEDDATA_H_ */