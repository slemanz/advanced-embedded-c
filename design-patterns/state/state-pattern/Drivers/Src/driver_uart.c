#include "driver_uart.h"

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}


void uart2_init(void)
{
    UART2_PCLK_EN();

    uint32_t temp = ((1 << 3) | (1 << 2)); // tx and rx enable
    UART2->CR1 = temp; 
    UART2->BRR = compute_uart_div(16000000, 115200); // baurate

    UART2->CR1 |= (1 << 0);// enable uart periph
}

int uart2_write(int ch)
{
	while(!(UART2->ISR & (1 << 7)));
    UART2->TDR = ch;

    return ch;
}

int uart2_read(void)
{
	while(!(UART2->ISR & (1 << 5)));
    return UART2->RDR;

}