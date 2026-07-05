#ifndef INC_WATCHSTATE_H_
#define INC_WATCHSTATE_H_

typedef struct watchState *watchStatePtr;

typedef void (*eventStartFunc)(watchStatePtr);
typedef void (*eventStopFunc)(watchStatePtr);

struct watchState
{
    eventStartFunc start;
    eventStopFunc stop;
};

void defaultImplementation(watchStatePtr state);

#endif /* INC_WATCHSTATE_H_ */