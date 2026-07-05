#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "simple-timer.h"

#include "driver_uart.h"

typedef enum
{
	SYS_APP = 1,
	SYS_FACTORY_APP,
}SYS_APPS;

volatile char g_ch_key = 0;
volatile uint8_t g_un_key = 0;

static void proces_btldr_cmds(SYS_APPS curr_app);

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\r\nInit bootloader...\r\n");

    simple_timer_t timer_blink;
    simple_timer_t timer_jump;
    
    simple_timer_setup(&timer_blink, 100, true);
    simple_timer_setup(&timer_jump, 4700, false);

    while (1)
    {   
        if(simple_timer_has_elapsed(&timer_blink))
        {
            led_toggle();
        }

        if(simple_timer_has_elapsed(&timer_jump))
        {
            INTERRUPT_DISABLE();
            jmp_to_app(DEFAULT_APP_ADDRESS);
            simple_timer_setup(&timer_blink, 500, true);
        }

        if(!button_get_state())
        {

            /*Button pressed*/
            printf("DBG: Button Pressed\r\n");

            /*Button pressed*/
            printf("==========================================\r\n");
            printf("==========================================\r\n");
            printf("==========================================\r\n");
            printf("==========================================\r\n");
            printf("==========================================\r\n");

            printf("\r\n");
            printf("Bootloader Menu\r\n");
            printf("\r\n");
            printf("==========================================\r\n");
            printf("==========================================\r\n");
            printf("==========================================\r\n");

            printf("Available Commands:\r\n");
            printf("1       ==> Run App\r\n");
            printf("F       ==> Factory App 2\r\n");

		    while(1)
		    {
			    proces_btldr_cmds((SYS_APPS)g_un_key);
		    }
        }
    }
}

static void proces_btldr_cmds(SYS_APPS curr_app)
{
    switch(curr_app)
    {
        case SYS_APP:
        {
            printf("APP1 Selected....\n\r");
            jmp_to_app(DEFAULT_APP_ADDRESS);
            while(1);
        }
        case SYS_FACTORY_APP:
        {
            printf("Factory APP Selected....\n\r");
            jmp_to_app(FACTORY_APP_ADDRESS);
            while(1);
        }

        default:
            break;
    }

}

static void uart_callback(void)
{
    g_ch_key = UART2->DR;

    if(g_ch_key == '1')
    {
        g_un_key = 1;
    }else if((g_ch_key ==  'f')  || (g_ch_key ==  'F'))
    {
        g_un_key = 2;
    }else
    {
        
    }
}

void USART2_IRQHandler(void)
{
    if(UART2->SR & UART_SR_RXNE)
    {
        uart_callback();
    }
}