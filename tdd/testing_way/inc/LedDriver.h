#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

#include <stdint.h>

void LedDriver_Create(uint16_t * address);
void LedDriver_Destroy(void);

void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);

uint8_t LedDriver_IsOn(int ledNumber);
uint8_t LedDriver_IsOff(int ledNumber);

#endif /* INC_LED_DRIVER_H_ */