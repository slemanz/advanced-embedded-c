#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include <stdint.h>

#define TAMP_STAMP_IRQn             2
#define RTC_Alarm_IRQn              41

void interrupt_config(uint8_t IRQNumber, uint8_t EnorDi);
void interrupt_priorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

#endif /* INC_DRIVER_INTERRUPT_H_ */