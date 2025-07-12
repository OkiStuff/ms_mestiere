#include <Muzzle.h>
#include <stdio.h>
#include "mem.h"
#include "application.h"

#include "scenes/game_scene.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

static void init_scenes(application_t* app)
{
    scene_manager_add_scene(&app->scene_manager, SCENE(game_scene, GAME_SCENE_ID));
}

int main(void)
{
    application_t app = application_init("My Muzzle App", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    init_scenes(&app);
    application_start(&app);
    application_terminate(&app);
    application_unload(&app);
    
    return 0;
}
