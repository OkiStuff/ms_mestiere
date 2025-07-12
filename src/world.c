#include "player.h"
#define FNL_IMPL
#include "FastNoiseLite.h"
#include "world.h"
#include "mem.h"
#include "cell.h"

#include <stdio.h>

#define NOISE_SCALE 0.1

world_t world_init()
{
    world_t world = (world_t){0};
    world.cells = MS_MALLOC(sizeof(cell_t) * WORLD_WIDTH * WORLD_HEIGHT);
    world.player = player_init((mz_vec2){WORLD_WIDTH / 2.f, WORLD_HEIGHT / 2.f});;

    if (world.cells == NULL)
    {
        // TODO: Add logging
        printf("ERROR: Memory allocation failed\n");
        exit(-1);
    }

    fnl_state noise_generator = fnlCreateState();
    noise_generator.noise_type = FNL_NOISE_PERLIN;

    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            float v = fnlGetNoise2D(&noise_generator, x * NOISE_SCALE, y * NOISE_SCALE);
            cell_type_t cell_type;

            if (v < 0.25)       cell_type = CELL_TYPE_STONE;
            else if (v < 0.4)   cell_type = CELL_TYPE_GRASS;
            else if (v < 0.7)   cell_type = CELL_TYPE_WATER;
            else                cell_type = CELL_TYPE_SAND;

            world.cells[y * WORLD_WIDTH + x] = cell_init(cell_type, (mz_vec2_i){x,y});
        }
    }

    return world;
}

void world_update(world_t* world, mz_applet* applet)
{
    for (int i = 0; i < WORLD_WIDTH * WORLD_HEIGHT; i++)
    {
        cell_update(&world->cells[i], applet);
    }
}

void world_render(world_t* world, mz_applet* applet)
{
    int half_width_cells = applet->width / (2 * CELL_WIDTH); // Confusingish formula, (width / 2) / CELL_WIDTH, (a/b)/c = a/(bc).
    int half_height_cells = applet->height / (2 * CELL_HEIGHT);
    mz_vec2_i top_left_cell = (mz_vec2_i){world->player.position.x - half_width_cells, world->player.position.y - half_height_cells};
    mz_vec2_i bottom_right_cell = (mz_vec2_i){world->player.position.x + half_width_cells, world->player.position.y + half_height_cells};

    for (int y = top_left_cell.y; y < bottom_right_cell.y; y++)
    {
        for (int x = top_left_cell.x; x < bottom_right_cell.x; x++)
        {
            mz_vec2_i screen_position = (mz_vec2_i){(x - world->player.position.x) * CELL_WIDTH, (y - world->player.position.y) * CELL_HEIGHT};
            cell_render(&world->cells[y * WORLD_WIDTH + x], applet, screen_position.x, screen_position.y);
        }
    }

    player_render(&world->player, applet);
}

void world_unload(world_t* world)
{
    MS_FREE(world->cells);
}
