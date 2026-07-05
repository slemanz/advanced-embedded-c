#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"

// Global variable (static allocation in .bss section if unintialized .data if initialized)
int global_counter = 10;


// Constant variable (stored in flash)
const float PI = 3.14159;

// Function demonstrating local and static variables
void staticFunctionDemo()
{
    static int static_counter = 0;  // static variable (allocated once in .data section)
    int local_counter = 0;          // local variable (allocated on the stack)

    static_counter++;               // Static variable retains value across calls
    local_counter++;                // Local variable resets each function call

    printf("Inside staticFunctionDemo:\n");
    printf("Static Counter (persistent): %d\n", static_counter);
    printf("Local Counter (Resets Every call): %d\n\n", local_counter);
}

// Function using global variables
void updateGlobalCounter()
{
    global_counter += 5; // Global variables can be modified anywhere in the program
    printf("Global counter updated: %d\n\n", global_counter);
}

struct Sensor
{
    int id;
    float temperature;
};

// Function demonstrating static allocation of struct
void staticStructDemo()
{
    static struct Sensor sensor1 = {1, 25.5}; // static allocted struct

    printf("Sensor ID: %d, Temperature: %.2f °C\n\n", sensor1.id, sensor1.temperature);
}

// Function demonstrating an array with static alloation
void staticArrayDemo()
{
    static int arr[5] = {10, 20, 30, 40, 50};
    printf("Static Array Contents: ");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}


int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    uint64_t start_time = ticks_get();
    printf("### Static Memory Allocation Demonstration ###\n\n");

    // display inital global counter
    printf("Initial Global counter: %d\n\n", global_counter);

    // call function that modifies global variable
    updateGlobalCounter();

    // Call function mltiple times to show persistence of static variable
    staticFunctionDemo();
    staticFunctionDemo();
    staticFunctionDemo();

    // Demonstrating Static Allocation in array
    staticStructDemo();

    // Demonstrating static allocation in array
    staticArrayDemo();

    // Accessing constant variable
    printf("Constant PI Value: %.5f (stored in flash)\n", PI);

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            led_toggle();
            start_time = ticks_get();
        }

    }
}