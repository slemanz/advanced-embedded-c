#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "stm32f401xx.h"

#define UART_CR1_TE					(1U<<3)
#define UART_CR1_UE					(1U<<13)
#define UART_SR_TXE					(1U<<7)

void uart2_init(void);
void uart2_init_pins(void);
void uart2_write_byte(uint8_t data);

#endif /* INC_DRIVER_UART_H_ */
