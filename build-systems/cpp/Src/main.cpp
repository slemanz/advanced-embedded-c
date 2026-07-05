#include "mcal_reg.h"

#define RCC_AHB1ENR  (*((volatile unsigned int *) 0x40023830)) 

class Led
{
    public:
        typedef std::uint32_t port_type;
        typedef std::uint32_t bval_type;
    
    Led(const port_type p, bval_type b):port(p),bval(b)
    {
        /* disable pin */
        *reinterpret_cast<volatile port_type *>(port) &= ~(1U<< bval);

        /* set pin mode as output */
        const port_type gpio_mode_reg =  port  - 0x14;
        *reinterpret_cast<volatile port_type *>(gpio_mode_reg) |= ( 1U<<(bval *2));
    }

    void toggle()const
    {
        *reinterpret_cast<volatile port_type*>(port) ^= (1U << bval);
    }

    void pseudo_delayMs()
    {
        for(int i = 0; i < 100000; i++){}
    }

    private:
		const port_type port;
		const bval_type bval; 
};

int main(void)
{
    RCC_AHB1ENR |= (1U << 0); /* Enable clock to GPIOA */
    Led led5(mcal::reg::gpioa, mcal::reg::gpio_pin5);
    
    while (1)
    {
        led5.toggle();
        led5.pseudo_delayMs();
    }
}