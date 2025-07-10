#include "map.h"
#include "function.h"
#include "types.h"

#define IMPLEMENT_MAP(K, V) \
bool_t MAP_FUNC(K,V,put)(MAP(K,V)* map, K key, V value, V* old_value_out)\
{\
	if (map->size > map->capacity * MAP_LOAD_FACTOR_THRESHOLD)\
	{\
		if (map->capacity >= SIZE_MAX / 2)\
		{\
			/* TODO: Standard log */\
			printf("ERROR: Map cannot grow any larger\n");\
			exit(-1);\
		}\
		map->capacity *= MAP_GROWTH_RATE;\
		map->data = MS_REALLOC(map->data, sizeof(void*) * map->capacity);\
		if (map->data == NULL)\
		{\
			/* TODO: Add logging */\
			printf("ERROR: Memory allocation failed\n");\
			exit(-1);\
		}\
	}\
	size_t index = map->hash(key) % map->capacity;\
	/* Because it is an open-addressing hash map, this will never result in an infinite loop */\
	while (map->data[index].occupied)\
	{\
		if (map->data[index].compare_key(&map->data[index], key))\
		{\
			break;\
		}\
		index = (index + 1) % map->capacity;\
	}\
	bool_t has_old_value = FALSE;\
	if (map->data[index].occupied)\
	{\
		has_old_value = TRUE;\
		*old_value_out = map->data[index].value;\
	}\
	else\
	{\
		map->size++;\
	}\
	map->data[index].occupied = TRUE;\
	map->data[index].value = value;\
	return has_old_value;\
}\
bool_t MAP_FUNC(K,V,contains)(MAP(K,V)* map, K key)\
{\
	size_t index = map->hash(key) % map->capacity;\
	const size_t starting_index = index;\
	while (map->data[index].occupied)\
	{\
		if (map->data[index].compare_key(&map->data[index], key))\
		{\
			return TRUE;\
		}\
		index = (index + 1) % map->capacity;\
		if (index == starting_index || !map->data[index].occupied)\
		{\
			break;\
		}\
	}\
	return FALSE;\
}\
V* MAP_FUNC(K,V,get)(MAP(K,V)* map, K key)\
{\
	size_t index = map->hash(key) % map->capacity;\
	const size_t starting_index = index;\
	while (map->data[index].occupied)\
	{\
		if (map->data[index].compare_key(&map->data[index], key))\
		{\
			return &map->data[index].value;\
		}\
		index = (index + 1) % map->capacity;\
		if (index == starting_index || !map->data[index].occupied)\
		{\
			break;\
		}\
	}\
	return NULL;\
}\
V* MAP_FUNC(K,V,get_or_default)(MAP(K,V)* map, K key, V* default_value)\
{\
	V* value = map->get(map, key);\
	return (value != NULL) ? value : default_value;\
}\
bool_t MAP_FUNC(K,V,remove)(MAP(K,V)* map, K key, V* old_value_out)\
{\
	size_t index = map->hash(key) % map->capacity;\
	const size_t starting_index = index;\
	while (map->data[index].occupied)\
	{\
		if (map->data[index].compare_key(&map->data[index], key))\
		{\
			*old_value_out = map->data[index].value;\
			map->data[index].occupied = FALSE;\
			map->data[index].value = ((V){0});\
			return TRUE;\
		}\
		index = (index + 1) % map->capacity;\
		if (index == starting_index || !map->data[index].occupied)\
		{\
			break;\
		}\
	}\
	return FALSE;\
}\
void MAP_FUNC(K,V,foreach)(MAP(K,V)* map, biconsumer_int_pointer_t_func_t callback)\
{\
	/* TODO: If we ever need foreach more often, it may be work while to\
	 * add some sort of array that tracks the current existing\
	 * key/value pairs instead of iterating through the entire\
	 * buffer looking for existing key/value pairs */\
	for (int i = 0, entries_found = 0; i < map->capacity && entries_found < map->size; i++)\
	{\
		if (map->data[i].occupied)\
		{\
			callback(map->data[i].key, map->data[i].value);\
			entries_found++;\
		}\
	}\
}

IMPLEMENT_MAP(int, pointer_t)
