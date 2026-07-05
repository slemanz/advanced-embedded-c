#include "comm_interface.h"
#include "driver_i2c.h"

static void I2C_Init(void)
{
    i2c1_init();
}

static void i2c_send(uint8_t *data, uint32_t len)
{
    i2c1_burst_write(0x50, 0x00, (char*)data, len);
}

const CommProtocol_t I2C_Protocol = {
    .init = I2C_Init,
    .send = i2c_send,
    .receive = NULL,
    .deinit = NULL
};