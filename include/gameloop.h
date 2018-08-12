#ifndef GAMELOOP_H__
#define GAMELOOP_H__

#include <stddef.h>


#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

short GJU_GLoopExit = 0;

typedef void(*DelayCB)(int milliseconds);
typedef unsigned int(*GetTicksCB)();


void GJU_SimpleGameLoop(size_t tick_hz, size_t max_frameskip, DelayCB Delayf, GetTicksCB GetTicksf, gju_state_manager_t *manager);

#ifdef __cplusplus
}
#endif
#endif
