#ifndef INC_ENVIRONMENTAL_DATA_H_
#define INC_ENVIRONMENTAL_DATA_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct enviromental_data{
    uint32_t temperature;
    uint32_t humidity;
    bool sprayed;
}env_data_t;


#endif /* INC_ENVIRONMENTAL_DATA_H_ */