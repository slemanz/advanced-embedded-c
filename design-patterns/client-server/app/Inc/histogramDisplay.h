#ifndef INC_HISTOGRAMDISPLAY_H_
#define INC_HISTOGRAMDISPLAY_H_

#include <stdint.h>
#include "ECGPkg.h"

typedef struct histogramDisplay histogramDisplay;

struct histogramDisplay{
    uint32_t index;
    struct TMDQueue *itsTMDQueue;
};

histogramDisplay *histogramDisplay_create(void);

void histogramDisplay_init(histogramDisplay *const me);
void histogramDisplay_getValue(histogramDisplay *const me);
void histogramDisplay_update(histogramDisplay *const me);
void histogramDisplay_setItsTMDQueue(histogramDisplay *const me, struct TMDQueue *pTMDQueue);

void histogramDisplay_destroy(histogramDisplay *const me);

#endif /* INC_HISTOGRAMDISPLAY_H_ */