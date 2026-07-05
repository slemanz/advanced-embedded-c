#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"

#include <stdlib.h>

// Function demonstatrating malloc()
void mallocExample()
{
    printf("\n--- malloc() example ---\n");

    // Allocating memory for 5 intengers dynamically
    int *ptr = (int *)malloc(5 * sizeof(int));

    if(ptr == NULL) // check if allocation failed
    {
        printf("Memory allocation failed!\n");
        return;
    }

    // initializing memory with values
    for(int i = 0; i < 5; i++)
    {
        ptr[i] = i*10;
    }

    // display allocated memory contents
    printf("Dynamically Allocated Array: ");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    free(ptr);
    printf("Memory freed successfully.\n");
}

// Funtion demonstrating calloc()
void callocExample()
{
    printf("\n--- calloc() Example ---\n");

    // Allocatinting memory for 5 intengers, initialized to 0
    int *ptr = (int *)calloc(5, sizeof(int));

    if(ptr == NULL) // check if allocation failed
    {
        printf("Memory allocation failed\n");
        return;
    }

    // Display allocated memory (should be initialized to 0)
    printf("Dynamic Allocated Array (initialized to 0): ");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    free(ptr);  // Freeing memory
    printf("Memory freed successfully.\n");
}

// Function demonstrating realloc()
void reallocExample()
{
    printf("\n--- realloc() Example ---\n");
    
    // Initial allocation for 3 intengers
    int *ptr = (int *)malloc(3*sizeof(int));

    if(ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    // assign values
    for(int i = 0; i < 3; i++)
    {
        ptr[i] = i*5;
    }

    // Display initial allocation
    printf("Initial Allocated Array: ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // Resize memory for 5 intengers
    ptr = (int *)realloc(ptr, 5*sizeof(int));

    if(ptr == NULL)
    {
        printf("Memory reallocation failed!\n");
        return;
    }

    // assign values to new memory locations
    for(int i = 3; i < 5; i++)
    {
        ptr[i] = i*5;
    }

    // Display redized array
    printf("Resized Array: ");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    free(ptr); // freeing memory
    printf("Memory freed sucessfully.\n");
}


// Function demonstrating double-free error
void doubleFreeExample()
{
    printf("\n--- Double-Free Example ---\n");

    int *ptr = (int *)malloc(5 * sizeof(int));

    if (ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    free(ptr);  // Free memory
    printf("Memory freed successfully.\n");

    // Attempting to free again
    // modern compilers wont let this obvious double free
    //free(ptr); // Uncommenting this line will cause a double-free warning
    printf("Double-free avoided by commenting out redundant free().\n");
}



int main(void)
 {
    config_drivers();
    config_bsp();
    uint64_t start_time = ticks_get();

    printf("### Dynamic Memory Allocation Demonstration ###\n");
    
    mallocExample();

    callocExample();
    reallocExample();

    doubleFreeExample();


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