#include "fertilizer_mixer_client.h"
#include <stdlib.h>
#include <stdio.h>

fertilizer_mixer_client_t *fertilizer_mixer_client_create(void)
{
    fertilizer_mixer_client_t *me = (fertilizer_mixer_client_t *)malloc(sizeof(fertilizer_mixer_client_t));
    if(me != NULL)
    {
        fertilizer_mixer_client_init(me);
    }
    return me;
}

void fertilizer_mixer_client_init(fertilizer_mixer_client_t *const me)
{
    me->fn_handler = fertilizer_mixer_client_handleNewData;
}

void fertilizer_mixer_client_handleNewData(void *me, env_data_t data)
{
    ((fertilizer_mixer_client_t *)me)->data = data;

    // process data
    printf("fertilizer_mixer_module:\t New data: %ld %ld %d\n",
                            ((fertilizer_mixer_client_t*)me)->data.temperature,
                            ((fertilizer_mixer_client_t*)me)->data.humidity,
                            ((fertilizer_mixer_client_t*)me)->data.sprayed);

}

void fertilizer_mixer_client_subscribe(fertilizer_mixer_client_t *const me, env_sensor_t *const server)
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

void fertilizer_mixer_client_unsubscribe(fertilizer_mixer_client_t *const me, env_sensor_t *const server)
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

void fertilizer_mixer_client_destroy(fertilizer_mixer_client_t *const me)
{
    free(me);
}