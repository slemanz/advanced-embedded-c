#ifndef INC_GPIO_PROXY_H_
#define INC_GPIO_PROXY_H_

#include <stdint.h>

// Proxy interface for GPIO
typedef struct{
    void    (*pin_set)(uint32_t pin);
    void    (*pin_clear)(uint32_t pin);
    uint8_t (*pin_read)(uint32_t pin);
}GPIO_Proxy_t;


// Secure GPIO Proxy Structure
typedef struct{
    GPIO_Proxy_t *real_gpio;
    uint32_t pins_allowed; /* Premitted pins */
}SecureGPIO_Proxy_t;

void secure_gpio_out_init(uint32_t pin);
void secure_gpio_in_init(uint32_t pin);

void secure_gpio_set_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin);
int8_t secure_gpio_read_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin);
void secure_gpio_clear_pin(SecureGPIO_Proxy_t *proxy, uint32_t pin);

void update_allowed_pins(SecureGPIO_Proxy_t *proxy, uint32_t new_allowed_pins);


extern SecureGPIO_Proxy_t secure_gpio;

#endif /* INC_GPIO_PROXY_H_ */