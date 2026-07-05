#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include "stm32f411xx.h"

#define UART_CR1_TE					(1U<<3)
#define UART_CR1_UE					(1U<<13)
#define UART_SR_TXE					(1U<<7)

typedef struct 
{
    UART_RegDef_t *uart_handle;
    uint8_t is_initialized;
}UART_Singleton_t;

// default functions
void uart2_init(void);
void uart2_init_pins(void);
void uart2_write_byte(uint8_t data);
void uart2_write(const char *data, uint32_t len);

// singleton functions
UART_Singleton_t *uart_get_instance(void);
void uart_write(UART_Singleton_t *uart_singleton, int ch);


#endif