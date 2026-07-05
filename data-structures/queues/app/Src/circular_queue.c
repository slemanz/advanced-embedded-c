#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"

#define QUEUE_SIZE          32
#define ADC_BUFFER_SIZE     64

/* Structure to represent the queue */
typedef struct{
    uint8_t buffer[QUEUE_SIZE]; // Fixed-size buffer for queue storage
    volatile uint8_t head;      // Index of the first element
    volatile uint8_t tail;      // Index of the next insertion point
}Queue_t;

/* Queue instance for UART Rx buffer */
static Queue_t uart_rx_queue = {.head = 0, .tail = 0};

/* Structure to represent the adc queue */
typedef struct{
    uint8_t buffer[ADC_BUFFER_SIZE];    // Fixed-size buffer for adc samples
    volatile uint8_t head;              // Index of the first element
    volatile uint8_t tail;              // Index of the next insertion point
}ADC_Queue_t;

/* Queue instance for ADC buffer */
static ADC_Queue_t adc_data_queue = {.head  = 0, .tail = 0};

/* Declare enum for possible commands to perform */
typedef enum
{
    COMMAND_LED_ON,
    COMMAND_LED_OFF,
    COMMAND_READ_ADC
}Command_type_t;

/* Structure for a single command */
typedef struct 
{
    Command_type_t command_type;
    uint64_t time;
}Command_t;

/* Structure to represent the command queue */
typedef struct
{
    Command_t buffer[QUEUE_SIZE];     // Fixed-size buffer for adc samples
    volatile uint8_t head;          // Index of the first element
    volatile uint8_t tail;          // Index of the next insertion point
}Command_queue_t;

/* Queue instance for command buffer */
static Command_queue_t command_queue = {.head = 0, .tail = 0};

/**
 * QUEUE IS FULL
 */

bool is_uart_queue_full(void)
{
    return (((uart_rx_queue.tail + 1) % QUEUE_SIZE) == uart_rx_queue.head);
}

bool is_adc_queue_full(void)
{
    return (((adc_data_queue.tail + 1) % ADC_BUFFER_SIZE) == adc_data_queue.head);
}

bool is_command_queue_full(void)
{
    return (((command_queue.tail + 1) % QUEUE_SIZE) == command_queue.head);
}

/**
 * QUEUE IS EMPTY
 */

bool is_uart_queue_empty(void)
{
    return (uart_rx_queue.tail == uart_rx_queue.head);
}

bool is_command_queue_empty(void)
{
    return (command_queue.tail == command_queue.head);
}

bool is_adc_queue_empty(void)
{
    return (adc_data_queue.tail == adc_data_queue.head);
}

/**
 * ENQUEUING
 */

bool enqueue_uart(uint8_t data)
{
    if(is_uart_queue_full())
    {
        return false;
    }

    uart_rx_queue.buffer[uart_rx_queue.tail] = data; // store data into buffer
    uart_rx_queue.tail = (uart_rx_queue.tail + 1) % QUEUE_SIZE; // move tail to the next position
    return true;
}

bool enqueue_command(Command_t command)
{
    if(is_command_queue_full())
    {
        return false;
    }

    command_queue.buffer[command_queue.tail] = command; // store data into buffer
    command_queue.tail = (command_queue.tail + 1) % QUEUE_SIZE; // move tail to the next position
    return true;
}

bool enqueue_adc(uint32_t data)
{
    if(is_adc_queue_full())
    {
        return false;
    }

    adc_data_queue.buffer[adc_data_queue.tail] = data; // store data into buffer
    adc_data_queue.tail = (adc_data_queue.tail + 1) % ADC_BUFFER_SIZE; // move tail to the next position
    return true;
}

/**
 * DEQUEUING
 */

bool dequeue_uart(uint8_t *data)
{
    if(is_uart_queue_empty())
    {
    	return false;
    }

    *data =  uart_rx_queue.buffer[uart_rx_queue.head];  //Retrieve data
    uart_rx_queue.head =  (uart_rx_queue.head + 1)% QUEUE_SIZE;  // Move front to the next element
	return true;
}

bool dequeue_command(Command_t *command)
{
    if(is_command_queue_empty())
    {
        return false;
    }

    *command = command_queue.buffer[command_queue.head]; // retrieve data
    command_queue.head = (command_queue.head + 1) % QUEUE_SIZE; // move front to the next element
    return true;
}

bool dequeue_adc(uint32_t *data)
{
    if(is_adc_queue_empty())
    {
    	return false;
    }

    *data =  adc_data_queue.buffer[adc_data_queue.head];  //Retrieve data
    adc_data_queue.head =  (adc_data_queue.head + 1) % ADC_BUFFER_SIZE;  // Move front to the next element
	return true;
}

/**
 * PROCESSING
 */

static void process_uart_data(void);
static void collect_adc_data(void);
static void process_commands(void);

int main(void)
 {
    config_drivers();
    config_bsp();

    adc_start_conversion();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        if((ticks_get() - start_time) >= 1000)
        {
            process_uart_data();
            process_commands();
            collect_adc_data();
            start_time = ticks_get();
        }
    }
}

uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
        enqueue_uart(received_data);
    }
}

/**
 * PROCESSING IMPLEMENTATION
 */

static void process_uart_data(void)
{
    uint8_t received_byte;
    while(dequeue_uart(&received_byte))
    {
        Command_t command;
        switch (received_byte)
        {
            case '1':
                command.command_type = COMMAND_LED_ON;
                enqueue_command(command);
                break;

            case '2':
                command.command_type = COMMAND_LED_OFF;
                enqueue_command(command);
                break;

            case '3':
                command.command_type = COMMAND_READ_ADC;
                enqueue_command(command);
                break;
            
            default:
                break;
        }
    }

}

static void process_commands(void)
{
    Command_t command;

    while(dequeue_command(&command))
    {
        switch (command.command_type)
        {
            case COMMAND_LED_ON:
                led_off();
                printf("Led turned on\n");
                break;
            case COMMAND_LED_OFF:
                led_on();
                printf("Led turned off\n");
                break;
            case COMMAND_READ_ADC:
                uint32_t adc_value;
                while(dequeue_adc(&adc_value))
                {
                    printf("ADC value: %lu\n", adc_value);
                }
                break;
            default:
                break;
        }
    }
}

static void collect_adc_data(void)
{
    uint32_t adc_value =  adc_read();
	if(!enqueue_adc(adc_value))
    {
        printf("Adc buffer is full!\n");
    }
}