#include "player.h"
#include "assets.h"

player_t player_init(mz_vec2 position)
{
    player_t player = (player_t){0};
    player.position = position;
    player.sprite = &images.player;

    return player;
}

void player_update(player_t* player, mz_applet* applet)
{

}

void player_render(player_t* player, mz_applet* applet)
{
    mz_draw_sprite(applet, player->sprite, (applet->width - player->sprite->width) / 2.f, (applet->height - player->sprite->height) / 2.f, TINT_WHITE);
}
