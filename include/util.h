#ifndef UTIL_H__
#define UTIL_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int GJU_ReallocArray(void **ptr, size_t currentNum, size_t wantNum, size_t sizeOfIndividualObject);

int GJU_RemoveArrayEntry(void **ptr, size_t currentNum, size_t positionToRemove, size_t sizeOfIndividualObject);

int GJU_AddArrayEntry(void **ptr, size_t currentNum, void *objectPtr, size_t sizeOfIndividualObject);

void GJU_SafeFree(void *ptr);

#ifdef __cplusplus
}
#endif
#endif
