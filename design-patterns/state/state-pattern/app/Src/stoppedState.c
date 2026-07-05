#include "stoppedState.h"
#include "startedState.h"

static void startWatch(watchStatePtr state)
{
    defaultImplementation(state);
}

void transitionToStopped(watchStatePtr state)
{
    transitionToStarted(state);
    state->start = startWatch;
}