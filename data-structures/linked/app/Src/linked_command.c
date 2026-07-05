#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "driver_systick.h"
#include "driver_uart.h"

#include "led.h"
#include "driver_adc.h"

#define COMMAND_QUEUE_SIZE      32  // Maximum number of commands that can be stored

// Enumeration for the different kinds of commands
typedef enum{
    COMMAND_LED_ON = 1, // Turn the LED on
    COMMAND_LED_OFF,    // Turn the LED off
    COMMAND_READ_ADC    // Read the ADC value
}CommandType_t;

// Struct representing the command.
typedef struct{
    CommandType_t command_type;     // type of command
    uint32_t data;                  // command data
}Command_t;

// Structure to represent a node in the linked list
typedef struct node
{
    Command_t command;  // Command to be performed
    struct node *next;  // poiner to next node in the list
}Node_t;

// Structure representing the linked list of commands
typedef struct{
    Node_t *head;
}LinkedList_t;


static LinkedList_t command_queue;
static void process_commands(void);


/**
 * @brief Inserts a command at the tail of the linked list (command queue)
 * @param list Pointer to the linked list (command queue)
 * @param command The command to be added
 * @return true if successful, false if not
 */
static inline bool insert_at_tail(LinkedList_t *list, Command_t command)
{
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t)); // allocate a new node

    if(newNode == NULL)
    {
        return false; // Allocation failed
    }

    newNode->command = command;
    newNode->next = NULL;

    if(list->head == NULL)
    {
        list->head = newNode;
    }else
    {
        // if list is not empty, traverse to the last node
        Node_t* current = list->head;
        while(current->next != NULL)
        {
            // move to the next node until the last node is reached
            current = current->next;
        }

        // Link the new node to the current last node
        current->next = newNode; // add to tail
    }

    return true;
}


/**
 * @brief Removes a command from the head of the command queue.
 * @param list Pointer to the linked list.
 * @param command Pointer to store the command in.
 * @return True if successful, false if not
 */
static inline bool remove_at_head(LinkedList_t *list, Command_t *command)
{
    if(list->head == NULL)
    {
        return false; // list is empty, nothing to remove
    }

    Node_t *temp = list->head;  // get the first node.
    *command = temp->command;   // copy the command
    list->head = temp->next;    // update head
    free(temp);                 // free node memory
    return true;
}


int main(void)
 {
    config_drivers();
    config_bsp();

    adc_start_conversion();
    printf("\nInit board...\n\r");

    //uint64_t start_time = ticks_get();

    // Initialize the command queue
    command_queue.head = NULL;

    while (1)
    {   
        process_commands();
        ticks_delay(100);
    }
}

uint8_t received_data;

void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
        Command_t command; // create a new command struct

        switch(received_data)
        {
            case '1':
                command.command_type = COMMAND_LED_ON;
                command.data = 0;
                insert_at_tail(&command_queue, command);
                break;
            case '2':
                command.command_type = COMMAND_LED_OFF;
                command.data = 0;
                insert_at_tail(&command_queue, command);
                break;
            case '3':
                command.command_type = COMMAND_READ_ADC;
                command.data = adc_read();
                insert_at_tail(&command_queue, command);
                break;
            default:
                break;
        }
    }
}
            

void process_adc_command(Command_t *command)
{
    printf("ADC Value %lu\n", command->data);
}


static void process_commands(void)
{
    Command_t command;

    while(remove_at_head(&command_queue, &command))
    {
        switch (command.command_type)
        {
        case COMMAND_LED_ON:
            led_on();
            printf("LED Turned on\n");
            break;

        case COMMAND_LED_OFF:
            led_off();
            printf("LED Turned off\n");
            break;

        case COMMAND_READ_ADC:
            process_adc_command(&command);
            break;
        
        default:
            break;
        }
    }
}