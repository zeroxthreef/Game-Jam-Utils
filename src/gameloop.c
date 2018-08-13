#include "gameloop.h"
#include "state.h"
#include "util.h"

#include <stdio.h>

short GJU_GLoopExit = 0;

void GJU_SimpleGameLoop(size_t tick_hz, size_t max_frameskip, DelayCB Delayf, GetTicksCB GetTicksf, gju_state_manager_t *manager)
{
  unsigned int skipTime = 0, lastframeLag = 0, frameskipCount = 0, current_tick = 0;


  current_tick = GetTicksf();

  while(!GJU_GLoopExit)
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
      if(frameskipCount >= (unsigned int)max_frameskip)
      {
        /* render */
        GJU_RenderState(manager);
      }
    }


    current_tick += 1000/(unsigned int)tick_hz;


    /*skipTime = current_tick - GetTicksf();

    if(skipTime >= 0)
    {
      Delayf(skipTime);
    }
    else
    {
      lastframeLag = 1;
    }*/
  }
}

void GJU_GameLoopExit(short value){GJU_GLoopExit = value;}
