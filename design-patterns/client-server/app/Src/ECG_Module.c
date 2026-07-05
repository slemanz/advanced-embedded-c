#include "ECG_Module.h"
#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include "driver_adc.h"

ECG_Module *ECG_Module_create(void)
{
     ECG_Module *me = (ECG_Module*)malloc(sizeof(ECG_Module));
     if(me != NULL)
     {
        ECG_Module_init(me);
     }

     return me;
}

void ECG_Module_init(ECG_Module *const me)
{
    me->dataNum = 0;
    me->itsTMDQueue = NULL;
}

void ECG_Module_aquireValue(ECG_Module *const me)
{
    timeMarkedData tmd;

    tmd.dataValue = adc_read(0);
    tmd.timeInterval = ++(me->dataNum);
    TMDQueue_insert(me->itsTMDQueue, tmd);
}

void ECG_Module_setLeadPair(ECG_Module *const me, uint32_t l1, uint32_t l2)
{
    me->lead1 = l1;
    me->lead2 = l2;
}

struct TMDQueue *ECG_Module_getsItsTMDQueue(ECG_Module *const me)
{
    return (struct TMDQueue *)me->itsTMDQueue;
}

void ECG_Module_setItsTMDQueue(ECG_Module *const me, struct TMDQueue *pTMDQueue)
{
    me->itsTMDQueue = pTMDQueue;
}

void ECG_Module_cleanUp(ECG_Module *const me)
{
    // do something
}

void ECG_Module_destroy(ECG_Module *const me)
{
    if(me != NULL)
    {
        ECG_Module_cleanUp(me);
    }
    free(me);
}