#ifndef INC_COLLEAGUE_H_
#define INC_COLLEAGUE_H_

#include "mediator.h"

/* Base colleague structure */
typedef struct Colleague_t Colleague_t;

struct Colleague_t
{
    Mediator_t *mediator;
    void (*sendEvent)(Colleague_t *colleague, const char *event);
    void (*performAction)(Colleague_t *colleague, const char *action);
};


/* Concrete object types */

typedef struct{
    Colleague_t base;
} Light_t;

typedef struct{
    Colleague_t base;
} Thermostat_t;

typedef struct{
    Colleague_t base;
} SecuritySystem_t;

Light_t* light_create(Mediator_t* mediator);
void lightPerformAction(Colleague_t *colleague, const char *action);

Thermostat_t *thermostat_create(Mediator_t *mediator);
void thermostatPerformAction(Colleague_t* colleague, const char* action);

SecuritySystem_t *securitySystem_create(Mediator_t *mediator);
void securitySystemPerformAction(Colleague_t *colleague, const char *action);

#endif /* INC_COLLEAGUE_H_  */