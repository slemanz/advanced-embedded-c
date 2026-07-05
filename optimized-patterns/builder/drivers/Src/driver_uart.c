#include "driver_uart.h"
#include "driver_gpio.h"


static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

UART_Builder_t uart_builder_init(void)
{
    UART_Builder_t builder;
    builder.BaudRate = 115200;
    builder.WordLength = UART_WORDLENGTH_8B;
    builder.Parity = UART_PARITY_NONE;
    builder.Mode = UART_MODE_TX_RX;

    return builder;
}

void uart_build(UART_Builder_t *builder)
{
    UART2_PCLK_EN();

    // set baudrate
    UART2->BRR = compute_uart_div(APB1_CLK, builder->BaudRate);

    // Configure word length, stop bits and parity
    UART2->CR1 = (builder->WordLength | builder->Parity | builder->Mode);

    // Enable uart module
    UART2->CR1 |= UART_CR1_UE;
}

// Set baudrate
UART_Builder_t *uart_set_baudrate(UART_Builder_t *builder, uint32_t baudrate)
{
    builder->BaudRate = baudrate;
    return builder;
}


// Set word length (8-bit or 9-bit)
UART_Builder_t *uart_set_wordlength(UART_Builder_t *builder, uint32_t wordlength)
{
    builder->WordLength = wordlength;
    return builder;
}


// Set parity (None, even or odd)
UART_Builder_t *uart_set_parity(UART_Builder_t *builder, uint32_t parity)
{
    builder->Parity = parity;
    return builder;
}


// Set mode (transmit, receive or both)
UART_Builder_t *uart_set_mode(UART_Builder_t *builder, uint32_t mode)
{
    builder->Mode = mode;
    return builder;
}


/*
 * OLD IMPLEMENTATION
 */

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