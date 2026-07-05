#include <stdio.h>
#include "adc_dma.h"
#include "state_read_adc.h"
#include "state_error.h"
#include "state_transmit.h"

//ADC error threshold
#define ADC_THRESHOLD 3000

extern uint16_t adc_raw_data[NUM_OF_CHANNELS];
uint32_t valid_sensor_data;

static void state_read_adc_enter(void);
static void state_read_adc_execute(void);
static void state_read_adc_exit(void);

// ADC Read state object
state_t state_read_adc = {
    .enter = state_read_adc_enter,
    .execute = state_read_adc_execute,
    .exit = state_read_adc_exit
};

static void state_read_adc_enter(void)
{
    printf("Entering ADC Read State.\n");
    adc_dma_init();
}

static void state_read_adc_execute(void)
{
    uint16_t sensor_value = adc_raw_data[1];
    printf("ADC Value: %d\n", sensor_value);

    if(sensor_value > ADC_THRESHOLD)
    {
        state_machine_set_state(&g_state_machine, &state_error);
    }else
    {
        state_machine_set_state(&g_state_machine, &state_transmit);
        valid_sensor_data  = sensor_value;
    }
}

static void state_read_adc_exit(void)
{
    printf("Exiting ADC Read State.\n");
}