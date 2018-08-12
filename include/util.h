#ifndef UTIL_H__
#define UTIL_H__

#include <stddef.h>

#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

short GJU_GlobalExit = 0;

typedef void(*DelayCB)(int milliseconds);
typedef unsigned int(*GetTicksCB)();

int GJU_ReallocArray(void **ptr, size_t currentNum, size_t wantNum, size_t sizeOfIndividualObject);

int GJU_RemoveArrayEntry(void **ptr, size_t currentNum, size_t positionToRemove, size_t sizeOfIndividualObject);

int GJU_AddArrayEntry(void **ptr, size_t currentNum, void *objectPtr, size_t sizeOfIndividualObject);

void GJU_SafeFree(void *ptr);

void GJU_SimpleGameLoop(size_t tick_hz, size_t max_frameskip, DelayCB Delayf, GetTicksCB GetTicksf, gju_state_manager_t *manager);

#ifdef __cplusplus
}
#endif
#endif
