#include "stm32g0.h"
#include "config.h"
#include <stdio.h>
#include "env_sensor.h"
#include "env_display_client.h"
#include "fertilizer_mixer_client.h"

int main(void)
{
    config_drivers();
    printf("Init board...\n");

    // setup server
    env_sensor_t *sensor = env_sensor_create();

    // setup client 1
    display_client_t *lcd_display = display_client_create();
    display_client_subscribe(lcd_display, sensor);

    // setup client 2
    fertilizer_mixer_client_t *fertilizer_mixer = fertilizer_mixer_client_create();
    fertilizer_mixer_client_subscribe(fertilizer_mixer, sensor);

    env_sensor_get_data(sensor);
    env_sensor_get_data(sensor);

    // test2
    printf("\n\nUnsubscribe lcd display\n");
    display_client_unsubscribe(lcd_display, sensor);
    env_sensor_get_data(sensor);
    env_sensor_get_data(sensor);


    // test3
    printf("\n\nSubscribe lcd display\n");
    display_client_subscribe(lcd_display, sensor);
    env_sensor_dumplist(sensor);


    while(1)
    {

    }
}