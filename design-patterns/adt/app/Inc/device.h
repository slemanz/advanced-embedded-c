#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include "address.h"
#include <stdbool.h>

typedef bool State_t;

/* Pointer to an incomplete type */
/* This hides implementation details */
typedef struct Device* DevicePtr;

DevicePtr device_create(const char *name, const Address *address);

void device_turnOn(DevicePtr device);
void device_turnOff(DevicePtr device);
void device_toggle(DevicePtr device);

State_t device_read(DevicePtr device);
void device_destroy(DevicePtr device);
void device_displayInfo(DevicePtr device);

#endif /* INC_DEVICE_H_ */