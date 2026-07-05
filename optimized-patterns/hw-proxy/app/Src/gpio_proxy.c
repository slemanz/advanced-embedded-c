#include <stdio.h>
#include "gpio_proxy.h"
#include "stm32f411xx.h"

/*
 * initialize a specific GPIO pin
 */

void secure_gpio_out_init(uint32_t pin)
{
    RCC->AHB1ENR |= (1U << 0); // Enable clock for GPIO 

    // Set output mode
    GPIOA->MODER &= ~(3U << (pin*2));
    GPIOA->MODER |=  (1U << (pin*2));

    GPIOA->BSRR = (1U << (pin + 16)); // ensure pin starts low (Defaul OFF)
}

void secure_gpio_in_init(uint32_t pin)
{
    RCC->AHB1ENR |= (1U << 0); // Enable clock for GPIO 
    GPIOA->MODER &= ~(3U << (pin*2));  // Set input mode
    GPIOA->BSRR = (1U << (pin + 16)); // ensure pin starts low (Defaul OFF)
}


/*
 * Real GPIO Driver Functions
 */

void real_gpio_set_pin(uint32_t pin)
{
    GPIOA->BSRR = (1U << pin);
    printf("Pin %lu is set\n", pin);
}

void real_gpio_clear_pin(uint32_t pin)
{
    GPIOA->BSRR = (1U << (pin + 16));
    printf("Pin %lu is cleared\n", pin);
}

uint8_t real_gpio_read_pin(uint32_t pin)
{
    return (GPIOA->IDR & (1U << pin)) ? 1 : 0; // read gpio state
}


/*
 * Real GPIO Instance
 */

GPIO_Proxy_t real_gpio = {
    .pin_set = real_gpio_set_pin,
    .pin_clear = real_gpio_clear_pin,
    .pin_read = real_gpio_read_pin
};

/*
 * Secure Proxy layer
 */

SecureGPIO_Proxy_t secure_gpio = {
    .real_gpio = &real_gpio,
    .pins_allowed = (1U << 5)
};

/*
 * Secure functions
 */

void secure_gpio_set_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin)
{
    if(proxy->pins_allowed & (1 << pin))
    {
        proxy->real_gpio->pin_set(pin);
    }else
    {
        printf("Access denied: Pin not allowed\n");
    }
}

int8_t secure_gpio_read_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin)
{
    if(proxy->pins_allowed & (1U << pin))
    {
        return proxy->real_gpio->pin_read(pin);
    }else
    {
        printf("Access denied: Pin not allowed\n");
    }
    return -1;
}

void secure_gpio_clear_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin)
{
    if(proxy->pins_allowed & (1 << pin))
    {
        proxy->real_gpio->pin_clear(pin);
    }else
    {
        printf("Access denied: Pin not allowed\n");
    }
}

/*
 * Function to update allowed pins at runtime
 */

void update_allowed_pins(SecureGPIO_Proxy_t *proxy, uint32_t new_allowed_pins)
{
	proxy->pins_allowed = new_allowed_pins;
}