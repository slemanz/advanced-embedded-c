#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"

// Manual Bit-Packing with Bitwise Operators

#define MODE_MASK   0x03    // 0b 0000 0011 : 2 bits for mode
#define FLAG_MASK   0x04    // 0b 0000 0100 : 1 bit for flag
#define SPEED_MASK  0x38    // 0b 0011 1000 : 3 bits for speed

unsigned char pack_data(unsigned char mode, unsigned char flag, unsigned char speed)
{
    return ((mode & 0x03) | ((flag & 0x01) << 2) | ((speed & 0x07) << 3));
}

void unpack_data(unsigned char data)
{
    unsigned char mode  = (data & MODE_MASK);
    unsigned char flag  = (data & FLAG_MASK) >> 2;
    unsigned char speed = (data & SPEED_MASK) >> 3;

    printf("Mode: %u, Flag: %u, Speed: %u\n\r", mode, flag, speed);
}

int main(void)
 {
    config_drivers();
    config_bsp();
    printf("\n");

    unsigned char packed = pack_data(2, 1, 5);
	unpack_data(packed);

    while (1)
    {   
    }
}