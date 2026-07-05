#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include "gpioStrategy.h"

typedef struct Device *devicePtr;

devicePtr device_create(const char *name, gpioStrategy deviceStrategy);
void device_change(devicePtr device, gpioStrategy newDeviceStrategy);
void device_set(devicePtr device, int device_num);
void device_destroy(devicePtr device);

#endif /* INC_DEVICE_H_ */