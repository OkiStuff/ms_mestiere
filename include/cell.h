#ifndef MESTIERE_CELL_H
#define MESTIERE_CELL_H

#include "prop.h"
#include "types.h"
#include <Muzzle.h>

typedef enum
{
	CELL_TYPE_GRASS = 0,
	CELL_TYPE_STONE,
	CELL_TYPE_SAND,
	CELL_TYPE_WATER
} cell_type_t;

typedef struct cell_t
{
	mz_sprite sprite;
	cell_type_t type;
	prop_t prop;
	bool_t has_prop:1;
} cell_t;

#endif // MESTIERE_CELL_H
