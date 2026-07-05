#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "stdint.h"

#define SECTOR0_BASE_ADDRESS		0x08000000 /* Bootloader sector*/
#define SECTOR1_BASE_ADDRESS		0x08004000 /* Factory APP sector*/
#define SECTOR2_BASE_ADDRESS		0x08008000 /* APP sector*/


#define FACTORY_APP_ADDRESS		SECTOR1_BASE_ADDRESS
#define DEFAULT_APP_ADDRESS		SECTOR2_BASE_ADDRESS

#define MSP_VERIFY_MASK			    0x2FFE0000
#define EMPTY_MEM					0xFFFFFFFF

#define LED_PORT        GPIOC
#define LED_PIN         GPIO_PIN_NO_13

#define MEM_CHECKK_V2

void config_drivers(void);
void config_bsp(void);

void jmp_to_app(uint32_t addr_value);

#endif /* INC_CONFIG_H_ */