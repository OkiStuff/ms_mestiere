#ifndef MESTIERE_PLAYER_H
#define MESTIERE_PLAYER_H

#include <Muzzle.h>

typedef struct player_t
{
    mz_vec2 position;
    mz_sprite* sprite;
} player_t;

player_t player_init(mz_vec2 position);
void player_update(player_t* player, mz_applet* applet);
void player_render(player_t* player, mz_applet* applet);

#endif // MESTIERE_PLAYER_H
