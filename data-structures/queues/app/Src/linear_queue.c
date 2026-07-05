#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"
#include "driver_rtc.h"

#define QUEUE_SIZE     32

/* Structre to represent the queue */
typedef struct {
    uint8_t buffer[QUEUE_SIZE]; // Fixed-size buffer for queue storage
    uint8_t front;              // Index of the first element
    uint8_t rear;               // Index of the next insertion point
    uint8_t length;             // Number of elements currently in the queue
} Queue_t;

/* Queue instance for the UART RX buffer */
static Queue_t uart_rx_queue = {.front = 0, .rear = 0, .length = 0};

bool queue_is_full()
{
    return (uart_rx_queue.length == QUEUE_SIZE);
}

bool queue_is_empty()
{
    return (uart_rx_queue.length == 0);
}

/**
 * @brief Add an element to the end of the queue
 * @param data The byte to be added to the queue
 * @retval true if successful, false if queue is full
 */
bool queue_enqueue(uint8_t data)
{
    if(queue_is_full())
    {
    	return false;
    }

    if(uart_rx_queue.rear >= QUEUE_SIZE) return false;

    uart_rx_queue.buffer[uart_rx_queue.rear] = data;    //Store data into buffer
    uart_rx_queue.rear++;                               // Move rear to the next position
    uart_rx_queue.length++;                             //Increase the number of stored elements

	return true;
}

/**
 * @brief Remove and return the front element from the queue
 * @param data Pointer to where the retrieved byte will be stored
 * @retval true if successful, false if queue is empty
 */
bool queue_dequeue(uint8_t *data)
{
    if(queue_is_empty())
    {
    	return false;
    }

    if(uart_rx_queue.front >= QUEUE_SIZE) return false;

    *data =  uart_rx_queue.buffer[uart_rx_queue.front]; //Retrieve data
    uart_rx_queue.front++;                              // Move front to the next element
    uart_rx_queue.length--;                             //Decrease the number of stored elements

	return true;
}

void process_uart_data();

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            process_uart_data();
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
        queue_enqueue(received_data);
    }
}

void process_uart_data()
{
    uint8_t rcv_data;
    while(!queue_is_empty())
    {
        queue_dequeue(&rcv_data);
        printf("Processed UART Byte: %c\n\r", rcv_data);
    }
}