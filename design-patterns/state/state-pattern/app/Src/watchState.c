#include "watchState.h"

static void defaultStop(watchStatePtr state)
{

}

static void defaultStart(watchStatePtr state)
{

}

void defaultImplementation(watchStatePtr state)
{
    state->start = defaultStart;
    state->stop = defaultStop;
}
