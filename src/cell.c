#include "cell.h"
#include "assets.h"

cell_t cell_init(cell_type_t type, mz_vec2_i position)
{
    cell_t cell = (cell_t){0};
    cell.type = type;
    cell.sprite = &images.cells[type];
    cell.position = position;

    return cell;
}

void cell_put_prop(cell_t* cell, prop_t prop)
{
    cell->prop = prop;
    cell->has_prop = TRUE;
}

void cell_remove_prop(cell_t* cell)
{
    cell->prop = (prop_t){0};
    cell->has_prop = FALSE;
}

void cell_update(cell_t* cell, mz_applet* applet)
{
    if (cell->has_prop)
    {
        cell->prop.update(&cell->prop, applet);
    }
}

void cell_render(cell_t* cell, mz_applet* applet, float x, float y)
{
    mz_draw_sprite(applet, cell->sprite, x, y, TINT_WHITE);

    if (cell->has_prop)
    {
        cell->prop.render(&cell->prop, applet);
    }
}
