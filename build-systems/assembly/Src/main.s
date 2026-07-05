.cpu cortex-m4
.syntax unified

.equ GPIOA_BASE,            0x40020000
.equ GPIO_MODER_OFFSET,     0x00
.equ GPIO_ODR_OFFSET,       0x14

.equ GPIOA_MODER,            GPIOA_BASE + GPIO_MODER_OFFSET
.equ GPIOA_ODR,              GPIOA_BASE + GPIO_ODR_OFFSET

.equ RCC_BASE,              0x40023800
.equ AHB1ENR_OFFSET,        0x30
.equ RCC_AHB1ENR,           RCC_BASE + AHB1ENR_OFFSET

.equ GPIO_EN,               1<<0
.equ MODER5_OUT,            1<<10
.equ LED_ON,                1<<5


            .section    .text
            .globl      main

main:
        BL      GPIO_Init

GPIO_Init:
        // Enable RCC GPIOA
        LDR     R0, =RCC_AHB1ENR
        LDR     R1, [R0]
        ORR     R1, #GPIO_EN
        STR     R1, [R0]

        // GPIO Mode output
        LDR     R0, =GPIOA_MODER
        LDR     R1, [R0]
        ORR     R1, #MODER5_OUT
        STR     R1, [R0]

        // led on
        LDR		R0,=GPIOA_ODR
		LDR		R1,=LED_ON
		STR		R1,[R0]

toggle:
    LDR r0, =GPIOA_ODR
    LDR r1, [r0]
    EOR r1, r1, #(1 << 5)
    STR r1, [r0]

    /* delay */
    LDR r2, =0x1E8480  /* 2.000.000 */

delay:
    SUBS r2, r2, #1
    BNE delay

    B toggle

    .end     