#ifndef INC_DRIVER_RTC_H_
#define INC_DRIVER_RTC_H_
#include <stdint.h>
#include "stm32f411xx.h"


#define CR_ALRAIE					(1U<<12)
#define ISR_ALRAF					(1U<<8)
#define ISR_INIT					(1U<<7)

#define CR_TSIE						(1U<<15)
#define CR_TSE						(1U<<11)
#define ISR_TSF						(1U<<11)

#define RTC_TAFCR_TAMPIE            (1U << 2U)
#define RTC_TAFCR_TAMP1TRG          (1U << 1U)
#define RTC_TAFCR_TAMP1E            (1U << 0U)

#define RTC_ISR_TAMP1F              (1U << 13U)

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YT_Pos                 (20U)                                    
#define RTC_DR_YT_Msk                 (0xFUL << RTC_DR_YT_Pos)                  /*!< 0x00F00000 */
#define RTC_DR_YT                     RTC_DR_YT_Msk                            
#define RTC_DR_YT_0                   (0x1UL << RTC_DR_YT_Pos)                  /*!< 0x00100000 */
#define RTC_DR_YT_1                   (0x2UL << RTC_DR_YT_Pos)                  /*!< 0x00200000 */
#define RTC_DR_YT_2                   (0x4UL << RTC_DR_YT_Pos)                  /*!< 0x00400000 */
#define RTC_DR_YT_3                   (0x8UL << RTC_DR_YT_Pos)                  /*!< 0x00800000 */
#define RTC_DR_YU_Pos                 (16U)                                    
#define RTC_DR_YU_Msk                 (0xFUL << RTC_DR_YU_Pos)                  /*!< 0x000F0000 */
#define RTC_DR_YU                     RTC_DR_YU_Msk                            
#define RTC_DR_YU_0                   (0x1UL << RTC_DR_YU_Pos)                  /*!< 0x00010000 */
#define RTC_DR_YU_1                   (0x2UL << RTC_DR_YU_Pos)                  /*!< 0x00020000 */
#define RTC_DR_YU_2                   (0x4UL << RTC_DR_YU_Pos)                  /*!< 0x00040000 */
#define RTC_DR_YU_3                   (0x8UL << RTC_DR_YU_Pos)                  /*!< 0x00080000 */
#define RTC_DR_WDU_Pos                (13U)                                    
#define RTC_DR_WDU_Msk                (0x7UL << RTC_DR_WDU_Pos)                 /*!< 0x0000E000 */
#define RTC_DR_WDU                    RTC_DR_WDU_Msk                           
#define RTC_DR_WDU_0                  (0x1UL << RTC_DR_WDU_Pos)                 /*!< 0x00002000 */
#define RTC_DR_WDU_1                  (0x2UL << RTC_DR_WDU_Pos)                 /*!< 0x00004000 */
#define RTC_DR_WDU_2                  (0x4UL << RTC_DR_WDU_Pos)                 /*!< 0x00008000 */
#define RTC_DR_MT_Pos                 (12U)                                    
#define RTC_DR_MT_Msk                 (0x1UL << RTC_DR_MT_Pos)                  /*!< 0x00001000 */
#define RTC_DR_MT                     RTC_DR_MT_Msk                            
#define RTC_DR_MU_Pos                 (8U)                                     
#define RTC_DR_MU_Msk                 (0xFUL << RTC_DR_MU_Pos)                  /*!< 0x00000F00 */
#define RTC_DR_MU                     RTC_DR_MU_Msk                            
#define RTC_DR_MU_0                   (0x1UL << RTC_DR_MU_Pos)                  /*!< 0x00000100 */
#define RTC_DR_MU_1                   (0x2UL << RTC_DR_MU_Pos)                  /*!< 0x00000200 */
#define RTC_DR_MU_2                   (0x4UL << RTC_DR_MU_Pos)                  /*!< 0x00000400 */
#define RTC_DR_MU_3                   (0x8UL << RTC_DR_MU_Pos)                  /*!< 0x00000800 */
#define RTC_DR_DT_Pos                 (4U)                                     
#define RTC_DR_DT_Msk                 (0x3UL << RTC_DR_DT_Pos)                  /*!< 0x00000030 */
#define RTC_DR_DT                     RTC_DR_DT_Msk                            
#define RTC_DR_DT_0                   (0x1UL << RTC_DR_DT_Pos)                  /*!< 0x00000010 */
#define RTC_DR_DT_1                   (0x2UL << RTC_DR_DT_Pos)                  /*!< 0x00000020 */
#define RTC_DR_DU_Pos                 (0U)                                     
#define RTC_DR_DU_Msk                 (0xFUL << RTC_DR_DU_Pos)                  /*!< 0x0000000F */
#define RTC_DR_DU                     RTC_DR_DU_Msk                            
#define RTC_DR_DU_0                   (0x1UL << RTC_DR_DU_Pos)                  /*!< 0x00000001 */
#define RTC_DR_DU_1                   (0x2UL << RTC_DR_DU_Pos)                  /*!< 0x00000002 */
#define RTC_DR_DU_2                   (0x4UL << RTC_DR_DU_Pos)                  /*!< 0x00000004 */
#define RTC_DR_DU_3                   (0x8UL << RTC_DR_DU_Pos)                  /*!< 0x00000008 */

/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_PM_Pos                 (22U)                                    
#define RTC_TR_PM_Msk                 (0x1UL << RTC_TR_PM_Pos)                  /*!< 0x00400000 */
#define RTC_TR_PM                     RTC_TR_PM_Msk                            
#define RTC_TR_HT_Pos                 (20U)                                    
#define RTC_TR_HT_Msk                 (0x3UL << RTC_TR_HT_Pos)                  /*!< 0x00300000 */
#define RTC_TR_HT                     RTC_TR_HT_Msk                            
#define RTC_TR_HT_0                   (0x1UL << RTC_TR_HT_Pos)                  /*!< 0x00100000 */
#define RTC_TR_HT_1                   (0x2UL << RTC_TR_HT_Pos)                  /*!< 0x00200000 */
#define RTC_TR_HU_Pos                 (16U)                                    
#define RTC_TR_HU_Msk                 (0xFUL << RTC_TR_HU_Pos)                  /*!< 0x000F0000 */
#define RTC_TR_HU                     RTC_TR_HU_Msk                            
#define RTC_TR_HU_0                   (0x1UL << RTC_TR_HU_Pos)                  /*!< 0x00010000 */
#define RTC_TR_HU_1                   (0x2UL << RTC_TR_HU_Pos)                  /*!< 0x00020000 */
#define RTC_TR_HU_2                   (0x4UL << RTC_TR_HU_Pos)                  /*!< 0x00040000 */
#define RTC_TR_HU_3                   (0x8UL << RTC_TR_HU_Pos)                  /*!< 0x00080000 */
#define RTC_TR_MNT_Pos                (12U)                                    
#define RTC_TR_MNT_Msk                (0x7UL << RTC_TR_MNT_Pos)                 /*!< 0x00007000 */
#define RTC_TR_MNT                    RTC_TR_MNT_Msk                           
#define RTC_TR_MNT_0                  (0x1UL << RTC_TR_MNT_Pos)                 /*!< 0x00001000 */
#define RTC_TR_MNT_1                  (0x2UL << RTC_TR_MNT_Pos)                 /*!< 0x00002000 */
#define RTC_TR_MNT_2                  (0x4UL << RTC_TR_MNT_Pos)                 /*!< 0x00004000 */
#define RTC_TR_MNU_Pos                (8U)                                     
#define RTC_TR_MNU_Msk                (0xFUL << RTC_TR_MNU_Pos)                 /*!< 0x00000F00 */
#define RTC_TR_MNU                    RTC_TR_MNU_Msk                           
#define RTC_TR_MNU_0                  (0x1UL << RTC_TR_MNU_Pos)                 /*!< 0x00000100 */
#define RTC_TR_MNU_1                  (0x2UL << RTC_TR_MNU_Pos)                 /*!< 0x00000200 */
#define RTC_TR_MNU_2                  (0x4UL << RTC_TR_MNU_Pos)                 /*!< 0x00000400 */
#define RTC_TR_MNU_3                  (0x8UL << RTC_TR_MNU_Pos)                 /*!< 0x00000800 */
#define RTC_TR_ST_Pos                 (4U)                                     
#define RTC_TR_ST_Msk                 (0x7UL << RTC_TR_ST_Pos)                  /*!< 0x00000070 */
#define RTC_TR_ST                     RTC_TR_ST_Msk                            
#define RTC_TR_ST_0                   (0x1UL << RTC_TR_ST_Pos)                  /*!< 0x00000010 */
#define RTC_TR_ST_1                   (0x2UL << RTC_TR_ST_Pos)                  /*!< 0x00000020 */
#define RTC_TR_ST_2                   (0x4UL << RTC_TR_ST_Pos)                  /*!< 0x00000040 */
#define RTC_TR_SU_Pos                 (0U)                                     
#define RTC_TR_SU_Msk                 (0xFUL << RTC_TR_SU_Pos)                  /*!< 0x0000000F */
#define RTC_TR_SU                     RTC_TR_SU_Msk                            
#define RTC_TR_SU_0                   (0x1UL << RTC_TR_SU_Pos)                  /*!< 0x00000001 */
#define RTC_TR_SU_1                   (0x2UL << RTC_TR_SU_Pos)                  /*!< 0x00000002 */
#define RTC_TR_SU_2                   (0x4UL << RTC_TR_SU_Pos)                  /*!< 0x00000004 */
#define RTC_TR_SU_3                   (0x8UL << RTC_TR_SU_Pos)                  /*!< 0x00000008 */

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A_Pos         (16U)                                    
#define RTC_PRER_PREDIV_A_Msk         (0x7FUL << RTC_PRER_PREDIV_A_Pos)         /*!< 0x007F0000 */
#define RTC_PRER_PREDIV_A             RTC_PRER_PREDIV_A_Msk                    
#define RTC_PRER_PREDIV_S_Pos         (0U)                                     
#define RTC_PRER_PREDIV_S_Msk         (0x7FFFUL << RTC_PRER_PREDIV_S_Pos)       /*!< 0x00007FFF */
#define RTC_PRER_PREDIV_S             RTC_PRER_PREDIV_S_Msk                    

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4_Pos           (31U)                                    
#define RTC_ALRMAR_MSK4_Msk           (0x1UL << RTC_ALRMAR_MSK4_Pos)            /*!< 0x80000000 */
#define RTC_ALRMAR_MSK4               RTC_ALRMAR_MSK4_Msk                      
#define RTC_ALRMAR_WDSEL_Pos          (30U)                                    
#define RTC_ALRMAR_WDSEL_Msk          (0x1UL << RTC_ALRMAR_WDSEL_Pos)           /*!< 0x40000000 */
#define RTC_ALRMAR_WDSEL              RTC_ALRMAR_WDSEL_Msk                     
#define RTC_ALRMAR_DT_Pos             (28U)                                    
#define RTC_ALRMAR_DT_Msk             (0x3UL << RTC_ALRMAR_DT_Pos)              /*!< 0x30000000 */
#define RTC_ALRMAR_DT                 RTC_ALRMAR_DT_Msk                        
#define RTC_ALRMAR_DT_0               (0x1UL << RTC_ALRMAR_DT_Pos)              /*!< 0x10000000 */
#define RTC_ALRMAR_DT_1               (0x2UL << RTC_ALRMAR_DT_Pos)              /*!< 0x20000000 */
#define RTC_ALRMAR_DU_Pos             (24U)                                    
#define RTC_ALRMAR_DU_Msk             (0xFUL << RTC_ALRMAR_DU_Pos)              /*!< 0x0F000000 */
#define RTC_ALRMAR_DU                 RTC_ALRMAR_DU_Msk                        
#define RTC_ALRMAR_DU_0               (0x1UL << RTC_ALRMAR_DU_Pos)              /*!< 0x01000000 */
#define RTC_ALRMAR_DU_1               (0x2UL << RTC_ALRMAR_DU_Pos)              /*!< 0x02000000 */
#define RTC_ALRMAR_DU_2               (0x4UL << RTC_ALRMAR_DU_Pos)              /*!< 0x04000000 */
#define RTC_ALRMAR_DU_3               (0x8UL << RTC_ALRMAR_DU_Pos)              /*!< 0x08000000 */
#define RTC_ALRMAR_MSK3_Pos           (23U)                                    
#define RTC_ALRMAR_MSK3_Msk           (0x1UL << RTC_ALRMAR_MSK3_Pos)            /*!< 0x00800000 */
#define RTC_ALRMAR_MSK3               RTC_ALRMAR_MSK3_Msk                      
#define RTC_ALRMAR_PM_Pos             (22U)                                    
#define RTC_ALRMAR_PM_Msk             (0x1UL << RTC_ALRMAR_PM_Pos)              /*!< 0x00400000 */
#define RTC_ALRMAR_PM                 RTC_ALRMAR_PM_Msk                        
#define RTC_ALRMAR_HT_Pos             (20U)                                    
#define RTC_ALRMAR_HT_Msk             (0x3UL << RTC_ALRMAR_HT_Pos)              /*!< 0x00300000 */
#define RTC_ALRMAR_HT                 RTC_ALRMAR_HT_Msk                        
#define RTC_ALRMAR_HT_0               (0x1UL << RTC_ALRMAR_HT_Pos)              /*!< 0x00100000 */
#define RTC_ALRMAR_HT_1               (0x2UL << RTC_ALRMAR_HT_Pos)              /*!< 0x00200000 */
#define RTC_ALRMAR_HU_Pos             (16U)                                    
#define RTC_ALRMAR_HU_Msk             (0xFUL << RTC_ALRMAR_HU_Pos)              /*!< 0x000F0000 */
#define RTC_ALRMAR_HU                 RTC_ALRMAR_HU_Msk                        
#define RTC_ALRMAR_HU_0               (0x1UL << RTC_ALRMAR_HU_Pos)              /*!< 0x00010000 */
#define RTC_ALRMAR_HU_1               (0x2UL << RTC_ALRMAR_HU_Pos)              /*!< 0x00020000 */
#define RTC_ALRMAR_HU_2               (0x4UL << RTC_ALRMAR_HU_Pos)              /*!< 0x00040000 */
#define RTC_ALRMAR_HU_3               (0x8UL << RTC_ALRMAR_HU_Pos)              /*!< 0x00080000 */
#define RTC_ALRMAR_MSK2_Pos           (15U)                                    
#define RTC_ALRMAR_MSK2_Msk           (0x1UL << RTC_ALRMAR_MSK2_Pos)            /*!< 0x00008000 */
#define RTC_ALRMAR_MSK2               RTC_ALRMAR_MSK2_Msk                      
#define RTC_ALRMAR_MNT_Pos            (12U)                                    
#define RTC_ALRMAR_MNT_Msk            (0x7UL << RTC_ALRMAR_MNT_Pos)             /*!< 0x00007000 */
#define RTC_ALRMAR_MNT                RTC_ALRMAR_MNT_Msk                       
#define RTC_ALRMAR_MNT_0              (0x1UL << RTC_ALRMAR_MNT_Pos)             /*!< 0x00001000 */
#define RTC_ALRMAR_MNT_1              (0x2UL << RTC_ALRMAR_MNT_Pos)             /*!< 0x00002000 */
#define RTC_ALRMAR_MNT_2              (0x4UL << RTC_ALRMAR_MNT_Pos)             /*!< 0x00004000 */
#define RTC_ALRMAR_MNU_Pos            (8U)                                     
#define RTC_ALRMAR_MNU_Msk            (0xFUL << RTC_ALRMAR_MNU_Pos)             /*!< 0x00000F00 */
#define RTC_ALRMAR_MNU                RTC_ALRMAR_MNU_Msk                       
#define RTC_ALRMAR_MNU_0              (0x1UL << RTC_ALRMAR_MNU_Pos)             /*!< 0x00000100 */
#define RTC_ALRMAR_MNU_1              (0x2UL << RTC_ALRMAR_MNU_Pos)             /*!< 0x00000200 */
#define RTC_ALRMAR_MNU_2              (0x4UL << RTC_ALRMAR_MNU_Pos)             /*!< 0x00000400 */
#define RTC_ALRMAR_MNU_3              (0x8UL << RTC_ALRMAR_MNU_Pos)             /*!< 0x00000800 */
#define RTC_ALRMAR_MSK1_Pos           (7U)                                     
#define RTC_ALRMAR_MSK1_Msk           (0x1UL << RTC_ALRMAR_MSK1_Pos)            /*!< 0x00000080 */
#define RTC_ALRMAR_MSK1               RTC_ALRMAR_MSK1_Msk                      
#define RTC_ALRMAR_ST_Pos             (4U)                                     
#define RTC_ALRMAR_ST_Msk             (0x7UL << RTC_ALRMAR_ST_Pos)              /*!< 0x00000070 */
#define RTC_ALRMAR_ST                 RTC_ALRMAR_ST_Msk                        
#define RTC_ALRMAR_ST_0               (0x1UL << RTC_ALRMAR_ST_Pos)              /*!< 0x00000010 */
#define RTC_ALRMAR_ST_1               (0x2UL << RTC_ALRMAR_ST_Pos)              /*!< 0x00000020 */
#define RTC_ALRMAR_ST_2               (0x4UL << RTC_ALRMAR_ST_Pos)              /*!< 0x00000040 */
#define RTC_ALRMAR_SU_Pos             (0U)                                     
#define RTC_ALRMAR_SU_Msk             (0xFUL << RTC_ALRMAR_SU_Pos)              /*!< 0x0000000F */
#define RTC_ALRMAR_SU                 RTC_ALRMAR_SU_Msk                        
#define RTC_ALRMAR_SU_0               (0x1UL << RTC_ALRMAR_SU_Pos)              /*!< 0x00000001 */
#define RTC_ALRMAR_SU_1               (0x2UL << RTC_ALRMAR_SU_Pos)              /*!< 0x00000002 */
#define RTC_ALRMAR_SU_2               (0x4UL << RTC_ALRMAR_SU_Pos)              /*!< 0x00000004 */
#define RTC_ALRMAR_SU_3               (0x8UL << RTC_ALRMAR_SU_Pos)


#define EXTI_IMR_MR21               (1U << 21U)
#define EXTI_IMR_IM21               EXTI_IMR_MR21

void rtc_init(void);
void rtc_alarm_init(void);
void rtc_timestamp_init(void);

uint8_t rtc_convert_bcd2bin(uint8_t value);
uint32_t rtc_date_get_day(void);
uint32_t rtc_date_get_year(void);
uint32_t rtc_date_get_month(void);
uint32_t rtc_time_get_second(void);
uint32_t rtc_time_get_minute(void);
uint32_t rtc_time_get_hour(void);
void rtc_timestamp_init(void);
void rtc_tamper_detect_init(void);

#endif