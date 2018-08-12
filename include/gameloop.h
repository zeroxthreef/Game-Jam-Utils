#ifndef GAMELOOP_H__
#define GAMELOOP_H__

#include <stddef.h>


#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*DelayCB)(int milliseconds);
typedef unsigned int(*GetTicksCB)();


void GJU_SimpleGameLoop(size_t tick_hz, size_t max_frameskip, DelayCB Delayf, GetTicksCB GetTicksf, gju_state_manager_t *manager);

void GJU_GameLoopExit(short value);

#ifdef __cplusplus
}
#endif
#endif
