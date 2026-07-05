#ifndef INC_DRIVER_SYSTICK_H_
#define INC_DRIVER_SYSTICK_H_

#include "stm32g0.h"

#define SYSTICK_LOAD_VAL                     16000
#define SYSTICK_CTRL_ENABLE                 (1U << 0)
#define SYSTICK_CTRL_CLKSRC                 (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG              (1U << 16)
#define SYSTICK_CTRL_TICKINT                (1U << 1)

#define ONE_SEC_LOAD                        16000000

void systick_init(uint32_t freq, uint32_t cpu_freq);
void systick_deinit(void);

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq);
void systick_counter(uint8_t EnorDi);
void systick_interrupt(uint8_t EnorDi);

uint64_t ticks_get(void);

#endif /* INC_DRIVER_SYSTICK_H_ */