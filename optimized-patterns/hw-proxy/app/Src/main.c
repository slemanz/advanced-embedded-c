#include <stdio.h>
#include "config.h"
#include "driver_systick.h"
#include "gpio_proxy.h"

int main(void)
 {
    config_drivers();
    config_bsp();

    printf("\nInit board...\n\r");

	secure_gpio_out_init(5);
    secure_gpio_out_init(8);

    ticks_delay(5000);

    secure_gpio_set_pin(&secure_gpio, 5);
    secure_gpio_set_pin(&secure_gpio, 8);
    ticks_delay(3000);

    update_allowed_pins(&secure_gpio, (1U << 8) | (1U << 5));
    secure_gpio_set_pin(&secure_gpio, 8);
    secure_gpio_clear_pin(&secure_gpio, 5);

    while (1) __asm("NOP");
}