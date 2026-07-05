#ifndef INC_DIGITALSTOPWATCH_H_
#define INC_DIGITALSTOPWATCH_H_

#include "timeSource.h"

typedef struct digitalStopWatch *digitalStopWatchPtr;

digitalStopWatchPtr watch_create(const char *name, const TimeSource *tmr);
void watch_start(digitalStopWatchPtr instance, long max_time, long *current_count);
void watch_stop(digitalStopWatchPtr instance);
void watch_destroy(digitalStopWatchPtr instance);


#endif /* INC_DIGITALSTOPWATCH_H_ */