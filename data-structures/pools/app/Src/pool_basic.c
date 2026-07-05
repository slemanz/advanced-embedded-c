#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"
#include "driver_adc.h"
#include "driver_uart.h"
#include "driver_rtc.h"

/* Configuration patameters */

#define MEMORY_POOL_SIZE        10  // Number of memory pools
#define MEMORY_BLOCK_SIZE       32  // Size of each memory block in bytes
#define ALIGNMENT               4   // Align memory blocks to 4-byte boundaries

/* Memory Pool Data Structure */
typedef struct MemBlock
{
    struct MemBlock *next;      // Pointer to the next free block
}MemBlock_t;

typedef struct{
    uint8_t pool[MEMORY_POOL_SIZE][MEMORY_BLOCK_SIZE];    // Pre-allocated memory
    MemBlock_t *freelist;               // Linked list of free block
}MemoryPool_t;

static MemoryPool_t memPool;

/**
 * @brief Initializes the memory pool by linking all blocks into a free list
 */
void MemoryPool_Init(void)
{
    memPool.freelist = (MemBlock_t*) memPool.pool;

    // Link all blocks together in a free list
    for(int i = 0; i < MEMORY_POOL_SIZE - 1; i++)
    {
        ((MemBlock_t*)memPool.pool[i])->next = (MemBlock_t*)memPool.pool[i+1];
    }

    ((MemBlock_t*)memPool.pool[MEMORY_POOL_SIZE - 1])->next = NULL; // End of list
}

/**
 * @brief Allocates a block of memory from the memory pool
 * @retval Pointer to allocated block, or NULL if poolis exhausted
 */
void *MemoryPool_Allocate(void)
{
    if(memPool.freelist == NULL)
    {
        return NULL; // no free blocks available
    }

    MemBlock_t *allocated_block = memPool.freelist; // taking first block
    memPool.freelist = allocated_block->next;

    return (void *)allocated_block;
}


/**
 * @brief  Frees a previosly allocated block, returning it to the pool
 * @param ptr Pointer to block to be free
 */
void MemoryPool_free(void *ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    MemBlock_t *block = (MemBlock_t*)ptr;
    block->next = memPool.freelist; // return the block to the free list
    memPool.freelist = block;
}

uint32_t MemoryPool_GetFreeBlockCount(void)
{
    uint32_t count = 0;

    MemBlock_t *current = memPool.freelist;
    while(current)
    {
        count++;
        current = current->next;
    }
    return count;
}


int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

    MemoryPool_Init();

    void *block1_ptr = MemoryPool_Allocate();
    printf("Free Blocks Left: %lu\n", MemoryPool_GetFreeBlockCount());

    void *block2_ptr = MemoryPool_Allocate();
    printf("Free Blocks Left: %lu\n", MemoryPool_GetFreeBlockCount());

    MemoryPool_free(block2_ptr);
    MemoryPool_free(block1_ptr);
    printf("Free Blocks Left: %lu\n", MemoryPool_GetFreeBlockCount());

    while (1)
    {   
    }
}

uint8_t received_data = 0;
void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        received_data = UART2->DR;
        uart2_write_byte(received_data);
    }
}