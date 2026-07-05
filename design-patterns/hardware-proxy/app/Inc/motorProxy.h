#ifndef INC_MOTOR_PROXY_H_
#define INC_MOTOR_PROXY_H_

#include "motorData.h"
#include <stdlib.h>
#include <stdint.h>

struct motorProxy{
    uint32_t *motorData;
    volatile uint32_t *motorAddr;
    uint32_t rotaryArmLength;
    const char *name;
};

typedef struct motorProxy motorProxy;

motorProxy* motorProxy_create(const char *name);
void motorProxy_destroy(motorProxy *const me);

void motorProxy_initialize(motorProxy *const me);
void motorProxy_cleanUp(motorProxy *const me);
void motorProxy_enable(motorProxy *const me);
void motorProxy_disable(motorProxy *const me);
void motorProxy_configure(motorProxy *const me, uint32_t length, volatile uint32_t *location, uint32_t *motorData);

Direction_e motorProxy_accessMotorDirection(motorProxy *const me);
uint32_t motorProxy_accessMotorSpeed(motorProxy *const me);
uint32_t motorProxy_accessMotorState(motorProxy *const me);
void motorProxy_writeMotorSpeed(motorProxy *const me, Direction_e direction, uint32_t speed);
void motorProxy_clearErrorStatus(motorProxy *const me);


#endif /* INC_MOTOR_PROXY_H_ */