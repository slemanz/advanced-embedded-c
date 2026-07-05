#ifndef INC_TMDQUEUE_H_
#define INC_TMDQUEUE_H_

#include "ECGPkg.h"
#include "timeMarkedData.h"

typedef struct TMDQueue TMDQueue;

struct TMDQueue{
    uint32_t head;
    uint32_t size;

    timeMarkedData buffer[QUEUE_SIZE];
};

TMDQueue *TMDQueue_create(void);

void TMDQueue_init(TMDQueue *const me);
void TMDQueue_insert(TMDQueue *const me, const timeMarkedData tmd);
uint8_t TMDQueue_isEmpty(TMDQueue *const me);
timeMarkedData TMDQueue_remove(TMDQueue *const me, uint32_t index);
uint32_t TMDQueue_getNextIndext(TMDQueue *const me, uint32_t index);

void TMDQueue_cleanUp(TMDQueue *const me);
void TMDQueue_destroy(TMDQueue *const me);

#endif /* INC_TMDQUEUE_H_ */