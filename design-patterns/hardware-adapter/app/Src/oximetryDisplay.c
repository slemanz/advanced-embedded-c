#include "oximetryDisplay.h"
#include <stdio.h>

TIA_pulseOximetryAdapter *tia_pulseOximetryAdpt;
LTF_pulseOximetryAdapter *ltf_pulseOximetryAdpt;

void oximetry_diplay_init(void)
{
    tia_pulseOximetryAdpt = TIA_pulseOximetryAdapter_create();
    ltf_pulseOximetryAdpt = LTF_pulseOximetryAdapter_create();

    uint32_t tia_spo2 = TIA_pulseOximetryAdapter_readSpo2(tia_pulseOximetryAdpt);
    uint32_t tia_pulse = TIA_pulseOximetryAdapter_readPulse(tia_pulseOximetryAdpt);

    uint32_t ltf_spo2 = LTF_pulseOximetryAdapter_readSpo2(ltf_pulseOximetryAdpt);
    uint32_t ltf_pulse = LTF_pulseOximetryAdapter_readPulse(ltf_pulseOximetryAdpt);

    printf("|************TIA Sensor*********************|\n\r");
	printf("Spo2 : %ld\n",tia_spo2);
	printf("Pulse :  %ld\n",tia_pulse);
	printf("--------------------------------------------\n\r");
	
	printf("|************LTF Sensor*********************|\n\r");
	printf("Spo2 : %ld\n",ltf_spo2);
	printf("Pulse :  %ld\n",ltf_pulse);
	printf("--------------------------------------------\n\r");
}

void oximetry_diplay_update(void)
{
    uint32_t tia_spo2 = TIA_pulseOximetryAdapter_readSpo2(tia_pulseOximetryAdpt);
    uint32_t tia_pulse = TIA_pulseOximetryAdapter_readPulse(tia_pulseOximetryAdpt);

    uint32_t ltf_spo2 = LTF_pulseOximetryAdapter_readSpo2(ltf_pulseOximetryAdpt);
    uint32_t ltf_pulse = LTF_pulseOximetryAdapter_readPulse(ltf_pulseOximetryAdpt);

    printf("|************TIA Sensor*********************|\n\r");
	printf("Spo2 : %ld\n",tia_spo2);
	printf("Pulse :  %ld\n",tia_pulse);
	printf("--------------------------------------------\n\r");
	
	printf("|************LTF Sensor*********************|\n\r");
	printf("Spo2 : %ld\n",ltf_spo2);
	printf("Pulse :  %ld\n",ltf_pulse);
	printf("--------------------------------------------\n\r");
}