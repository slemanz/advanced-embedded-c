#include "stm32g0.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "motorProxy.h"

// client1: motor dashboard
void motor_dashboard(motorProxy *motor)
{
    uint32_t getSpeed = motorProxy_accessMotorSpeed(motor);
    uint32_t getState = motorProxy_accessMotorState(motor);
    Direction_e getDirection = motorProxy_accessMotorDirection(motor);

    printf("****************DASHBOARD************************\n");
    printf("Motor name: %s\n", motor->name);
    printf("Motor current direction: %d, speed: %ld, state: %ld\n", getDirection, getSpeed, getState);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
}

// client2: motor controller
void motor_controller(motorProxy *motor, Direction_e direction, uint32_t speed)
{
    motorProxy_writeMotorSpeed(motor, direction, speed);
}

int main(void)
{
    config_drivers();
    printf("Init\n");

    volatile uint32_t *motor1_addr = (uint32_t*)calloc(sizeof(uint32_t), sizeof(uint32_t)); // could be a gpio port (ODR)
    volatile uint32_t *motor2_addr = (uint32_t*)calloc(sizeof(uint32_t), sizeof(uint32_t)); // could be a gpio port (ODR)
    if(!(motor1_addr && motor2_addr))
    {
        printf("No memory space availabe!\n");
        return 0;
    }

    motorProxy *motor1;
    motorProxy *motor2;

    const char* motor1_name = "Base";
    motor1 = motorProxy_create(motor1_name);
    uint32_t motor1_data = 100;
    uint32_t motor1_armLength = 2;

    const char* motor2_name = "Shoulder";
    motor2 = motorProxy_create(motor2_name);
    uint32_t motor2_data = 100;
    uint32_t motor2_armLength = 15;

    motorProxy_configure(motor1, motor1_armLength, motor1_addr, &motor1_data);
    motorProxy_initialize(motor1);
    motorProxy_enable(motor1);

    motorProxy_configure(motor2, motor2_armLength, motor2_addr, &motor2_data);
    motorProxy_initialize(motor2);
    motorProxy_enable(motor2);

    motor_controller(motor1, FORWARD, 1);
    motor_controller(motor2, FORWARD, 10);

    motor_dashboard(motor1);
    motor_dashboard(motor2);

    printf("Final\n");

    while(1)
    {
    }
}