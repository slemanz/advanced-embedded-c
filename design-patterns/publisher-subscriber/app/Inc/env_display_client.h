#ifndef INC_ENV_DISPLAY_CLIENT_H_
#define INC_ENV_DISPLAY_CLIENT_H_

#include "env_sensor.h"
#include "enviromental_data.h"

typedef struct display_client
{
    env_data_t data;
    callback_fn fn_handler;
}display_client_t;

display_client_t *display_client_create(void);
void display_client_init(display_client_t *const me);

void display_client_handleNewData(void *me, env_data_t data);
void display_client_subscribe(display_client_t *const me, env_sensor_t *const server);
void display_client_unsubscribe(display_client_t *const me, env_sensor_t *const server);

void display_client_destroy(display_client_t *const me);


#endif /* INC_ENV_DISPLAY_CLIENT_H_ */