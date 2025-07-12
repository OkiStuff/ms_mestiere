#ifndef MESTIERE_ASSETS_H
#define MESTIERE_ASSETS_H

#include <Muzzle.h>
#include "cell.h"

#ifndef ASSETS_DIR
    #define ASSETS_DIR "../"
#endif

struct assets_images
{
    mz_sprite cells[NUM_CELL_TYPES];
    mz_sprite player;
};

struct assets_images images;

void assets_init(mz_applet* applet);
void assets_unload(mz_applet* applet);

#endif // MESTIERE_ASSETS_H
