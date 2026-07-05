#include "driver_uart.h"

static void __attribute__((constructor)) serial_init(void)
{
    uart2_init();
}


extern int __io_putchar(int ch)
{
    uart2_write_byte((uint8_t)ch);
    return ch;

}