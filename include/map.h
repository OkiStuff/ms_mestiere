#ifndef MESTIERE_MAP_H
#define MESTIERE_MAP_H

/*
* Open Addressing Hashmap Implemention 
*/

#define MAP_LOAD_FACTOR_THRESHOLD 0.7
#define MAP_GROWTH_RATE 2
#define MAP_DEFAULT_CAPACITY 8

#include "function.h"
#include "types.h"
#include "mem.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_FUNC(K, V, name) map_##K##_##V##_##name
#define MAP(K, V) map_##K##_##V##_t

// #define MAP_STATIC_ASSERTIONS(K, V) \
// _Static_assert(offsetof(MAP(K,V), data) == offsetof(generic_map_t, data), "Offset mismatch: data");\
// _Static_assert(offsetof(MAP(K,V), size) == offsetof(generic_map_t, size), "Offset mismatch: size");\
// _Static_assert(offsetof(MAP(K,V), capacity) == offsetof(generic_map_t, capacity), "Offset mismatch: size")

#define MAP_ENTRY(K, V) map_##K##_##V##_entry_t

#define DEFINE_MAP_ENTRY(K, V) \
typedef struct MAP_ENTRY(K,V) \
{\
	K key;\
	V value;\
	bool_t occupied:1;\
	bool_t (*compare_key)(struct MAP_ENTRY(K,V)*, K);\
} MAP_ENTRY(K,V)

#define DEFINE_MAP(K, V) \
DEFINE_MAP_ENTRY(K,V);\
typedef struct MAP(K,V) \
{\
	MAP_ENTRY(K,V)* data;\
	size_t size;\
	size_t capacity;\
	uint64_t (*hash)(K);\
	bool_t (*put)(struct MAP(K,V)*, K, V, V*);\
	bool_t (*contains)(struct MAP(K,V)*, K);\
	V* (*get)(struct MAP(K,V)*, K);\
	V* (*get_or_default)(struct MAP(K,V)*, K, V*);\
	bool_t (*remove)(struct MAP(K,V)*, K, V*);\
	void (*foreach)(struct MAP(K,V)*, biconsumer_int_pointer_t_func_t);\
} MAP(K,V);\
bool_t MAP_FUNC(K,V,put)(MAP(K,V)*, K, V, V*);\
bool_t MAP_FUNC(K,V,contains)(MAP(K,V)*, K);\
V* MAP_FUNC(K,V,get)(MAP(K,V)*, K);\
V* MAP_FUNC(K,V,get_or_default)(MAP(K,V)*, K, V*);\
bool_t MAP_FUNC(K,V,remove)(MAP(K,V)*, K, V*);\
void MAP_FUNC(K,V,foreach)(MAP(K,V)*, biconsumer_int_pointer_t_func_t)

DEFINE_MAP(int, pointer_t);

#endif // MESTIERE_MAP_H
