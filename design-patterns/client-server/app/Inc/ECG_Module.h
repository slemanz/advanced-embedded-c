#ifndef INC_ECG_MODULE_H_
#define INC_ECG_MODULE_H_

#include <stdint.h>
#include "ECGPkg.h"

typedef struct ECG_Module ECG_Module;

struct ECG_Module{
    uint32_t dataNum;
    uint32_t lead1;
    uint32_t lead2;
    struct TMDQueue *itsTMDQueue;
};

ECG_Module *ECG_Module_create(void);
void ECG_Module_init(ECG_Module *const me);
void ECG_Module_aquireValue(ECG_Module *const me);
void ECG_Module_setLeadPair(ECG_Module *const me, uint32_t l1, uint32_t l2);
struct TMDQueue *ECG_Module_getsItsTMDQueue(ECG_Module *const me);
void ECG_Module_setItsTMDQueue(ECG_Module *const me, struct TMDQueue *pTMDQueue);
void ECG_Module_cleanUp(ECG_Module *const me);
void ECG_Module_destroy(ECG_Module *const me);

#endif /* INC_ECG_MODULE_H_ */