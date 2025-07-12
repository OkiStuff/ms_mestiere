#include "assets.h"
#include "cell.h"
#include "core/applet.h"
#include "primitives/sprite.h"

struct assets_images images = (struct assets_images){0};

static inline void images_cells_init()
{
    images.cells[CELL_TYPE_GRASS] = mz_load_sprite(ASSETS_DIR "images/cells/grass.png");
    images.cells[CELL_TYPE_STONE] = mz_load_sprite(ASSETS_DIR "images/cells/stone.png");
    images.cells[CELL_TYPE_SAND] = mz_load_sprite(ASSETS_DIR "images/cells/sand.png");
    images.cells[CELL_TYPE_WATER] = mz_load_sprite(ASSETS_DIR "images/cells/water.png");
}

static inline void images_cells_unload()
{
    for (int i = 0; i < NUM_CELL_TYPES; i++)
    {
        mz_unload_sprite(&images.cells[i]);
    }
}

static inline void images_init()
{
    images_cells_init();
    images.player = mz_load_sprite(ASSETS_DIR "images/player.png"); // TODO: Change
}

static inline void images_unload()
{
    images_cells_unload();
}

void assets_init(mz_applet* applet)
{
    images_init();
}

void assets_unload(mz_applet* applet)
{
    images_unload();
}
