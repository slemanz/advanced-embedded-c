#ifndef INC_STM32G0_H_
#define INC_STM32G0_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/*
 *      Most important macros
 */

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))

typedef void (*void_fn)(void);

#define ENABLE          1
#define DISABLE         0
#define FLAG_SET        ENABLE
#define FLAG_RESET      DISABLE

#define CPU_FREQ        (16000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x08000000U
#define SRAM1_BASEADDR						0x20000000U

/*
 *  Base addresses peripherals
 */

#define RCC_BASEADDR                    (0x40021000U)
#define FLASH_R_BASEADDR                (0x40022000U)
#define IWDG_BASEADDR                   (0x40003000U)

#define GPIOA_BASEADDR                  (0x50000000U)
#define GPIOB_BASEADDR                  (0x50000400U)
#define GPIOC_BASEADDR                  (0x50000800U)

#define UART1_BASEADDR                  (0x40013800U)
#define UART2_BASEADDR                  (0x40004400U)

#define SCS_BASE            				    (0xE000E000U)
#define SYSTICK_BASEADDR					      (SCS_BASE + 0x0010U)

#define ADC_BASEADDR                    (0x40012400U)
#define ADC_CCR_BASEADDR                (ADC_BASEADDR + 0x308U)

#define I2C1_BASEADDR                   (0x40005400U)
#define I2C2_BASEADDR                   (0x40005800U)

#define SPI1_BASEADDR                   (0x40013000U)
#define SPI2_BASEADDR                   (0x40003800U)
#define SPI3_BASEADDR                   (0x40003C00U)

#define DAC1_BASEADDR                   (0x40007400U)

#define TIM2_BASEADDR                   (0x40000000U)

/*
 *    INTERRUPTS
 */

// ARM-Cortex Mx Processor NVIC ISERx register addresses
#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

// ARM-Cortex Mx Processor NVIC ISERx register addresses
#define NVIC_ICER0 						((__vo uint32_t*)0xE000E180UL)
#define NVIC_ICER1 						((__vo uint32_t*)0xE000E184UL)
#define NVIC_ICER2 						((__vo uint32_t*)0xE000E188UL)
#define NVIC_ICER3 						((__vo uint32_t*)0xE000E18CUL)

// ARm Cortex Mx Processor Priority Regesiter Address Calculation
#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400UL)

/*
 *   peripheral structs
 */

typedef struct
{
  __vo uint32_t CR;          // Address offset: 0x00 */
  __vo uint32_t ICSCR;       // Address offset: 0x04 */
  __vo uint32_t CFGR;        // Address offset: 0x08 */
  __vo uint32_t PLLCFGR;     // Address offset: 0x0C */
  __vo uint32_t RESERVED0;   // Address offset: 0x10 */
  __vo uint32_t CRRCR;       // Address offset: 0x14 */
  __vo uint32_t CIER;        // Address offset: 0x18 */
  __vo uint32_t CIFR;        // Address offset: 0x1C */
  __vo uint32_t CICR;        // Address offset: 0x20 */
  __vo uint32_t IOPRSTR;     // Address offset: 0x24 */
  __vo uint32_t AHBRSTR;     // Address offset: 0x28 */
  __vo uint32_t APBRSTR1;    // Address offset: 0x2C */
  __vo uint32_t APBRSTR2;    // Address offset: 0x30 */
  __vo uint32_t IOPENR;      // Address offset: 0x34 */
  __vo uint32_t AHBENR;      // Address offset: 0x38 */
  __vo uint32_t APBENR1;     // Address offset: 0x3C */
  __vo uint32_t APBENR2;     // Address offset: 0x40 */
  __vo uint32_t IOPSMENR;    // Address offset: 0x44 */
  __vo uint32_t AHBSMENR;    // Address offset: 0x48 */
  __vo uint32_t APBSMENR1;   // Address offset: 0x4C */
  __vo uint32_t APBSMENR2;   // Address offset: 0x50 */
  __vo uint32_t CCIPR;       // Address offset: 0x54 */
  __vo uint32_t CCIPR2;      // Address offset: 0x58 */
  __vo uint32_t BDCR;        // Address offset: 0x5C */
  __vo uint32_t CSR;         // Address offset: 0x60 */
} RCC_RegDef_t;

typedef struct
{
  __vo uint32_t ACR;          /*!< Address offset: 0x00 */
  __vo uint32_t RESERVED1;    /*!< Address offset: 0x04 */
  __vo uint32_t KEYR;         /*!< Address offset: 0x08 */
  __vo uint32_t OPTKEYR;      /*!< Address offset: 0x0C */
  __vo uint32_t SR;           /*!< Address offset: 0x10 */
  __vo uint32_t CR;           /*!< Address offset: 0x14 */
  __vo uint32_t ECCR;          /*!<Address offset: 0x18 */
  __vo uint32_t ECC2R;         /*!<Address offset: 0x1C */
  __vo uint32_t OPTR;         /*!< Address offset: 0x20 */
  __vo uint32_t PCROP1ASR;    /*!< Address offset: 0x24 */
  __vo uint32_t PCROP1AER;    /*!< Address offset: 0x28 */
  __vo uint32_t WRP1AR;       /*!< Address offset: 0x2C */
  __vo uint32_t WRP1BR;       /*!< Address offset: 0x30 */
  __vo uint32_t PCROP1BSR;    /*!< Address offset: 0x34 */
  __vo uint32_t PCROP1BER;    /*!< Address offset: 0x38 */
  __vo uint32_t RESERVED5[2]; /*!< Address offset: 0x3C--0x40 */
  __vo uint32_t PCROP2ASR;    /*!< Address offset: 0x44 */
  __vo uint32_t PCROP2AER;    /*!< Address offset: 0x48 */
  __vo uint32_t WRP2AR;       /*!< Address offset: 0x4C */
  __vo uint32_t WRP2BR;       /*!< Address offset: 0x50 */
  __vo uint32_t PCROP2BSR;    /*!< Address offset: 0x54 */
  __vo uint32_t PCROP2BER;    /*!< Address offset: 0x58 */
  __vo uint32_t RESERVED7[9]; /*!< Address offset: 0x5C--0x7C */
  __vo uint32_t SECR;         /*!< Address offset: 0x80 */
} FLASH_RegDef_t;

typedef struct
{
  __vo uint32_t MODER;       /*<! Address offset: 0x00      */
  __vo uint32_t OTYPER;      /*<! Address offset: 0x04      */
  __vo uint32_t OSPEEDR;     /*<! Address offset: 0x08      */
  __vo uint32_t PUPDR;       /*<! Address offset: 0x0C      */
  __vo uint32_t IDR;         /*<! Address offset: 0x10      */
  __vo uint32_t ODR;         /*<! Address offset: 0x14      */
  __vo uint32_t BSRR;        /*<! Address offset: 0x18      */
  __vo uint32_t LCKR;        /*<! Address offset: 0x1C      */
  __vo uint32_t AFR[2];      /*<! Address offset: 0x20-0x24 */
  __vo uint32_t BRR;         /*<! Address offset: 0x28      */
}GPIO_RegDef_t;

typedef struct
{
  __vo uint32_t CR1;         /*!< Address offset: 0x00  */
  __vo uint32_t CR2;         /*!< Address offset: 0x04  */
  __vo uint32_t CR3;         /*!< Address offset: 0x08  */
  __vo uint32_t BRR;         /*!< Address offset: 0x0C  */
  __vo uint32_t GTPR;        /*!< Address offset: 0x10  */
  __vo uint32_t RTOR;        /*!< Address offset: 0x14  */
  __vo uint32_t RQR;         /*!< Address offset: 0x18  */
  __vo uint32_t ISR;         /*!< Address offset: 0x1C  */
  __vo uint32_t ICR;         /*!< Address offset: 0x20  */
  __vo uint32_t RDR;         /*!< Address offset: 0x24  */
  __vo uint32_t TDR;         /*!< Address offset: 0x28  */
  __vo uint32_t PRESC;       /*!< Address offset: 0x2C  */
}UART_RegDef_t;

typedef struct
{
  __vo uint32_t CTRL;        /*!< Address Offset: 0x000   SysTick Control and Status Register */
  __vo uint32_t LOAD;        /*!< Address Offset: 0x004   SysTick Reload Value Register */
  __vo uint32_t VAL;         /*!< Address Offset: 0x008   SysTick Current Value Register */
  __vo uint32_t CALIB;       /*!< Address Offset: 0x00C   SysTick Calibration Register */
}SysTick_RegDef_t;

typedef struct
{
  __vo uint32_t ISR;          /*!< Address offset: 0x00 */
  __vo uint32_t IER;          /*!< Address offset: 0x04 */
  __vo uint32_t CR;           /*!< Address offset: 0x08 */
  __vo uint32_t CFGR1;        /*!< Address offset: 0x0C */
  __vo uint32_t CFGR2;        /*!< Address offset: 0x10 */
  __vo uint32_t SMPR;         /*!< Address offset: 0x14 */
  __vo uint32_t RESERVED1;    /*!<                 0x18 */
  __vo uint32_t RESERVED2;    /*!<                 0x1C */
  __vo uint32_t AWD1TR;       /*!< Address offset: 0x20 */
  __vo uint32_t AWD2TR;       /*!< Address offset: 0x24 */
  __vo uint32_t CHSELR;       /*!< Address offset: 0x28 */
  __vo uint32_t AWD3TR;       /*!< Address offset: 0x2C */
  __vo uint32_t RESERVED3[4]; /*!<          0x30 - 0x3C */
  __vo uint32_t DR;           /*!< Address offset: 0x40 */
  __vo uint32_t RESERVED4[23];/*!<          0x44 - 0x9C */
  __vo uint32_t AWD2CR;       /*!< Address offset: 0xA0 */
  __vo uint32_t AWD3CR;       /*!< Address offset: 0xA4 */
  __vo uint32_t RESERVED5[3]; /*!<          0xA8 - 0xB0 */
  __vo uint32_t CALFACT;      /*!< Address offset: 0xB4 */
} ADC_RegDef_t;

typedef struct
{
  __vo uint32_t CR1;         /*!< Address offset: 0x00 */
  __vo uint32_t CR2;         /*!< Address offset: 0x04 */
  __vo uint32_t OAR1;        /*!< Address offset: 0x08 */
  __vo uint32_t OAR2;        /*!< Address offset: 0x0C */
  __vo uint32_t TIMINGR;     /*!< Address offset: 0x10 */
  __vo uint32_t TIMEOUTR;    /*!< Address offset: 0x14 */
  __vo uint32_t ISR;         /*!< Address offset: 0x18 */
  __vo uint32_t ICR;         /*!< Address offset: 0x1C */
  __vo uint32_t PECR;        /*!< Address offset: 0x20 */
  __vo uint32_t RXDR;        /*!< Address offset: 0x24 */
  __vo uint32_t TXDR;        /*!< Address offset: 0x28 */
} I2C_RegDef_t;

typedef struct
{
  __vo uint32_t CR1;          /*!<  Address offset: 0x00 */
  __vo uint32_t CR2;          /*!<  Address offset: 0x04 */
  __vo uint32_t SR;           /*!<  Address offset: 0x08 */
  __vo uint32_t DR;           /*!<  Address offset: 0x0C */
  __vo uint32_t CRCPR;        /*!<  Address offset: 0x10 */
  __vo uint32_t RXCRCR;       /*!<  Address offset: 0x14 */
  __vo uint32_t TXCRCR;       /*!<  Address offset: 0x18 */
  __vo uint32_t I2SCFGR;      /*!<  Address offset: 0x1C */
  __vo uint32_t I2SPR;        /*!<  Address offset: 0x20 */
} SPI_RegDef_t;

typedef struct
{
  __vo uint32_t CR;          /*!< Address offset: 0x00 */
  __vo uint32_t SWTRIGR;     /*!< Address offset: 0x04 */
  __vo uint32_t DHR12R1;     /*!< Address offset: 0x08 */
  __vo uint32_t DHR12L1;     /*!< Address offset: 0x0C */
  __vo uint32_t DHR8R1;      /*!< Address offset: 0x10 */
  __vo uint32_t DHR12R2;     /*!< Address offset: 0x14 */
  __vo uint32_t DHR12L2;     /*!< Address offset: 0x18 */
  __vo uint32_t DHR8R2;      /*!< Address offset: 0x1C */
  __vo uint32_t DHR12RD;     /*!< Address offset: 0x20 */
  __vo uint32_t DHR12LD;     /*!< Address offset: 0x24 */
  __vo uint32_t DHR8RD;      /*!< Address offset: 0x28 */
  __vo uint32_t DOR1;        /*!< Address offset: 0x2C */
  __vo uint32_t DOR2;        /*!< Address offset: 0x30 */
  __vo uint32_t SR;          /*!< Address offset: 0x34 */
  __vo uint32_t CCR;         /*!< Address offset: 0x38 */
  __vo uint32_t MCR;         /*!< Address offset: 0x3C */
  __vo uint32_t SHSR1;       /*!< Address offset: 0x40 */
  __vo uint32_t SHSR2;       /*!< Address offset: 0x44 */
  __vo uint32_t SHHR;        /*!< Address offset: 0x48 */
  __vo uint32_t SHRR;        /*!< Address offset: 0x4C */
} DAC_RegDef_t;

typedef struct
{
  __vo uint32_t KR;          /*!< Address offset: 0x00 */
  __vo uint32_t PR;          /*!< Address offset: 0x04 */
  __vo uint32_t RLR;         /*!< Address offset: 0x08 */
  __vo uint32_t SR;          /*!< Address offset: 0x0C */
  __vo uint32_t WINR;        /*!< Address offset: 0x10 */
} IWDG_RegDef_t;

typedef struct
{
    __vo uint32_t CR1;         /*!< Address offset: 0x00 */
    __vo uint32_t CR2;         /*!< Address offset: 0x04 */
    __vo uint32_t SMCR;        /*!< Address offset: 0x08 */
    __vo uint32_t DIER;        /*!< Address offset: 0x0C */
    __vo uint32_t SR;          /*!< Address offset: 0x10 */
    __vo uint32_t EGR;         /*!< Address offset: 0x14 */
    __vo uint32_t CCMR1;       /*!< Address offset: 0x18 */
    __vo uint32_t CCMR2;       /*!< Address offset: 0x1C */
    __vo uint32_t CCER;        /*!< Address offset: 0x20 */
    __vo uint32_t CNT;         /*!< Address offset: 0x24 */
    __vo uint32_t PSC;         /*!< Address offset: 0x28 */
    __vo uint32_t ARR;         /*!< Address offset: 0x2C */
    __vo uint32_t RCR;         /*!< Address offset: 0x30 */
    __vo uint32_t CCR1;        /*!< Address offset: 0x34 */
    __vo uint32_t CCR2;        /*!< Address offset: 0x38 */
    __vo uint32_t CCR3;        /*!< Address offset: 0x3C */
    __vo uint32_t CCR4;        /*!< Address offset: 0x40 */
    __vo uint32_t BDTR;        /*!< Address offset: 0x44 */
    __vo uint32_t DCR;         /*!< Address offset: 0x48 */
    __vo uint32_t DMAR;        /*!< Address offset: 0x4C */
    __vo uint32_t OR1;         /*!< Address offset: 0x50 */
    __vo uint32_t CCMR3;       /*!< Address offset: 0x54 */
    __vo uint32_t CCR5;        /*!< Address offset: 0x58 */
    __vo uint32_t CCR6;        /*!< Address offset: 0x5C */
    __vo uint32_t AF1;         /*!< Address offset: 0x60 */
    __vo uint32_t AF2;         /*!< Address offset: 0x64 */
    __vo uint32_t TISEL;       /*!< Address offset: 0x68 */
} TIM_RegDef_t;


/*
 * Peripheral defines
 */

#define RCC                 ((RCC_RegDef_t*)RCC_BASEADDR)
#define FLASH               ((FLASH_RegDef_t*) FLASH_R_BASEADDR)
#define SYSTICK             ((SysTick_RegDef_t*)SYSTICK_BASEADDR) 
#define IWDG                ((IWDG_RegDef_t *) IWDG_BASEADDR)

#define GPIOA               ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB               ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC               ((GPIO_RegDef_t*)GPIOC_BASEADDR)

#define UART1               ((UART_RegDef_t*)UART1_BASEADDR)
#define UART2               ((UART_RegDef_t*)UART2_BASEADDR)

#define ADC                 ((ADC_RegDef_t*)ADC_BASEADDR)

#define I2C1                ((I2C_RegDef_t*) I2C1_BASEADDR)
#define I2C2                ((I2C_RegDef_t*) I2C2_BASEADDR)

#define SPI1                ((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2                ((SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3                ((SPI_RegDef_t*) SPI3_BASEADDR)

#define DAC1                ((DAC_RegDef_t*) DAC1_BASEADDR)

#define TIM2                ((TIM_RegDef_t*) TIM2_BASEADDR)

/*
 * RCC ENABLE
 */

#define GPIOA_EN            (1 << 0)
#define GPIOB_EN            (1 << 1)
#define GPIOC_EN            (1 << 2)

/*
 *  Peripheral Enable Macros
 */

#define FLASH_PCLK_EN()     (RCC->AHBENR |= (1 << 8))

#define GPIOA_PCLK_EN()     (RCC->IOPENR |= (1 << 0))
#define GPIOB_PCLK_EN()     (RCC->IOPENR |= (1 << 1))
#define GPIOC_PCLK_EN()     (RCC->IOPENR |= (1 << 2))

#define UART1_PCLK_EN()     (RCC->APBENR2 |= (1 << 14))
#define UART2_PCLK_EN()     (RCC->APBENR1 |= (1 << 17))

#define ADC_PCLK_EN()       (RCC->APBENR2 |= (1 << 20))

#define I2C1_PCLK_EN()       (RCC->APBENR1 |= (1 << 21))
#define I2C2_PCLK_EN()       (RCC->APBENR1 |= (1 << 22))

#define SPI1_PCLK_EN()       (RCC->APBENR2 |= (1 << 12))
#define SPI2_PCLK_EN()       (RCC->APBENR1 |= (1 << 14))
#define SPI3_PCLK_EN()       (RCC->APBENR1 |= (1 << 15))

#define DAC1_PCLK_EN()       (RCC->APBENR1 |= (1 << 29))

/*
 *  Peripheral Disable Macros
 */

#define FLASH_PCLK_DI()     (RCC->AHBENR &= ~(1 << 8))

#define GPIOA_PCLK_DI()     (RCC->IOPENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()     (RCC->IOPENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()     (RCC->IOPENR &= ~(1 << 2))

#define UART1_PCLK_DI()     (RCC->APBENR2 &= ~(1 << 14))
#define UART2_PCLK_DI()     (RCC->APBENR1 &= ~(1 << 17))

#define ADC_PCLK_DI()       (RCC->APBENR2 &= ~(1 << 20))

#define I2C1_PCLK_DI()       (RCC->APBENR1 &= ~(1 << 21))
#define I2C2_PCLK_DI()       (RCC->APBENR1 &= ~(1 << 22))

#define SPI1_PCLK_DI()       (RCC->APBENR2 &= ~(1 << 12))
#define SPI2_PCLK_DI()       (RCC->APBENR1 &= ~(1 << 14))
#define SPI3_PCLK_DI()       (RCC->APBENR1 &= ~(1 << 15))

#define DAC1_PCLK_DI()       (RCC->APBENR1 &= ~(1 << 29))

/*
 * 	Macros to RESET 
 */

#define FLASH_REG_RESET()		  do{RCC->AHBRSTR |= (1 << 8); RCC->AHBRSTR &= ~(1 << 8);}while(0)

#define GPIOA_REG_RESET()		  do{RCC->IOPRSTR |= (1 << 0); RCC->IOPRSTR &= ~(1 << 0);}while(0)
#define GPIOB_REG_RESET()		  do{RCC->IOPRSTR |= (1 << 1); RCC->IOPRSTR &= ~(1 << 1);}while(0)
#define GPIOC_REG_RESET()		  do{RCC->IOPRSTR |= (1 << 2); RCC->IOPRSTR &= ~(1 << 2);}while(0)

#define UART1_REG_RESET()		  do{RCC->APBRSTR2 |= (1 << 14); RCC->APBRSTR2 &= ~(1 << 14);}while(0)
#define UART2_REG_RESET()		  do{RCC->APBRSTR1 |= (1 << 17); RCC->APBRSTR1 &= ~(1 << 17);}while(0)
#define ADC_REG_RESET()		    do{RCC->APBRSTR2 |= (1 << 20); RCC->APBRSTR2 &= ~(1 << 20);}while(0)

#define I2C1_REG_RESET()		  do{RCC->APBRSTR1 |= (1 << 21); RCC->APBRSTR1 &= ~(1 << 21);}while(0)
#define I2C2_REG_RESET()		  do{RCC->APBRSTR1 |= (1 << 22); RCC->APBRSTR1 &= ~(1 << 22);}while(0)
#define I2C3_REG_RESET()		  do{RCC->APBRSTR1 |= (1 << 23); RCC->APBRSTR1 &= ~(1 << 23);}while(0)

#define DAC1_REG_RESET()		  do{RCC->APBRSTR1 |= (1 << 29); RCC->APBRSTR1 &= ~(1 << 29);}while(0)



/*
 *     Drivers Includes
 */

#include "driver_systick.h"
#include "driver_gpio.h"
#include "driver_uart.h"

typedef uint32_t Pin_Type;

#endif
