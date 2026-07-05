#include "TMDQueue.h"
#include <stdlib.h>
#include <stdio.h>

uint32_t TMDQueue_getNextIndext(TMDQueue *const me, uint32_t index)
{
    return (index + 1)%QUEUE_SIZE;
}

TMDQueue *TMDQueue_create(void)
{
    TMDQueue *me = (TMDQueue*)malloc(sizeof(TMDQueue));

    if(me != NULL)
    {
        // init queue
    }

    return me;
}

void TMDQueue_init(TMDQueue *const me)
{
    me->head = 0;
    me->size = 0;
}

void TMDQueue_insert(TMDQueue *const me, const timeMarkedData tmd)
{
    printf("Inserting at: %ld TimeInterval #: %ld\n", me->head, tmd.timeInterval);
    me->buffer[me->head] = tmd;
    me->head = TMDQueue_getNextIndext(me, me->head);

    if(me->size < QUEUE_SIZE) ++me->size;
    printf("Storing data value: %ld\n\r", tmd.dataValue);
}

uint8_t TMDQueue_isEmpty(TMDQueue *const me)
{
    return (uint8_t)(me->size == 0);
}

timeMarkedData TMDQueue_remove(TMDQueue *const me, uint32_t index)
{
    timeMarkedData tmd;
    tmd.timeInterval = 99999;
    tmd.dataValue = 99999;

    if(!TMDQueue_isEmpty(me) && (index < QUEUE_SIZE) && (index < me->size))
    {
        tmd = me->buffer[index];
    }

    return tmd;
}

void TMDQueue_cleanUp(TMDQueue *const me)
{
    // do something
    printf("Clean up complete...\n");
}

void TMDQueue_destroy(TMDQueue *const me)
{
    if(me != NULL)
    {
        TMDQueue_cleanUp(me);
    }
    free(me);
}