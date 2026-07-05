#ifndef INC_QSRDETECTOR_H_
#define INC_QSRDETECTOR_H_

#include "ECGPkg.h"

typedef struct QRSDetector QRSDetector;

struct QRSDetector{
    uint32_t index;
    struct TMDQueue *itsTMDQueue;
    uint32_t heartRate;
};

QRSDetector *QRSDetector_create(void);
void QRSDetector_init(QRSDetector *const me);

void QRSDetector_computeHeartRate(QRSDetector *const me);
void QRSDetector_getDataSample(QRSDetector *const me);
void QRSDetector_setItsTMDQueue(QRSDetector *const me, struct TMDQueue *pTMDQueue);

void QRSDetector_destroy(QRSDetector *const me);

#endif /* INC_QSRDETECTOR_H_ */