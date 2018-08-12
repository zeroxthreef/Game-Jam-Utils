#include "util.h"
#include "state.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int GJU_ReallocArray(void **ptr, size_t currentNum, size_t wantNum, size_t sizeOfIndividualObject) /* NOTE can just pass it a NULL pointer and it allocates it and stuff */
{
  void *tempPtr = NULL;

  /* printf("pointer0 %p pointer1 %p\n", ptr, *ptr); */
  if(*ptr == NULL)
  {
    tempPtr = calloc(wantNum, sizeOfIndividualObject);

    if(tempPtr == NULL)
      return 1;
    else
      *ptr = tempPtr;
  }
  else
  {
    tempPtr = realloc(*ptr, sizeOfIndividualObject * wantNum);
    if(tempPtr == NULL)
      return 1;
    else
      *ptr = tempPtr;
  }
  return 0;
}

int GJU_RemoveArrayEntry(void **ptr, size_t currentNum, size_t positionToRemove, size_t sizeOfIndividualObject)
{
  void *destPtr = *ptr + (positionToRemove * sizeOfIndividualObject);
  void *selectptr = *ptr + ((positionToRemove + 1) * sizeOfIndividualObject);


  /* TODO check if it is the last item because there is nothing to copy after that */

  if(positionToRemove == currentNum)
  {
    if(!GJU_ReallocArray(ptr, currentNum - 1, currentNum - 1, sizeOfIndividualObject))
      return 0;
    else
      return 1;
  }
  else
  {
    memmove(destPtr, selectptr, sizeOfIndividualObject * (currentNum - positionToRemove));
    if(!GJU_ReallocArray(ptr, currentNum - 1, currentNum - 1, sizeOfIndividualObject))
    {
      return 0;
    }
    else
      return 1;
  }

  return 0;
}

int GJU_AddArrayEntry(void **ptr, size_t currentNum, void *objectPtr, size_t sizeOfIndividualObject)
{
  if(!GJU_ReallocArray(ptr, currentNum, currentNum + 1, sizeOfIndividualObject))
  {
    /* ptr[currentNum + 1] = *objectPtr; */
    void *tempPtr = *ptr + (currentNum) * sizeOfIndividualObject;
    /* tempPtr = *objectPtr; */
    memcpy(tempPtr, objectPtr, sizeOfIndividualObject);
    /* printf("[%c] [%c]\n", *((char *)tempPtr), *((char *)tempPtr)); */
  }
  else
  {
    return 1;
  }

  return 0;
}

void GJU_SafeFree(void *ptr)
{
  if(ptr != NULL)
    free(ptr);
}

void GJU_SimpleGameLoop(size_t tick_hz, size_t max_frameskip, DelayCB Delayf, GetTicksCB GetTicksf, gju_state_manager_t *manager)
{
  int skipTime = 0, lastframeLag = 0, frameskipCount = 0, current_tick = 0;


  current_tick = GetTicksf();

  while(!GJU_GlobalExit)
  {
    /* call state event functions */
    /* call state logic functions */
    GJU_TickState(manager);

    if(!lastframeLag)
    {
      frameskipCount = 0;
      /* render */
      GJU_RenderState(manager);
    }
    else
    {
      lastframeLag = 0;
      if(frameskipCount >= max_frameskip)
      {
        /* render */
        GJU_RenderState(manager);
      }
    }


    current_tick += 1000/tick_hz;


    skipTime = current_tick - GetTicksf();

    if(skipTime >= 0)
    {
      Delayf(skipTime);
    }
    else
    {
      lastframeLag = 1;
    }
  }
}
