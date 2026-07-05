#include "comm_interface.h"

CommProtocol_t *CommProtocol_create(CommProtocolType_e type)
{
    switch(type)
    {
        case PROTOCOL_UART: return (CommProtocol_t*)&UART_Protocol;
        case PROTOCOL_SPI: return (CommProtocol_t*)&SPI_Protocol;
        case PROTOCOL_I2C: return (CommProtocol_t*)&I2C_Protocol;
        default: return NULL;
    }
}