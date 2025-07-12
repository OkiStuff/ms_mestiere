#include "map.h"
#include "function.h"
#include "types.h"
#include "scene.h"

void map_free(map_generic_t* map)
{
	MS_FREE(map->data);
	map->data = NULL;
	map->size = 0;
	map->capacity = 0;
}

uint64_t map_hash_int(int value)
{
	return (uint64_t)(value);
}

uint64_t map_hash_double(double value)
{
	return (uint64_t)(value);
}

uint64_t map_hash_pointer_t(void* value)
{
	uintptr_t x = (uintptr_t)(value);
	x ^= x >> 33;
	x *= 0xff51afd7ed558ccdULL;
	x ^= x >> 33;
	x *= 0xc4ceb9fe1a85ec53ULL;
	x ^= x >> 33;

	return x;
}

uint64_t map_hash_string_t(const char* value)
{
	return map_hash_pointer_t((void*)(value));
}

uint64_t map_hash_mz_vec2(mz_vec2 vec2)
{
	union {float f; uint32_t i;} x = {vec2.x};
	union {float f; uint32_t i;} y = {vec2.y};

	if (x.i == 0x80000000) x.i = 0;
	if (y.i == 0x80000000) y.i = 0;

	uint64_t hash = (uint64_t)(x.i * 0x9e3779b97f4a7c15ULL);
	hash ^= (uint64_t)(x.i * 0x9e3779b97f4a7c13ULL);
	hash ^= hash >> 32;
	
	return hash;
}

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
		if (map->compare_key(map->data[index].key, key))\
		{\
			break;\
		}\
		index = (index + 1) % map->capacity;\
	}\
	bool_t has_old_value = FALSE;\
	if (map->data[index].occupied)\
	{\
		has_old_value = TRUE;\
		if (old_value_out != NULL) *old_value_out = map->data[index].value;\
	}\
	else\
	{\
		map->size++;\
	}\
	map->data[index].occupied = TRUE;\
	map->data[index].key = key;\
	map->data[index].value = value;\
	return has_old_value;\
}\
bool_t MAP_FUNC(K,V,contains)(MAP(K,V)* map, K key)\
{\
	size_t index = map->hash(key) % map->capacity;\
	const size_t starting_index = index;\
	while (map->data[index].occupied)\
	{\
		if (map->compare_key(map->data[index].key, key))\
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
		if (map->compare_key(map->data[index].key, key))\
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
		if (map->compare_key(map->data[index].key, key))\
		{\
			if (old_value_out != NULL) *old_value_out = map->data[index].value;\
			map->data[index].occupied = FALSE;\
			map->data[index].key = ((K){0});\
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
void MAP_FUNC(K,V,foreach)(MAP(K,V)* map, void* dataptr, TRICONSUMER(pointer_t, K, pointer_t) callback)\
{\
	/* TODO: If we ever need foreach more often, it may be work while to\
	 * add some sort of array that tracks the current existing\
	 * key/value pairs instead of iterating through the entire\
	 * buffer looking for existing key/value pairs */\
	for (int i = 0, entries_found = 0; i < map->capacity && entries_found < map->size; i++)\
	{\
		if (map->data[i].occupied)\
		{\
			callback(dataptr, map->data[i].key, &map->data[i].value);\
			entries_found++;\
		}\
	}\
}\
void MAP_FUNC(K,V,init_with_capacity)(MAP(K,V)* map, size_t initial_capacity)\
{\
	map->data = MS_CALLOC(initial_capacity, sizeof(MAP_ENTRY(K,V)));\
	map->capacity = initial_capacity;\
	map->size = 0;\
	map->hash = map_hash_##K;\
	map->put = MAP_FUNC(K,V,put);\
	map->contains = MAP_FUNC(K,V,contains);\
	map->get = MAP_FUNC(K,V,get);\
	map->get_or_default = MAP_FUNC(K,V,get_or_default);\
	map->remove = MAP_FUNC(K,V,remove);\
	map->foreach = MAP_FUNC(K,V,foreach);\
	map->compare_key = map_##K##_compare_key;\
	if (map->data == NULL)\
	{\
		/* TODO: Add logging */\
		printf("ERROR: Memory allocation failed\n");\
		exit(-1);\
	}\
}\
void MAP_FUNC(K,V,init)(MAP(K,V)* map)\
{\
	MAP_FUNC(K,V,init_with_capacity)(map, MAP_DEFAULT_CAPACITY);\
}\
void MAP_FUNC(K,V,init_with_capacity_and_hash)(MAP(K,V)* map, MAP_HASH_FUNC_TYPE(K) hash_function, size_t initial_capacity)\
{\
	MAP_FUNC(K,V,init_with_capacity)(map, initial_capacity);\
	map->hash = hash_function;\
}\
void MAP_FUNC(K,V,init_with_hash)(MAP(K,V)* map, MAP_HASH_FUNC_TYPE(K) hash_function)\
{\
	MAP_FUNC(K,V,init_with_capacity_and_hash)(map, hash_function, MAP_DEFAULT_CAPACITY);\
}

#define IMPLEMENT_SIMPLE_COMPARE_KEY(K) \
bool_t map_##K##_compare_key(K a, K b) \
{\
	return a == b;\
}

// All maps, regardless of definition location, will be implemented here

IMPLEMENT_SIMPLE_COMPARE_KEY(int)

// map.h
IMPLEMENT_MAP(int, pointer_t)
IMPLEMENT_MAP(int, int)
IMPLEMENT_MAP(int, mz_vec2)

// scene.h
IMPLEMENT_MAP(int, scene_t)
