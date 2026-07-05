#include "TIA_pulseOximetryAdapter.h"
#include <stdio.h>
#include <stdlib.h>

TIA_pulseOximetryAdapter *TIA_pulseOximetryAdapter_create(void)
{
    TIA_pulseOximetryAdapter *me = (TIA_pulseOximetryAdapter*)malloc(sizeof(TIA_pulseOximetryAdapter));

    if(me != NULL)
    {
        TIA_pulseOximetryAdapter_init(me);
        printf("TIA_PulseOximetryAdapter created successfully\n");
    }else
    {
        printf("Low memory. Could not create adapter\n");
    }

    return me;
}

void TIA_pulseOximetryAdapter_destroy(TIA_pulseOximetryAdapter *const me)
{
    TIA_pulseOximetryAdapter_cleanup(me);
    printf("TIA_PulseOximetryAdapter destroyed\n");
    free(me);
}

void TIA_pulseOximetryAdapter_init(TIA_pulseOximetryAdapter *const me)
{
    me->itsTIA_photoDiodeProxy = (TIA_photoDiodeProxy*)malloc(sizeof(TIA_photoDiodeProxy));

    if(me->itsTIA_photoDiodeProxy != NULL)
    {
        me->itsTIA_photoDiodeProxy->getSpO2 = getSpO2;
        me->itsTIA_photoDiodeProxy->getPulse = getPulse;
    }
}

void TIA_pulseOximetryAdapter_cleanup(TIA_pulseOximetryAdapter *const me)
{
    // do something
    printf("Cleanup complete...\n");
}

uint32_t TIA_pulseOximetryAdapter_readSpo2(TIA_pulseOximetryAdapter *const me)
{
    double volts, computed_spo2;
    uint32_t temp;
    temp = me->itsTIA_photoDiodeProxy->getSpO2();

    volts = ((temp*3.3)/4095);
    // some alghoritm
    computed_spo2 = volts*30; // just example

    if(computed_spo2 < 80)
    {
        return 9999;
    }else
    {
        return computed_spo2;
    }
}

uint32_t TIA_pulseOximetryAdapter_readPulse(TIA_pulseOximetryAdapter *const me)
{
    double volts, computed_pulse;
    uint32_t temp;
    temp = me->itsTIA_photoDiodeProxy->getPulse();

    volts = ((temp*3.3)/4095);
    // some alghoritm
    computed_pulse = volts*25; // just example

    return computed_pulse;
}