#include "motorProxy.h"
#include <stdio.h>

static uint32_t marshal(const motorData mData);
static motorData unmarshal(uint32_t encodedMData);
static void _motorproxy_init(motorProxy *const me, const char *name);

void motorProxy_initialize(motorProxy *const me)
{
    motorData mData;
    if(!me->motorData)
    {
        return;
    }

    mData.on_off =                  1;
    mData.direction =               0;
    mData.speed =                   0;
    mData.errorStatus =             0;
    mData.noPowerError =            0;
    mData.noTorqueError =           0;
    mData.BITError =                0;
    mData.overTemperatureError =    0;
    mData.reserverdError1 =         0;
    mData.reserverdError2 =         0;
    mData.unknownError =            0;

    *me->motorAddr = marshal(mData);
    printf("%s, 0x%lX, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

motorProxy* motorProxy_create(const char *name)
{
    motorProxy *me = (motorProxy *)malloc(sizeof(motorProxy));
    if(me)
    {
        _motorproxy_init(me, name);
    }

    return me;
}

void motorProxy_destroy(motorProxy *const me)
{
    if(me)
    {
        motorProxy_cleanUp(me);
    }

    free(me);
}

static void _motorproxy_init(motorProxy *const me, const char *name)
{
    me->motorAddr = NULL;
    me->name = name;
}

void motorProxy_cleanUp(motorProxy *const me)
{

}

void motorProxy_enable(motorProxy *const me)
{
    if(!me->motorData)
    {
        return;
    }

    *me->motorAddr |= 1;

    printf("%s, 0x%lX, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void motorProxy_disable(motorProxy *const me)
{
    if(!me->motorData)
    {
        return;
    }

    *me->motorAddr &= ~1;

    printf("%s, %ld, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

/*
    Fn: MotorProxy_configure
*/
void motorProxy_configure(motorProxy *const me, uint32_t length, volatile uint32_t *location, uint32_t *motorData)
{
    me->rotaryArmLength = length;
    me->motorAddr = location;
    me->motorData = motorData;

    printf("%s, 0x%lX, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

Direction_e motorProxy_accessMotorDirection(motorProxy *const me)
{
    motorData mData;
    if(!me->motorData)
    {
        return 0;
    }

    mData = unmarshal((*me->motorAddr));

    return mData.direction;
}

uint32_t motorProxy_accessMotorSpeed(motorProxy *const me)
{
    motorData mData;
    if(!me->motorData)
    {
        return 0;
    }

    mData = unmarshal((*me->motorAddr));

    return mData.speed;
}

uint32_t motorProxy_accessMotorState(motorProxy *const me)
{
    motorData mData;
    if(!me->motorData)
    {
        return 0;
    }

    mData = unmarshal((*me->motorAddr));

    return mData.errorStatus;
}

void motorProxy_writeMotorSpeed(motorProxy *const me, Direction_e direction, uint32_t speed)
{
    motorData mData;
    double dPi = 3.14159, dArmLength, dSpeed, dAdjSpeed;

    if(!me->motorData)
    {
        return;
    }

    if(me->rotaryArmLength > 0)
    {
        mData = unmarshal((*me->motorAddr));
        dSpeed = speed;
        mData.direction = direction;
        dArmLength = me->rotaryArmLength;
        dAdjSpeed = dSpeed/2.0/dPi/dArmLength*10.0;
        mData.speed = (int)dAdjSpeed;
    }else
    {
        mData.speed = speed;
    }

    *me->motorAddr = marshal(mData);
    printf("%s, 0x%lX, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void motorProxy_clearErrorStatus(motorProxy *const me)
{
    if(!me->motorAddr)
    {
        return;
    }

    *me->motorAddr &= ~(1 << 8);
}

static uint32_t marshal(const motorData mData)
{
    uint32_t deviceCmd = 0;

    if(mData.on_off) deviceCmd |= (1 << 0);

    if(mData.direction == FORWARD)
    {
        deviceCmd |= (2 << 1);
    }else if(mData.direction == REVERSE)
    {
        deviceCmd |= (1 << 1);
    }

    if(mData.speed < 32) deviceCmd |= (mData.speed << 3); // 5 bits

    if(mData.errorStatus)           deviceCmd |= (1 << 8);
    if(mData.noPowerError)          deviceCmd |= (1 << 9);
    if(mData.noTorqueError)         deviceCmd |= (1 << 10);
    if(mData.BITError)              deviceCmd |= (1 << 11);
    if(mData.overTemperatureError)  deviceCmd |= (1 << 12);
    if(mData.reserverdError1)       deviceCmd |= (1 << 13);
    if(mData.reserverdError2)       deviceCmd |= (1 << 14);
    if(mData.unknownError)          deviceCmd |= (1 << 15);

    return deviceCmd;
}

static motorData unmarshal(uint32_t encodedMData)
{
    motorData mData;
    int temp;

    mData.on_off = (encodedMData & 1);

    temp = (encodedMData & (0x3 << 1)) >> 1;

    if(temp == 1)
    {
        mData.direction = REVERSE;
    }else if(temp == 2)
    {
        mData.direction = FORWARD;
    }else
    {
        mData.direction = NO_DIRECTION;
    }

    mData.speed =                   (encodedMData >> 3)  & 31;
    mData.errorStatus =             (encodedMData >> 8)  & 1;
    mData.noPowerError =            (encodedMData >> 9)  & 1;
    mData.noTorqueError =           (encodedMData >> 10) & 1;
    mData.BITError =                (encodedMData >> 11) & 1;
    mData.overTemperatureError =    (encodedMData >> 12) & 1;
    mData.reserverdError1 =         (encodedMData >> 13) & 1;
    mData.reserverdError2 =         (encodedMData >> 14) & 1;
    mData.unknownError =            (encodedMData >> 15) & 1;

    return mData;
}