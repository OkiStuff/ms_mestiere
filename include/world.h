#ifndef MESTIERE_WORLD_H
#define MESTIERE_WORLD_H

#include "cell.h"
#include "player.h"

#define WORLD_WIDTH 512
#define WORLD_HEIGHT 512

typedef struct world_t
{
    cell_t* cells;
    player_t player;
} world_t;

world_t world_init();
void world_update(world_t* world, mz_applet* applet);
void world_render(world_t* world, mz_applet* applet);
void world_unload(world_t* world);

#endif // MESTIERE_WORLD_H
