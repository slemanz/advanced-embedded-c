#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "stm32g0.h"

void uart2_init(void);
int uart2_write(int ch);
int uart2_read(void);

#endif /* INC_DRIVER_UART_H_ */