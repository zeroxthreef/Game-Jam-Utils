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


int GJU_InitScene(gju_scene_manager_t *manager);

int GJU_AddObject(gju_scene_manager_t *manager, char *type, char *name, short visible, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf, void *data);

int GJU_RemoveObjectByName(gju_scene_manager_t *manager, char *type, char *name);

int GJU_RemoveObjectByType(gju_scene_manager_t *manager, char *type);

void *GJU_GetObjectByName(gju_scene_manager_t *manager, char *type, char *name);

gju_scene_object_t *GJU_GetObjectByIndex(gju_scene_manager_t *manager, size_t index);

void GJU_DestroyScene(gju_scene_manager_t *manager);

#ifdef __cplusplus
}
#endif
#endif
