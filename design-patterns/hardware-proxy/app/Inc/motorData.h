#ifndef INC_MOTOR_DATA_H_
#define INC_MOTOR_DATA_H_

#include "motor.h"

typedef struct motorData motorData;

struct motorData{
    unsigned char on_off;                   // Bit range = 0
    Direction_e direction;                  // Bit range = 1-2
    unsigned int speed;                     // Bit range = 3-7
    unsigned char errorStatus;              // Bit range = 8
    unsigned char noPowerError;             // Bit range = 9
    unsigned char noTorqueError;            // Bit range = 10
    unsigned char BITError;                 // Bit range = 11
    unsigned char overTemperatureError;     // Bit range = 12
    unsigned char reserverdError1;          // Bit range = 13
    unsigned char reserverdError2;          // Bit range = 14
    unsigned char unknownError;             // Bit range = 15
};

#endif /* INC_MOTOR_DATA_H_ */