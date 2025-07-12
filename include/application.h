#ifndef MESTIERE_APPLICATION_H
#define MESTIERE_APPLICATION_H

#include "core/applet.h"
#include "scene.h"
#include <Muzzle.h>

typedef struct application_t
{
	mz_applet applet;
	scene_manager_t scene_manager;
} application_t;

application_t application_init(const char* title, int width, int height, mz_applet_flags flags);
void application_start(application_t* app);
void application_terminate(application_t* app);
void application_unload(application_t* app);

#endif // MESTIERE_APPLICATION_H
