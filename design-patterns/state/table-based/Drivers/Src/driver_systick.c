#include "driver_systick.h"

uint64_t ticks = 0;

void systick_init(uint32_t freq, uint32_t cpu_freq)
{
    systick_set_frequency(freq, cpu_freq);
    systick_counter(ENABLE);
    systick_interrupt(ENABLE);
}

void systick_deinit(void)
{
    systick_counter(DISABLE);
    systick_interrupt(DISABLE);
}

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq)
{
    SYSTICK->LOAD   = (cpu_freq/freq) - 1;
    SYSTICK->VAL = 0;
}

void systick_counter(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        SYSTICK->CTRL = (SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSRC);
    }else
    {
        SYSTICK->CTRL &= ~(SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSRC);
    }
}

void systick_interrupt(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        SYSTICK->CTRL |= SYSTICK_CTRL_TICKINT;
    }else
    {
        SYSTICK->CTRL &= ~SYSTICK_CTRL_TICKINT;
    }
}

uint64_t ticks_get(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}