#ifndef INC_SUBJECT_H_
#define INC_SUBJECT_H_

#include "observer.h"

#define MAX_OBSERVERS       5

typedef struct subject{
    // array of pointers to attached observers
    observer_t *observer_list[MAX_OBSERVERS];

    // the current count of attached observers
    int observer_count;

    // the sensor data
    int sensor_data;
}subject_t;

void subject_notify(subject_t *self);
void subject_detach(subject_t *self, observer_t *obs);
void subject_attach(subject_t *self, observer_t *obs);

#endif /* INC_SUBJECT_H_ */