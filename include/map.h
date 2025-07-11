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
#include <Muzzle.h> // only for vec2 hash

#define MAP_FUNC(K, V, name) map_##K##_##V##_##name
#define MAP(K, V) map_##K##_##V##_t

#define MAP_STATIC_ASSERTIONS(K, V) \
_Static_assert(offsetof(MAP(K,V), data) == offsetof(map_generic_t, data), "Offset mismatch: data");\
_Static_assert(offsetof(MAP(K,V), size) == offsetof(map_generic_t, size), "Offset mismatch: size");\
_Static_assert(offsetof(MAP(K,V), capacity) == offsetof(map_generic_t, capacity), "Offset mismatch: size")

#define MAP_ENTRY(K, V) map_##K##_##V##_entry_t
#define MAP_HASH_FUNC_TYPE(K) map_hash_##K##_func_t

#define DEFINE_MAP_HASH_FUNC_TYPE(K) typedef uint64_t (*MAP_HASH_FUNC_TYPE(K))(K)

#define DEFINE_MAP_ENTRY(K, V) \
typedef struct MAP_ENTRY(K,V) \
{\
	K key;\
	V value;\
	bool_t occupied:1;\
} MAP_ENTRY(K,V)

#define DEFINE_COMPARE_KEY(K) \
bool_t map_##K##_compare_key(K, K)

#define DEFINE_MAP(K, V) \
DEFINE_MAP_ENTRY(K,V);\
typedef struct MAP(K,V) \
{\
	MAP_ENTRY(K,V)* data;\
	size_t size;\
	size_t capacity;\
	MAP_HASH_FUNC_TYPE(K) hash;\
	bool_t (*put)(struct MAP(K,V)*, K, V, V*);\
	bool_t (*contains)(struct MAP(K,V)*, K);\
	V* (*get)(struct MAP(K,V)*, K);\
	V* (*get_or_default)(struct MAP(K,V)*, K, V*);\
	bool_t (*remove)(struct MAP(K,V)*, K, V*);\
	void (*foreach)(struct MAP(K,V)*, biconsumer_int_pointer_t_func_t);\
	bool_t (*compare_key)(K, K);\
} MAP(K,V);\
bool_t MAP_FUNC(K,V,put)(MAP(K,V)*, K, V, V*);\
bool_t MAP_FUNC(K,V,contains)(MAP(K,V)*, K);\
V* MAP_FUNC(K,V,get)(MAP(K,V)*, K);\
V* MAP_FUNC(K,V,get_or_default)(MAP(K,V)*, K, V*);\
bool_t MAP_FUNC(K,V,remove)(MAP(K,V)*, K, V*);\
void MAP_FUNC(K,V,foreach)(MAP(K,V)*, biconsumer_int_pointer_t_func_t);\
void MAP_FUNC(K,V,init_with_capacity)(MAP(K,V)*, size_t);\
void MAP_FUNC(K,V,init)(MAP(K,V)*);\
void MAP_FUNC(K,V,init_with_capacity_and_hash)(MAP(K,V)*, MAP_HASH_FUNC_TYPE(K), size_t);\
void MAP_FUNC(K,V,init_with_hash)(MAP(K,V)*, MAP_HASH_FUNC_TYPE(K));\
MAP_STATIC_ASSERTIONS(K,V)

#define MAP_INIT(K, V, map_ptr) MAP_FUNC(K,V,init)(map_ptr)
#define MAP_INIT_WITH_CAPACITY(K, V, map_ptr, initial_capacity) MAP_FUNC(K,V,init_with_capacity)(map_ptr, initial_capacity)
#define MAP_INIT_WITH_HASH(K, V, map_ptr, hash_function) MAP_FUNC(K,V,init_with_hash)(map_ptr, hash_function)
#define MAP_INIT_WITH_CAPACITY_AND_HASH(K, V, map_ptr, hash_function, initial_capacity) MAP_FUNC(K,V,init_with_capacity_and_hash)(map_ptr, hash_function, initial_capacity)

typedef struct map_generic_t
{
	void* data;
	size_t size;
	size_t capacity;
} map_generic_t;

DEFINE_MAP_HASH_FUNC_TYPE(int);
DEFINE_MAP_HASH_FUNC_TYPE(double);
DEFINE_MAP_HASH_FUNC_TYPE(pointer_t);
DEFINE_MAP_HASH_FUNC_TYPE(string_t);
DEFINE_MAP_HASH_FUNC_TYPE(mz_vec2);

uint64_t map_hash_int(int value);
uint64_t map_hash_double(double value);
uint64_t map_hash_pointer_t(void* value);
uint64_t map_hash_string_t(const char* value);
uint64_t map_hash_mz_vec2(mz_vec2 vec2);

DEFINE_COMPARE_KEY(int);

DEFINE_MAP(int, pointer_t);
DEFINE_MAP(int, int);
DEFINE_MAP(int, mz_vec2);

void map_free(map_generic_t* map);

#endif // MESTIERE_MAP_H
