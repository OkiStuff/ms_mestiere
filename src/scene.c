#include "scene.h"

scene_manager_t scene_manager_init(void)
{
	scene_manager_t manager = (scene_manager_t){0};
	MAP_INIT(int, scene_t, &manager.scenes);
	
	return manager;
}

void scene_manager_update(scene_manager_t* manager, mz_applet* applet)
{
	manager->current_scene->update(manager->current_scene, applet, manager);
}

void scene_manager_render(scene_manager_t* manager, mz_applet* applet)
{
	manager->current_scene->render(manager->current_scene, applet, manager);
}

void scene_manager_switch_scene(scene_manager_t* manager, uint8_t id)
{
	if (manager->current_scene != NULL && manager->current_scene->leave != NULL)
	{
		manager->current_scene->leave(manager->current_scene, manager);
	}

	manager->current_scene = manager->scenes.get(&manager->scenes, id);

	if (manager->current_scene == NULL)
	{
		// TODO: Add logging
		printf("ERROR: No scene at id %d", id);
		exit(-1);
	}

	if (manager->current_scene->enter == NULL)
	{
		manager->current_scene->enter(manager->current_scene, manager);
	}
}

void scene_manager_add_scene(scene_manager_t* manager, scene_t scene)
{
	manager->scenes.put(&manager->scenes, scene.id, scene, NULL);

	if (manager->current_scene == NULL)
	{
		manager->current_scene = manager->scenes.get(&manager->scenes, scene.id);
	}
}

struct init_scenes_dependencies
{
	mz_applet* applet;
	scene_manager_t* manager;
};

static void init_scenes(void* dependencies, int key, void* pointer)
{
	(void)(key);
	struct init_scenes_dependencies* deps = (struct init_scenes_dependencies*)(dependencies);
	
	scene_t* scene = (scene_t*)(pointer);
	scene->init(scene, deps->applet, deps->manager);
}

void scene_manager_init_scenes(scene_manager_t* manager, mz_applet* applet)
{
	struct init_scenes_dependencies deps = (struct init_scenes_dependencies){.applet = applet, .manager = manager};
	manager->scenes.foreach(&manager->scenes, &deps, init_scenes);
}

static void unload_scenes(void* dependencies, int key, void* pointer)
{
	(void)(key);
	struct init_scenes_dependencies* deps = (struct init_scenes_dependencies*)(dependencies);

	scene_t* scene = (scene_t*)(pointer);

	if (scene->unload != NULL)
	{
		scene->unload(scene, deps->applet, deps->manager);
	}
}

void scene_manager_unload_scenes(scene_manager_t* manager, mz_applet* applet)
{
	struct init_scenes_dependencies deps = (struct init_scenes_dependencies){.applet = applet, .manager = manager};
	manager->scenes.foreach(&manager->scenes, &deps, unload_scenes);
}

void scene_manager_unload(scene_manager_t* manager)
{
	manager->current_scene = NULL;
	map_free((map_generic_t*)(&manager->scenes));
}
