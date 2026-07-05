#include <stdio.h>
#include "observer.h"

void uart_observer_update(struct  observer *self, int data)
{
    printf("UART Observer: received sensor data %d\n", data);
}

observer_t uart_observer = {
    .update = uart_observer_update
};



