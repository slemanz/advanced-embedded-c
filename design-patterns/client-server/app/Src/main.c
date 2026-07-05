#include "stm32g0.h"
#include "config.h"
#include <stdio.h>
#include "systemManager.h"

void btn_update(void);

int main(void)
{
    config_drivers();
    printf("Init system...\n");

    systemManager *pSystemManager;
    pSystemManager = systemManager_create();

    // client 1
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));

    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));

    // client 2
    QRSDetector_getDataSample(&(pSystemManager->itsQRSDetector));
    QRSDetector_getDataSample(&(pSystemManager->itsQRSDetector));
    
    // client 1
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));

    // client 3
    arrythmiaDetector_getDataSample(&(pSystemManager->itsArrythmiaDetector));
    arrythmiaDetector_getDataSample(&(pSystemManager->itsArrythmiaDetector));
    arrythmiaDetector_getDataSample(&(pSystemManager->itsArrythmiaDetector));

    printf("Done!\n");

    while(1)
    {
    }
}