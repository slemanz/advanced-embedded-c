#ifndef INC_ARRYTHMIADETECTOR_H_
#define INC_ARRYTHMIADETECTOR_H_

#include "ECGPkg.h"
#include <stdint.h>

typedef struct arrythmiaDetector arrythmiaDetector;

struct arrythmiaDetector{
    uint32_t index;
    struct TMDQueue *itsTMDQueue;
    uint32_t STSegmentHeight;
    uint32_t fibrillation;
    uint32_t firstDegreeHeartBlock;
};

arrythmiaDetector *arrythmiaDetector_create(void);
void arrythmiaDetector_init(arrythmiaDetector *const me);
void arrythmiaDetector_identify(arrythmiaDetector *const me);
void arrythmiaDetector_getDataSample(arrythmiaDetector *const me);
void arrythmiaDetector_setItsTMDQueue(arrythmiaDetector *const me, struct TMDQueue *pTMDQueue);
void arrythmiaDetector_destroy(arrythmiaDetector *const me);

#endif /* INC_ARRYTHMIADETECTOR_H_ */