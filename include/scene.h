#ifndef STATE_H__
#define STATE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*ObjectDestroyCB)(char *, char *, void *); /* (char *name, char *type, void *data) */
typedef unsigned int(*SceneGetTicks)(void);

typedef struct
{
  char *name;
  char *type;
  void *data;
  short visible;
  size_t lifetime;
  size_t lifetimeBegin;
  ObjectDestroyCB CB_DestroyObject;
} gju_scene_object_t;

typedef struct
{
  gju_scene_object_t *objects;
  size_t object_num;
  SceneGetTicks getticks;
} gju_scene_manager_t;

#ifdef __cplusplus
}
#endif
#endif
