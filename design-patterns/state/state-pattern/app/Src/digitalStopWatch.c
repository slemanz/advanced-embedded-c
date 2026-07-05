#include "digitalStopWatch.h"
#include "timeSource.h"

#include <stdlib.h>
#include <stdio.h>

#include "stoppedState.h"

struct digitalStopWatch
{
    struct watchState state;
    TimeSource source;
    const char *name;
};

digitalStopWatchPtr watch_create(const char *name, const TimeSource *tmr)
{
    digitalStopWatchPtr new_watch = (digitalStopWatchPtr)calloc(sizeof(digitalStopWatchPtr), sizeof(digitalStopWatchPtr));
    
    if(new_watch)
    {
        // initial state
        transitionToStopped(&new_watch->state);
        new_watch->name = name;
        new_watch->source.timer = tmr->timer;

        printf("Watch created successfully!\n");
    }else
    {
          printf("Low memory. Could not create watch\n");
    }

    return new_watch;
}

void watch_start(digitalStopWatchPtr instance, long max_time, long *current_count)
{
    instance->state.start(&instance->state);

    switch(instance->source.timer)
    {
        case TIMER2:
            timer2_sec_set(max_time, current_count);
            break;
        case TIMER_SYSTICK:
            systick_millis_set(max_time, current_count);
            break;
        default:
            break;
    }
}

void watch_stop(digitalStopWatchPtr instance)
{
    instance->state.stop(&instance->state);

    switch(instance->source.timer)
    {
        case TIMER2:
            timer2_sec_reset();
            break;
        case TIMER_SYSTICK:
            systick_millis_reset();
            break;
        default:
            break;
    }
}

void watch_destroy(digitalStopWatchPtr instance)
{
    free(instance);
}

