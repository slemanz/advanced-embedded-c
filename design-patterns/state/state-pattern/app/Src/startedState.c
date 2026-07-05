#include "startedState.h"
#include "stoppedState.h"

static void stopWatch(watchStatePtr state)
{
    transitionToStopped(state);
}

void transitionToStarted(watchStatePtr state)
{
    defaultImplementation(state);
    state->stop = stopWatch;
}