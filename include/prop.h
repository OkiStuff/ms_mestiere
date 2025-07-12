#ifndef MESTIERE_PROP_H
#define MESTIERE_PROP_H

#include <Muzzle.h>
#include <stdint.h>

typedef struct prop_t prop_t;

typedef void (*prop_func_t)(prop_t*, mz_applet*);

typedef struct prop_t
{
	mz_sprite sprite;
	uint32_t attributes;
	prop_func_t update;
	prop_func_t render;
} prop_t;

#endif // MESTIERE_PROP_H
