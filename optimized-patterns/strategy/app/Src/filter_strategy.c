#include "filter_strategy.h"

uint32_t noFilter(FilterStrategy_t *strategy, uint32_t rawValue)
{
    (void)strategy; // Unused

    return rawValue;
}

uint32_t movingAvarageFilter(FilterStrategy_t *strategy, uint32_t rawValue)
{
    MovingAvarageFilter_t *avg = (MovingAvarageFilter_t*)strategy;

    /* Insert new value into buffer */
    avg->samples[avg->index] = rawValue;
    avg->index = (avg->index + 1) % 4;
    if(avg->count < 4) avg->count++;

    /* Collect the avarage of the collected samples */
    uint32_t sum = 0;
    for(uint8_t i = 0; i < avg->count; i++)
    {
        sum += avg->samples[i];
    }

    return (sum / avg->count);
}