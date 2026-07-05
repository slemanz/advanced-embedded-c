#ifndef INC_COMM_INTERFACE_H_
#define INC_COMM_INTERFACE_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    PROTOCOL_UART,
    PROTOCOL_I2C,
    PROTOCOL_SPI
}CommProtocolType_e;

typedef struct
{
    void (*init)(void);
    void (*send)(uint8_t *data, uint32_t len);
    void (*receive)(uint8_t *buffer, uint32_t len);
    void (*deinit)(void);
}CommProtocol_t;

/* Factory Method */
CommProtocol_t *CommProtocol_create(CommProtocolType_e type);

extern const CommProtocol_t UART_Protocol;
extern const CommProtocol_t I2C_Protocol;
extern const CommProtocol_t SPI_Protocol;


#endif /* INC_COMM_INTERFACE_H_ */