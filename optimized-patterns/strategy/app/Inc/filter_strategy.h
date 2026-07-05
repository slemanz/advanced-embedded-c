#ifndef INC_FILTER_STRATEGY_H_
#define INC_FILTER_STRATEGY_H_

#include <stdint.h>

/* Generic filter strategy interface using a function pointer */
typedef struct FilterStrategy_t FilterStrategy_t;

struct FilterStrategy_t{
    uint32_t (*filter)(FilterStrategy_t *strategy, uint32_t rawValue);
};


/* Concrete strategy: moving avarage filter */
/* The MovingAvarageFilter_t structure stores a small buffer and its state */
typedef struct {
    FilterStrategy_t base; // must be first to allow polymorphic use
    uint32_t samples[4];
    uint8_t index;
    uint8_t count;
} MovingAvarageFilter_t;


/* Concrete strategy: no filtering (pass-through) */
uint32_t noFilter(FilterStrategy_t *strategy, uint32_t rawValue);

uint32_t movingAvarageFilter(FilterStrategy_t *strategy, uint32_t rawValue);

#endif /* INC_FILTER_STRATEGY_H_ */