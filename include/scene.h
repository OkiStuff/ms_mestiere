#ifndef MESTIERE_SCENE_H
#define MESTIERE_SCENE_H

#include "map.h"
#include <Muzzle.h>

typedef struct scene_manager_t scene_manager_t;
typedef struct scene_t scene_t;

typedef void (*scene_func_t)(scene_t*, mz_applet*, scene_manager_t*);
typedef void (*scene_enter_leave_func_t)(scene_t*, scene_manager_t*);

#define SCENE(scene, scene_id) ((scene_t){.init = scene##_init, .id = scene_id})

typedef struct scene_t
{
	scene_func_t init;
	scene_func_t update;
	scene_func_t render;
	scene_func_t unload;
	scene_enter_leave_func_t enter;
	scene_enter_leave_func_t leave;
	void* data;
	uint8_t id;
} scene_t;

DEFINE_MAP(int, scene_t);

typedef struct scene_manager_t
{
	MAP(int, scene_t) scenes;
	scene_t* current_scene;
} scene_manager_t;

scene_manager_t scene_manager_init(void);
void scene_manager_update(scene_manager_t* manager, mz_applet* applet);
void scene_manager_render(scene_manager_t* manager, mz_applet* applet);
void scene_manager_switch_scene(scene_manager_t* manager, uint8_t id);
void scene_manager_add_scene(scene_manager_t* manager, scene_t scene);
void scene_manager_init_scenes(scene_manager_t* manager, mz_applet* applet);
void scene_manager_unload_scenes(scene_manager_t* manager, mz_applet* applet);
void scene_manager_unload(scene_manager_t* manager);

#endif // MESTIERE_SCENE_H
