#ifndef STATE_H__
#define STATE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*StateInitCB)(void *);/* get the manager pointer */
typedef void(*StateLogicCB)();
typedef void(*StateEventCB)(void *);/* event data */
typedef void(*StateRenderCB)();
typedef void(*StateDestroyCB)();

/* typedef int(*StatePollCB)(void *); */
typedef int(*StatePollCB)();
/* typedef void(*StateDelayCB)(); */


typedef struct
{
  const char *name;
  StateInitCB CB_Init;
  StateLogicCB CB_Logic;
  StateEventCB CB_Event;
  StateRenderCB CB_Render;
  StateDestroyCB CB_Destroy;
} gju_state_t;

typedef struct
{
  size_t stateNum;
  gju_state_t *states;
  const char *currentStateName;
  size_t cacheStateNum; /* this is only used internally */
  void *event; /* for something like SDL_Event */
  StatePollCB PollEvent; /* something to poll events */
  short using_foreground;
  /* foreground stuff */
  StateInitCB CB_ForegroundInit;
  StateLogicCB CB_ForegroundLogic;
  StateEventCB CB_ForegroundEvent;
  StateRenderCB CB_ForegroundRender;
  StateDestroyCB CB_ForegroundDestroy;
} gju_state_manager_t;



int GJU_InitStateManager(gju_state_manager_t *state_manager);

int GJU_AddState(gju_state_manager_t *state_manager, const char *name, StateInitCB CB_Initf, StateLogicCB CB_Logicf, StateEventCB CB_Eventf, StateRenderCB CB_Renderf, StateDestroyCB CB_Destroyf);

int GJU_AddForegroundState(gju_state_manager_t *state_manager, StateInitCB CB_ForegroundInitf, StateLogicCB CB_ForegroundLogicf, StateEventCB CB_ForegroundEventf, StateRenderCB CB_ForegroundRenderf, StateDestroyCB CB_ForegroundDestroyf);

int GJU_DestroyStateManager(gju_state_manager_t *state_manager);

int GJU_ResetStateManager(gju_state_manager_t *state_manager);

int GJU_ChangeState(gju_state_manager_t *state_manager, const char *name);

void GJU_TickState(gju_state_manager_t *state_manager);

void GJU_RenderState(gju_state_manager_t *state_manager);


#ifdef __cplusplus
}
#endif
#endif
