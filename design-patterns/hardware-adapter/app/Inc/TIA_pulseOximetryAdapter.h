#ifndef TIA_PULSEOXIMETRYADAPTER_H_
#define TIA_PULSEOXIMETRYADAPTER_H_

#include "TIA_photoDiodeProxy.h"
#include "pulseOximetrySensor.h"


typedef struct TIA_pulseOximetryAdapter TIA_pulseOximetryAdapter;

struct TIA_pulseOximetryAdapter
{
    pulseOximetrySensor *pulseOximetrySensor;
    TIA_photoDiodeProxy *itsTIA_photoDiodeProxy;
};

TIA_pulseOximetryAdapter *TIA_pulseOximetryAdapter_create(void);
void TIA_pulseOximetryAdapter_destroy(TIA_pulseOximetryAdapter *const me);

void TIA_pulseOximetryAdapter_init(TIA_pulseOximetryAdapter *const me);
void TIA_pulseOximetryAdapter_cleanup(TIA_pulseOximetryAdapter *const me);

uint32_t TIA_pulseOximetryAdapter_readSpo2(TIA_pulseOximetryAdapter *const me);
uint32_t TIA_pulseOximetryAdapter_readPulse(TIA_pulseOximetryAdapter *const me);

#endif /* TIA_PULSEOXIMETRYADAPTER_H_ */