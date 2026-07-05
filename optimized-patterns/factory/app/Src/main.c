#include "config.h"
#include "driver_systick.h"

#include "comm_interface.h"



#define PROTO_ID                0

static CommProtocolType_e detect_protocol(int protocol_id)
{
    switch (protocol_id)
    {
    case 0: return PROTOCOL_UART;
    case 1: return PROTOCOL_I2C;
    case 2: return PROTOCOL_SPI;
    default: return PROTOCOL_UART;
    }
}

int main(void)
 {
    config_drivers();

    CommProtocolType_e protocol_type = detect_protocol(PROTO_ID);
    CommProtocol_t *protocol = CommProtocol_create(protocol_type);

    if(!protocol)
    {
        while(1); //error
    }

    protocol->init();
    const char *msg = "Hello from comm protocol!\n";

    uint64_t start_time = ticks_get();
    while (1)
    {   
        if((ticks_get() - start_time) >= 5000)
        {
            protocol->send((uint8_t*)msg, 26);
            start_time = ticks_get();
        }
    }
}