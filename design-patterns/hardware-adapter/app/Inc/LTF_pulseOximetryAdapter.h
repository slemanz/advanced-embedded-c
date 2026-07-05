#ifndef LTF_PULSEOXIMETRYADAPTER_H_
#define LTF_PULSEOXIMETRYADAPTER_H_

#include "LTF_photoDiodeProxy.h"
#include "pulseOximetrySensor.h"


typedef struct LTF_pulseOximetryAdapter LTF_pulseOximetryAdapter;

struct LTF_pulseOximetryAdapter
{
    pulseOximetrySensor *pulseOximetrySensor;
    LTF_photoDiodeProxy *itsLTF_photoDiodeProxy;
};

LTF_pulseOximetryAdapter *LTF_pulseOximetryAdapter_create(void);
void LTF_pulseOximetryAdapter_destroy(LTF_pulseOximetryAdapter *const me);

void LTF_pulseOximetryAdapter_init(LTF_pulseOximetryAdapter *const me);
void LTF_pulseOximetryAdapter_cleanup(LTF_pulseOximetryAdapter *const me);

uint32_t LTF_pulseOximetryAdapter_readSpo2(LTF_pulseOximetryAdapter *const me);
uint32_t LTF_pulseOximetryAdapter_readPulse(LTF_pulseOximetryAdapter *const me);

#endif /* LTF_PULSEOXIMETRYADAPTER_H_ */