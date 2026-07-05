#include <stdio.h>
#include "subject.h"

// notify all observers with current sensor data
void subject_notify(subject_t *self)
{
    for(uint8_t i = 0; i < self->observer_count; i++)
    {
        if(self->observer_list[i] && self->observer_list[i]->update)
        {
            // call the observers update function and pass the current sensor data
            self->observer_list[i]->update(self->observer_list[i], self->sensor_data);
        }
    }
}

// attach an observer to the subject
void subject_attach(subject_t *self, observer_t *obs)
{
    if(self->observer_count < MAX_OBSERVERS)
    {
        self->observer_list[self->observer_count++] = obs;
    }
}

// deatach an observer from the subject
void subject_detach(subject_t *self, observer_t *obs)
{
    for(uint8_t i = 0; i < self->observer_count; i++)
    {
        if(self->observer_list[i] == obs)
        {
            // shift the remaining observers to fill the gap
            for(uint8_t j = i; j < self->observer_count - 1; j++)
            {
                self->observer_list[j] = self->observer_list[j+1];
            }
            self->observer_count--;
            break;
        }
    }
}