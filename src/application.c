#include "application.h"

static void applet_dispatch(mz_applet* applet)
{
	(void)(applet);
}

static void applet_loop(mz_applet* applet, scene_manager_t* manager)
{
	while (mz_keep_applet(applet))
	{
		scene_manager_update(manager, applet);
		
		mz_begin_drawing(applet);
			scene_manager_render(manager, applet);
		mz_end_drawing(applet);
	}
}

application_t application_init(const char* title, int width, int height, mz_applet_flags flags)
{
	application_t app = (application_t){0};
	app.scene_manager = scene_manager_init();
	app.applet = mz_initialize_applet(title, width, height, flags);

	return app;
}

void application_start(application_t* app)
{
	scene_manager_init_scenes(&app->scene_manager, &app->applet);
	mz_start_applet(&app->applet, applet_dispatch);
	applet_loop(&app->applet, &app->scene_manager);
}

void application_terminate(application_t* app)
{
	scene_manager_unload_scenes(&app->scene_manager, &app->applet);
	mz_terminate_applet(&app->applet);
}

void application_unload(application_t* app)
{
	scene_manager_unload(&app->scene_manager);
}
