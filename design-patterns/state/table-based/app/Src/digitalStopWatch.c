#include "digitalStopWatch.h"
#include "timeSource.h"

#include <stdlib.h>
#include <stdio.h>

#define NO_OF_EVENTS        2
#define NO_OF_STATES        2

typedef enum{
    stopped,
    started
}State;

typedef enum{
    stopEvent,
    startEvent
}Events;

struct digitalStopWatch{
    State state;
    TimeSource source;
    const char *name;
};

static State transitionTable[NO_OF_STATES][NO_OF_EVENTS] = {{stopped, started}, {stopped, started}};

digitalStopWatchPtr watch_create(const char *name, const TimeSource *tmr)
{
    digitalStopWatchPtr new_watch = (digitalStopWatchPtr)calloc(sizeof(digitalStopWatchPtr), sizeof(digitalStopWatchPtr));
    if(new_watch)
    {
        new_watch->state = stopped;
        new_watch->name = name;
        new_watch->source.timer = tmr->timer;
        printf("Watch created succesfully\n");
    }
    else
    {
        printf("Low memory. Could not create watch.\n");
    }

    return new_watch;
}

void watch_start(digitalStopWatchPtr instance, long max_time, long *current_count)
{
    const State currentState = instance->state;

    switch (currentState)
    {
        case started:
            printf("Watch has already started\n");
            break;
        
        case stopped:
            instance->state = started;
            printf("STARTED\n");
            switch (instance->source.timer)
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
            break;

        default:
            printf("State does not exist.\n");
            break;
    }
    instance->state = transitionTable[currentState][startEvent];
}

void watch_stop(digitalStopWatchPtr instance)
{
    const State currentState = instance->state;

    switch (currentState)
    {
        case started:
            instance->state = stopped;
            switch (instance->source.timer)
            {
                case TIMER2:
                    timer2_sec_reset();
                    break;
                case TIMER_SYSTICK:
                    systick_millis_reset();
                default:
                    break;
            }
            printf("STOPPED\n");

        case stopped:
            printf("Watch has already stopped!\n");
            break;
        default:
            printf("State does not exist.\n");
            break;
    }
    instance->state = transitionTable[currentState][stopEvent];
}