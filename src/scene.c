#include "scene.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GJU_InitScene(gju_scene_manager_t *manager)
{
  manager->objects = NULL;
  manager->object_num = 0;
  return 0;
}

int GJU_AddObject(gju_scene_manager_t *manager, char *type, char *name, short visible, size_t lifetime, ObjectDestroyCB CB_DestroyObjectf, void *data)
{
  gju_scene_object_t tempObj;

  tempObj.name = malloc(strlen(name) + 1);
  tempObj.name[0] = 0x00;
  strcat(tempObj.name, name);

  tempObj.type = malloc(strlen(type) + 1);
  tempObj.type[0] = 0x00;
  strcat(tempObj.type, type);

  tempObj.lifetime = lifetime;
  tempObj.lifetimeBegin = manager->getticks();

  tempObj.CB_DestroyObject = CB_DestroyObjectf;

  tempObj.visible = visible;

  tempObj.data = data;

  if(GJU_AddArrayEntry(&manager->objects, manager->object_num, &tempObj, sizeof(gju_scene_object_t)))
    printf("SCENE: Huge error. Not going to do anything about it though because I don't have time\n");


  manager->object_num++;

  return 0;
}

int GJU_RemoveObjectByName(gju_scene_manager_t *manager, char *type, char *name)
{
  size_t i;

  for(i = 0; i < manager->object_num; i++)
  {
    if(strcmp(manager->objects[i].name, name) == 0 && strcmp(manager->objects[i].type, type))
    {
      manager->objects[i].CB_DestroyObject(name, type, manager->objects[i].data);
      GJU_SafeFree(manager->objects[i].name);
      GJU_SafeFree(manager->objects[i].type);


      GJU_RemoveArrayEntry(&manager->objects, manager->object_num, i, sizeof(gju_scene_object_t));
      return 0;
    }
  }

  return 1;
}

int GJU_RemoveObjectByType(gju_scene_manager_t *manager, char *type)
{
  size_t i;

  for(i = 0; i < manager->object_num; i++)
  {
    if(strcmp(manager->objects[i].type, type))
    {
      manager->objects[i].CB_DestroyObject(manager->objects[i].name, type, manager->objects[i].data);
      GJU_SafeFree(manager->objects[i].name);
      GJU_SafeFree(manager->objects[i].type);


      GJU_RemoveArrayEntry(&manager->objects, manager->object_num, i, sizeof(gju_scene_object_t));
    }
  }

  return 0;
}

void *GJU_GetObjectByName(gju_scene_manager_t *manager, char *type, char *name)
{
  size_t i;

  for(i = 0; i < manager->object_num; i++)
  {
    if(strcmp(manager->objects[i].name, name) == 0 && strcmp(manager->objects[i].type, type))
    {

      return &manager->objects[i];
    }
  }

  return NULL;
}

gju_scene_object_t *GJU_GetObjectByIndex(gju_scene_manager_t *manager, size_t index)
{
  if(index < manager->object_num)
    return &manager->objects[index];


  return NULL;
}

void GJU_DestroyScene(gju_scene_manager_t *manager)
{
  size_t i;

  for(i = 0; i < manager->object_num; i++)
  {
    manager->objects[i].CB_DestroyObject(manager->objects[i].name, manager->objects[i].type, manager->objects[i].data);
    GJU_SafeFree(manager->objects[i].name);
    GJU_SafeFree(manager->objects[i].type);


    GJU_RemoveArrayEntry(&manager->objects, manager->object_num, i, sizeof(gju_scene_object_t));
  }
}
