#include "env_display_client.h"
#include <stdlib.h>
#include <stdio.h>

display_client_t *display_client_create(void)
{
    display_client_t *me = (display_client_t *)malloc(sizeof(display_client_t));
    if(me != NULL)
    {
        display_client_init(me);
    }
    return me;
}

void display_client_init(display_client_t *const me)
{
    me->fn_handler = display_client_handleNewData;
}

void display_client_handleNewData(void *me, env_data_t data)
{
    ((display_client_t *)me)->data = data;

    // process data
    printf("display_module:\t New data: %ld %ld %d\n",
                            ((display_client_t*)me)->data.temperature,
                            ((display_client_t*)me)->data.humidity,
                            ((display_client_t*)me)->data.sprayed);

}

void display_client_subscribe(display_client_t *const me, env_sensor_t *const server)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        // check if client is already subscribe
        if(server->clients[i].pObject == me)
        {
            return;
        }

        // add new client
        if(server->clients[i].pObject == NULL)
        {
            server->n_client++;
            server->clients[i].pObject = me;
            server->clients[i].fn_handler = me->fn_handler;

            // remove duplicate
            for(int j = i +1; j < MAX_CLIENT; j++)
            {
                if(server->clients[j].pObject == me)
                {
                    server->clients[j].pObject = NULL;
                    server->clients[j].fn_handler = NULL;
                }
            }
            return;
        }
    }
}

void display_client_unsubscribe(display_client_t *const me, env_sensor_t *const server)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        if(server->clients[i].pObject == me)
        {
            server->clients[i].pObject = NULL;
            server->clients[i].fn_handler = NULL;
            server->n_client--;
            return;
        }
    }
}

void display_client_destroy(display_client_t *const me)
{
    free(me);
}