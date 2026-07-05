#include "arrythmiaDetector.h"
#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>

arrythmiaDetector *arrythmiaDetector_create(void)
{
    arrythmiaDetector *me = (arrythmiaDetector*)malloc(sizeof(arrythmiaDetector));
    if(me != NULL)
    {
        arrythmiaDetector_init(me);
    }

    return me;
}

void arrythmiaDetector_init(arrythmiaDetector *const me)
{
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void arrythmiaDetector_identify(arrythmiaDetector *const me)
{
    // Implement arrythmia identification
}

void arrythmiaDetector_getDataSample(arrythmiaDetector *const me)
{
    timeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf("ArrythmiaDetector index: %ld TimeInterval: %ld DataValue: %ld\n", me->index, tmd.timeInterval, tmd.dataValue);
    me->index = TMDQueue_getNextIndext(me->itsTMDQueue, me->index);
}

void arrythmiaDetector_setItsTMDQueue(arrythmiaDetector *const me, struct TMDQueue *pTMDQueue)
{
    me->itsTMDQueue = pTMDQueue;
}

void arrythmiaDetector_destroy(arrythmiaDetector *const me)
{
    // do cleanup
    free(me);
}