#include "unity_fixture.h"
#include "LedDriver.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, LedsOffAfterCreate)
{
    //TEST_FAIL_MESSAGE("Start here");
    virtualLeds = 0xFFFF;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, TurnOffLedOne);
}