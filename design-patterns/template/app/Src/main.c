#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

void btn_update(void);

int main(void)
{
    config_drivers();
    printf("Init\n");

    uint64_t start_time = ticks_get();


    while(1)
    {
        btn_update();

        if((ticks_get() - start_time) >= 500)
        {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
            start_time = ticks_get();
        }
    }
}

uint8_t btnState = 0, btnStateOld = 1;
uint16_t adc_value = 0;
float temperature_mcu = 0.0;

void btn_update(void)
{

    btnState = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);
    if(btnState && (btnStateOld != btnState))
    {
        adc_value = adc_read(0);
        printf("Adc value: %d\n", adc_value);

        temperature_mcu = adc_read_temperature();
        printf("Temperature: %.2f C\n", temperature_mcu);

        btnStateOld = btnState;
    }else if(btnStateOld != btnState)
    {
        btnStateOld = btnState;
    }
}

