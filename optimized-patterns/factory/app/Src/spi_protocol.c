#include "comm_interface.h"
#include "driver_spi.h"

static SPI_Handle_t hspi;

static void SPI_Init(void)
{
    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    spi_init(&hspi);
}

static void spi_send(uint8_t *data, uint32_t len)
{
    spi_transmit(&hspi, data, len, 1000);
}

const CommProtocol_t SPI_Protocol =  {
    .init = SPI_Init,
    .send = spi_send,
    .receive = NULL,
    .deinit = NULL
};