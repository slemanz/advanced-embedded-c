#include "comm_interface.h"
#include "driver_uart.h"

static void uart_init(void)
{
    uart2_init();
}

void uart_send(uint8_t *data, uint32_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart2_write_byte(data[i]);
    }
}

void uart_deinit(void)
{
    UART2->CR1 &= ~UART_CR1_UE;
}

const CommProtocol_t UART_Protocol = {
    .init = uart_init,
    .send = uart_send,
    .receive = NULL,
    .deinit = uart_deinit
};