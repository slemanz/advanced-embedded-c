#include "stm32g0.h"
#include "config.h"
#include <stdio.h>

#include "digitalStopWatch.h"

long watch_1_counter = 0;

int main(void)
{
    config_drivers();
    printf("Init\n");

    digitalStopWatchPtr stop_watch_1;

    const char *name1 = "Diag Timer";
    TimeSource timer1 = {TIMER2};
    stop_watch_1 = watch_create(name1, &timer1);
    watch_start(stop_watch_1, 20, &watch_1_counter);
    watch_stop(stop_watch_1);
    
    while(1)
    {
    }
}