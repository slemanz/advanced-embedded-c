#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"

typedef struct{
    uint8_t mode : 2;   // 2 bit for mode (0-3)
    uint8_t flag : 1;   // 1 bit flag (0 or 1)
    uint8_t speed : 3;  // 3 bits for speed (0-7)
}SensorConfig;

int main(void)
 {
    config_drivers();
    config_bsp();

    SensorConfig config = {2, 1, 5};
    
    printf("Mode: %d, Flag: %u, Speed: %u\n", config.mode, config.flag, config.speed);
    printf("Size of SensorConfig: %u\n", sizeof(SensorConfig));

    while (1)
    {   
    }
}