#include "driver_uart.h"


static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_periphClkEnable(UART_RegDef_t *pUART, uint8_t EnorDi);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

static void uart_periphClkEnable(UART_RegDef_t *pUART, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUART == UART2)
        {
            UART2_PCLK_EN();
        }
    }else
    {
        if(pUART == UART2)
        {
            UART2_PCLK_DI();
        }
    }
}


void uart2_init(void)
{
    uart2_init_pins();
    UART2_PCLK_EN();

    // no flow control (default reset)
    uint32_t temp = ((UART_CR1_TE) | (1 << 2)); // tx and rx enable
    UART2->CR1 = temp; 
    UART2->BRR = compute_uart_div(16000000, 115200); // baurate

    UART2->CR1 |= UART_CR1_UE;// enable uart periph
}

void uart2_write_byte(uint8_t data)
{
	while(!(UART2->SR & UART_SR_TXE));
    UART2->DR = data;
}

void uart2_write(const char *data, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        uart2_write_byte((uint8_t)data[i]);
    }
}

void uart2_init_pins(void)
{
    GPIO_Handle_t UartPin;

    UartPin.pGPIOx = GPIOA;
    UartPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    UartPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    UartPin.GPIO_PinConfig.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;

    GPIO_Init(&UartPin);
}

UART_Singleton_t *uart_get_instance(void)
{
    static UART_Singleton_t uart_singleton = {UART2, 0};

    if(!(uart_singleton.is_initialized))
    {
        uart2_init_pins();
        uart_periphClkEnable(uart_singleton.uart_handle, ENABLE);

        uint32_t temp = ((UART_CR1_TE) | (1 << 2)); // tx and rx enable
        uart_singleton.uart_handle->CR1 = temp; 
        uart_singleton.uart_handle->BRR = compute_uart_div(16000000, 115200); // baurate
        uart_singleton.uart_handle->CR1 |= UART_CR1_UE;// enable uart periph

        uart_singleton.is_initialized = 1;
        //uart2_write("\nInit singleton\n", 16);
    }

    return &uart_singleton;
}

void uart_write(UART_Singleton_t *uart_singleton, int ch)
{
    while(!(uart_singleton->uart_handle->SR & UART_SR_TXE));
    uart_singleton->uart_handle->DR = (ch & 0xFF);
}
