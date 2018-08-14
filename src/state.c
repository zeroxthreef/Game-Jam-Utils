#include "state.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int GJU_InitStateManager(gju_state_manager_t *state_manager)
{

  state_manager->stateNum = 0;
  state_manager->states = NULL;
  state_manager->currentStateName = NULL;
  state_manager->cacheStateNum = 0;
  state_manager->using_foreground = 0;

  return 0;
}

int GJU_AddState(gju_state_manager_t *state_manager, const char *name, StateInitCB CB_Initf, StateLogicCB CB_Logicf, StateEventCB CB_Eventf, StateRenderCB CB_Renderf, StateDestroyCB CB_Destroyf)
{
  static short first_state = 1;
  gju_state_t tempState;

  tempState.name = name;
  tempState.CB_Init = CB_Initf;
  tempState.CB_Logic = CB_Logicf;
  tempState.CB_Event = CB_Eventf;
  tempState.CB_Destroy = CB_Destroyf;
  tempState.CB_Render = CB_Renderf;
  if(GJU_AddArrayEntry(&state_manager->states, state_manager->stateNum, &tempState, sizeof(gju_state_t)))
    printf("Huge error. Not going to do anything about it though because I don't have time\n");

  if(first_state)
  {
    tempState.CB_Init(state_manager);
    state_manager->currentStateName = tempState.name;
    first_state = 0;
  }

  state_manager->stateNum++;
  return 0;
}

int GJU_AddForegroundState(gju_state_manager_t *state_manager, StateInitCB CB_ForegroundInitf, StateLogicCB CB_ForegroundLogicf, StateEventCB CB_ForegroundEventf, StateRenderCB CB_ForegroundRenderf, StateDestroyCB CB_ForegroundDestroyf)
{
  /* TODO add error checking */
  state_manager->CB_ForegroundInit = CB_ForegroundInitf;
  state_manager->CB_ForegroundLogic = CB_ForegroundLogicf;
  state_manager->CB_ForegroundEvent = CB_ForegroundEventf;
  state_manager->CB_ForegroundRender = CB_ForegroundRenderf;
  state_manager->CB_ForegroundDestroy = CB_ForegroundDestroyf;

  state_manager->CB_ForegroundInit(state_manager);
  state_manager->using_foreground = 1;

  return 0;
}

int GJU_DestroyStateManager(gju_state_manager_t *state_manager)
{
  if(state_manager->stateNum > 0)
    state_manager->states[state_manager->cacheStateNum].CB_Destroy();
  if(state_manager->using_foreground)
    state_manager->CB_ForegroundDestroy();
  free(state_manager->states);
  return 0;
}

int GJU_ResetStateManager(gju_state_manager_t *state_manager)
{
  GJU_DestroyStateManager(state_manager);
  GJU_InitStateManager(state_manager);
}

int GJU_ChangeState(gju_state_manager_t *state_manager, const char *name)
{
  size_t i;
  /* clear last state, scan for state names, then cache its number */
  state_manager->states[state_manager->cacheStateNum].CB_Destroy();

  for(i = 0; i < state_manager->stateNum; i++)
  {
    if(strcmp(state_manager->states[i].name, name) == 0)
    {
      state_manager->states[i].CB_Init(state_manager);
      state_manager->cacheStateNum = i;
      state_manager->currentStateName = state_manager->states[i].name;

      return 0;
    }
  }


  return 1; /* return error only if it cannot find the state */
}

void GJU_TickState(gju_state_manager_t *state_manager)
{
  while(state_manager->PollEvent(state_manager->event))//state_manager->event
  {
    /* Call all event callbacks */
    if(state_manager->stateNum > 0)
      state_manager->states[state_manager->cacheStateNum].CB_Event(state_manager->event);
    if(state_manager->using_foreground)
      state_manager->CB_ForegroundEvent(state_manager->event);
  }

  /* call logic functions */
  if(state_manager->stateNum > 0)
    state_manager->states[state_manager->cacheStateNum].CB_Logic();
  if(state_manager->using_foreground)
    state_manager->CB_ForegroundLogic();
}

void GJU_RenderState(gju_state_manager_t *state_manager)
{
  /* call render functions */
  if(state_manager->stateNum > 0)
    state_manager->states[state_manager->cacheStateNum].CB_Render();
  if(state_manager->using_foreground)
    state_manager->CB_ForegroundRender();
}
