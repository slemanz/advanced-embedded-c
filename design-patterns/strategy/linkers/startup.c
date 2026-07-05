#include <stdint.h>

/*
 *      STM32G0B1xx
 */

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (128 * 1024) 
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))

#define STACK_START     (SRAM_END)

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;


/* Prototype of main*/
int main(void);

void __libc_init_array(void);



/* Functions prototypes of STM32F401 system exceptions and IRQ handlers */
void Reset_Handler(void);


void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler"))); 
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));


void WWDG_IRQHandler                                    (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler                                     (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_TAMP_IRQHandler                                (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler                                   (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler                                (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_UCPD1_2_IRQHandler                             (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler                           (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler                         (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_COMP_IRQHandler                               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler                                    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_TIM4_IRQHandler                               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler                         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_LPTIM2_IRQHandler                             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM14_IRQHandler                                   (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM15_IRQHandler                                   (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM16_FDCAN_IT0_IRQHandler                         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM17_FDCAN_IT1_IRQHandler                         (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler                                    (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_3_IRQHandler                                  (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler                                    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_3_IRQHandler                                  (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler                                  (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_4_5_6_IRQHandler                            (void) __attribute__ ((weak, alias("Default_Handler")));
void CEC_IRQHandler                                     (void) __attribute__ ((weak, alias("Default_Handler")));
void AES_RNG_IRQHandler                                 (void) __attribute__ ((weak, alias("Default_Handler")));




uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                                //  position
    (uint32_t)Reset_Handler,                    // -15
    (uint32_t)NMI_Handler,                      // -14
    (uint32_t)HardFault_Handler,                // -13
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,                      // -5
    0,
    0,
    (uint32_t)PendSV_Handler,                   // -2
    (uint32_t)SysTick_Handler,                  // -1


    // chip st
    (uint32_t)WWDG_IRQHandler,                  // 0 
    (uint32_t)PVD_IRQHandler,                   // 1
    (uint32_t)RTC_TAMP_IRQHandler,              // 2
    (uint32_t)FLASH_IRQHandler,                 // 3
    (uint32_t)RCC_CRS_IRQHandler,               // 4
    (uint32_t)EXTI0_1_IRQHandler,               // 5
    (uint32_t)EXTI2_3_IRQHandler,               // 6
    (uint32_t)EXTI4_15_IRQHandler,              // 7
    (uint32_t)USB_UCPD1_2_IRQHandler,           // 8
    (uint32_t)DMA1_Channel1_IRQHandler,         // 9
    (uint32_t)DMA1_Channel2_3_IRQHandler,       // 10
    (uint32_t)DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler, // 11
    (uint32_t)ADC1_COMP_IRQHandler,             // 12
    (uint32_t)TIM1_BRK_UP_TRG_COM_IRQHandler,   // 13
    (uint32_t)TIM1_CC_IRQHandler,               // 14
    (uint32_t)TIM2_IRQHandler,                  // 15
    (uint32_t)TIM3_TIM4_IRQHandler,             // 16
    (uint32_t)TIM6_DAC_LPTIM1_IRQHandler,       // 17
    (uint32_t)TIM7_LPTIM2_IRQHandler,           // 18
    (uint32_t)TIM14_IRQHandler,                 // 19
    (uint32_t)TIM15_IRQHandler,                 // 20
    (uint32_t)TIM16_FDCAN_IT0_IRQHandler,       // 21
    (uint32_t)TIM17_FDCAN_IT1_IRQHandler,       // 22
    (uint32_t)I2C1_IRQHandler,                  // 23
    (uint32_t)I2C2_3_IRQHandler,                // 24
    (uint32_t)SPI1_IRQHandler,                  // 25
    (uint32_t)SPI2_3_IRQHandler,                // 26
    (uint32_t)USART1_IRQHandler,                // 27
    (uint32_t)USART2_IRQHandler,               // 28
    (uint32_t)USART3_4_5_6_IRQHandler,          // 29
    (uint32_t)CEC_IRQHandler,                   // 30
    (uint32_t)AES_RNG_IRQHandler                // 31
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    // copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

    uint8_t *pDst = (uint8_t*)&_sdata; //sram
    uint8_t *pSrc = (uint8_t*)&_la_data; //flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    // Init the .bss section to zero in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }

    __libc_init_array();

    // call main()
    main();
}