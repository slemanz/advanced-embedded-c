#ifndef INC_ENV_SENSOR_H_
#define INC_ENV_SENSOR_H_

#include "enviromental_data.h"

#define MAX_CLIENT          10

// calback function for notification
typedef void (*callback_fn)(void *pObject, env_data_t data);

typedef struct notify_handler{
    void *pObject;          /* Pointer to client object */
    callback_fn fn_handler; /* Callback fn */
}notify_handler_t;

typedef struct env_sensor{
    env_data_t data;
    uint32_t n_client;

    notify_handler_t clients[MAX_CLIENT];
}env_sensor_t;



env_sensor_t *env_sensor_create(void);
void env_sensor_init(env_sensor_t *const me);

void env_sensor_get_data(env_sensor_t *const me);
void env_sensor_notify(env_sensor_t *const me);
void env_sensor_dumplist(env_sensor_t *const me);

void env_sensor_destroy(env_sensor_t *const me);


#endif /* INC_ENV_SENSOR_H_ */