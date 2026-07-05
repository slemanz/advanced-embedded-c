#include "QRSDetector.h"
#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>

QRSDetector *QRSDetector_create(void)
{
    QRSDetector *me = (QRSDetector *)malloc(sizeof(QRSDetector));

    if(me != NULL)
    {
        QRSDetector_init(me);
    }

    return me;
}

void QRSDetector_init(QRSDetector *const me)
{
    me->heartRate = 0;
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void QRSDetector_computeHeartRate(QRSDetector *const me)
{
    // HeartRate computation
    me->heartRate = 85; // example
}

void QRSDetector_getDataSample(QRSDetector *const me)
{
    timeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf("QRSDetector index is: %ld TimeInterval: %ld Data value: %ld\n", me->index, tmd.timeInterval, tmd.dataValue);
    me->index = TMDQueue_getNextIndext(me->itsTMDQueue, me->index);
}

void QRSDetector_setItsTMDQueue(QRSDetector *const me, struct TMDQueue *pTMDQueue)
{
    me->itsTMDQueue = pTMDQueue;
}

void QRSDetector_destroy(QRSDetector *const me)
{
    // cleanup
    free(me);
}