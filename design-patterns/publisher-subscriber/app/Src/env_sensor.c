#include "env_sensor.h"
#include <stdlib.h>
#include <stdio.h>

env_sensor_t *env_sensor_create(void)
{
    env_sensor_t *me = (env_sensor_t*)malloc(sizeof(env_sensor_t));
    if(me != NULL)
    {
        env_sensor_init(me);
    }
    return me;
}

void env_sensor_init(env_sensor_t *const me)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        me->clients[i].pObject = NULL;
        me->clients[i].fn_handler = NULL;
    }
    me->n_client = 0;
}

void env_sensor_get_data(env_sensor_t *const me)
{
    me->data.temperature = (rand() % 100);
    me->data.humidity = (rand() % 100);
    me->data.sprayed = 0;

    // notify all clients
    env_sensor_notify(me);
}

void env_sensor_notify(env_sensor_t *const me)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        if(me->clients[i].pObject != NULL && me->clients[i].fn_handler != NULL)
        {
            me->clients[i].fn_handler(me->clients[i].pObject, me->data);
        }
    }
}

void env_sensor_dumplist(env_sensor_t *const me)
{
    printf("Dumplist: \t Number of clients %ld\n", me->n_client);
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        if(me->clients[i].pObject != NULL && me->clients[i].fn_handler != NULL)
        {
            printf("\t pObject: %p \t fn_handler: %p\n", me->clients[i].pObject, me->clients[i].fn_handler);
        }
    }
}

void env_sensor_destroy(env_sensor_t *const me)
{
    // do something
    free(me);
}