#ifndef INC_MEDIATOR_H_
#define INC_MEDIATOR_H_

// Forward declaration for context structure
typedef struct EmbeddedSystem_t EmbeddedSystem_t;

// mediator interface
typedef struct
{
    void (*notify)(EmbeddedSystem_t *system, const char *event);
}Mediator_t;

#endif /* INC_MEDIATOR_H_ */