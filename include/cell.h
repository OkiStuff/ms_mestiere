#ifndef MESTIERE_CELL_H
#define MESTIERE_CELL_H

#include "prop.h"
#include "types.h"
#include <Muzzle.h>

#define CELL_WIDTH 64
#define CELL_HEIGHT 64

typedef enum
{
	CELL_TYPE_GRASS = 0,
	CELL_TYPE_STONE,
	CELL_TYPE_SAND,
	CELL_TYPE_WATER,
	NUM_CELL_TYPES
} cell_type_t;

typedef struct cell_t
{
	mz_sprite* sprite;
	mz_vec2_i position;
	cell_type_t type;
	prop_t prop;
	bool_t has_prop:1;
} cell_t;

cell_t cell_init(cell_type_t type, mz_vec2_i position);
void cell_put_prop(cell_t* cell, prop_t prop);
void cell_remove_prop(cell_t* cell);
void cell_update(cell_t* cell, mz_applet* applet);
void cell_render(cell_t* cell, mz_applet* applet, float x, float y);

#endif // MESTIERE_CELL_H
