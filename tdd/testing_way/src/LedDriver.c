#include "LedDriver.h"
#include "util/RuntimeError.h"

static uint16_t *ledsAddress;
static uint16_t ledsImage;

enum
{
    ALL_LEDS_ON = ~0,
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum
{
    FIRST_LED = 1,
    LAST_LED = 16
};

static uint16_t convertLedNumberToBit(int ledNumber)
{
    return (1 << (ledNumber - 1));
}

static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}

static uint8_t isLedOutOfBounds(int ledNumber)
{
    return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}

void setLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
}

void clearLedImageBit(int ledNumber)
{
    ledsImage &= ~convertLedNumberToBit(ledNumber);
}



void LedDriver_Create(uint16_t * address)
{
    ledsAddress  = address;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_Destroy(void)
{

}

void LedDriver_TurnOn(int ledNumber)
{
    if (isLedOutOfBounds(ledNumber))
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }

    setLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if (isLedOutOfBounds(ledNumber))
        return;

    clearLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

uint8_t LedDriver_IsOn(int ledNumber)
{
    if(isLedOutOfBounds(ledNumber))
    {
        return 0;
    }
    
    return (ledsImage & (convertLedNumberToBit(ledNumber))) != 0;
}

uint8_t LedDriver_IsOff(int ledNumber)
{
    if(isLedOutOfBounds(ledNumber))
    {
        return 1;
    }
    
    return (ledsImage & (convertLedNumberToBit(ledNumber))) == 0;
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}