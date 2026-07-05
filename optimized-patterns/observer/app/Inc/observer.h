#ifndef INC_OBSERVER_H_
#define INC_OBSERVER_H_

#include <stdint.h>

typedef struct observer{
    void (*update)(struct observer *self, int data);
}observer_t;

#endif /* INC_OBSERVER_H_ */