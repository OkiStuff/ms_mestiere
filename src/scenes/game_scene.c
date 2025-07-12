#include "scenes/game_scene.h"
#include "mem.h"

void game_scene_init(scene_t* scene, mz_applet* applet, scene_manager_t* manager)
{
	game_scene_t this = (game_scene_t){0};

	scene->data = MS_MALLOC(sizeof(game_scene_t));
	scene->update = game_scene_update;
	scene->render = game_scene_render;

	if (scene->data == NULL)
	{
		// TODO: Add logging
		printf("ERROR: Memory allocation failed\n");
		exit(-1);
	}

	*(game_scene_t*)(scene->data) = this;
}

void game_scene_update(scene_t* scene, mz_applet* applet, scene_manager_t* manager)
{
	game_scene_t* this = scene->data;

	this->pos.x += 100 * applet->delta_time;
	this->pos.y += 100 * applet->delta_time;
}

void game_scene_render(scene_t* scene, mz_applet* applet, scene_manager_t* manager)
{
	game_scene_t* this = scene->data;
	
	mz_clear_screen(TINT_BLACK);
	mz_draw_circle_vec2(applet, this->pos, 50.f, TINT_PINK);
}
