#ifndef MESTIERE_SCENES_GAME_SCENE_H
#define MESTIERE_SCENES_GAME_SCENE_H

#include <Muzzle.h>
#include "scene.h"

#define GAME_SCENE_ID 0

typedef struct game_scene_t
{
	mz_vec2 pos;
} game_scene_t;

void game_scene_init(scene_t* scene, mz_applet* applet, scene_manager_t* manager);
void game_scene_update(scene_t* scene, mz_applet* applet, scene_manager_t* manager);
void game_scene_render(scene_t* scene, mz_applet* applet, scene_manager_t* manager);

#endif // MESTIERE_SCENES_GAME_SCENE_H
