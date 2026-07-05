#include "LTF_pulseOximetryAdapter.h"
#include <stdlib.h>
#include <stdio.h>

LTF_pulseOximetryAdapter *LTF_pulseOximetryAdapter_create(void)
{
    LTF_pulseOximetryAdapter *me = (LTF_pulseOximetryAdapter*)malloc(sizeof(LTF_pulseOximetryAdapter));

    if(me != NULL)
    {
        LTF_pulseOximetryAdapter_init(me);
        printf("LTF_PulseOximetryAdapter created successfully\n");
    }else
    {
        printf("Low memory. Could not create adapter\n");
    }

    return me;
}

void LTF_pulseOximetryAdapter_destroy(LTF_pulseOximetryAdapter *const me)
{
    LTF_pulseOximetryAdapter_cleanup(me);
    free(me);
}

void LTF_pulseOximetryAdapter_init(LTF_pulseOximetryAdapter *const me)
{
    me->itsLTF_photoDiodeProxy = (LTF_photoDiodeProxy*)malloc(sizeof(LTF_photoDiodeProxy));

    if(me->itsLTF_photoDiodeProxy != NULL)
    {
        me->itsLTF_photoDiodeProxy->accessSpO2 = accessSpO2;
        me->itsLTF_photoDiodeProxy->accessPulse = accessPulse;
    }
}

void LTF_pulseOximetryAdapter_cleanup(LTF_pulseOximetryAdapter *const me)
{
    // do something
    printf("Cleanup complete...\n");
}

uint32_t LTF_pulseOximetryAdapter_readSpo2(LTF_pulseOximetryAdapter *const me)
{
    double computed_spo2;
    
    computed_spo2 = me->itsLTF_photoDiodeProxy->accessSpO2()/9.6;

    return computed_spo2;
}

uint32_t LTF_pulseOximetryAdapter_readPulse(LTF_pulseOximetryAdapter *const me)
{
    double computed_pulse;
    
    computed_pulse = me->itsLTF_photoDiodeProxy->accessSpO2()/11;

    return computed_pulse;
}