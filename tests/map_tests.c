#include "map.h"
#include <prova.h>

PV_TEST(init_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test initialization of hashmap");

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	PV_EXPECT_NEQ(map.data, NULL);
	PV_EXPECT_EQ(map.size, 0);
	PV_EXPECT_EQ(map.capacity, MAP_DEFAULT_CAPACITY);
	PV_EXPECT_EQ(map.hash, map_hash_int);
	PV_EXPECT_EQ(map.put, map_int_int_put);
	PV_EXPECT_EQ(map.contains, map_int_int_contains);
	PV_EXPECT_EQ(map.get, map_int_int_get);
	PV_EXPECT_EQ(map.get_or_default, map_int_int_get_or_default);
	PV_EXPECT_EQ(map.remove, map_int_int_remove);
	PV_EXPECT_EQ(map.foreach, map_int_int_foreach);
	PV_EXPECT_EQ(map.compare_key, map_int_compare_key);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

PV_TEST(init_with_capacity_test)
{
	
	PV_REGISTRY;
	PV_DESCRIPTION("Test initialization of hashmap");

	MAP(int, int) map;
	MAP_INIT_WITH_CAPACITY(int, int, &map, 100);

	PV_EXPECT_NEQ(map.data, NULL);
	PV_EXPECT_EQ(map.size, 0);
	PV_EXPECT_EQ(map.capacity, 100);
	PV_EXPECT_EQ(map.hash, map_hash_int);
	PV_EXPECT_EQ(map.put, map_int_int_put);
	PV_EXPECT_EQ(map.contains, map_int_int_contains);
	PV_EXPECT_EQ(map.get, map_int_int_get);
	PV_EXPECT_EQ(map.get_or_default, map_int_int_get_or_default);
	PV_EXPECT_EQ(map.remove, map_int_int_remove);
	PV_EXPECT_EQ(map.foreach, map_int_int_foreach);
	PV_EXPECT_EQ(map.compare_key, map_int_compare_key);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

static uint64_t my_hash(int value)
{
	return 100;
}

PV_TEST(init_with_hash_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test initialization of hashmap");

	MAP(int, int) map;
	MAP_INIT_WITH_HASH(int, int, &map, my_hash);

	PV_EXPECT_NEQ(map.data, NULL);
	PV_EXPECT_EQ(map.size, 0);
	PV_EXPECT_EQ(map.capacity, MAP_DEFAULT_CAPACITY);
	PV_EXPECT_EQ(map.hash, my_hash);
	PV_EXPECT_EQ(map.put, map_int_int_put);
	PV_EXPECT_EQ(map.contains, map_int_int_contains);
	PV_EXPECT_EQ(map.get, map_int_int_get);
	PV_EXPECT_EQ(map.get_or_default, map_int_int_get_or_default);
	PV_EXPECT_EQ(map.remove, map_int_int_remove);
	PV_EXPECT_EQ(map.foreach, map_int_int_foreach);
	PV_EXPECT_EQ(map.compare_key, map_int_compare_key);

	uint64_t map_hash_result = map.hash(0);
	uint64_t my_hash_result = my_hash(0);

	PV_EXPECT_EQ(map_hash_result, my_hash_result);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

PV_TEST(init_with_capacity_and_hash_test)
{
	
	PV_REGISTRY;
	PV_DESCRIPTION("Test initialization of hashmap");

	MAP(int, int) map;
	MAP_INIT_WITH_CAPACITY_AND_HASH(int, int, &map, my_hash, 100);

	PV_EXPECT_NEQ(map.data, NULL);
	PV_EXPECT_EQ(map.size, 0);
	PV_EXPECT_EQ(map.capacity, 100);
	PV_EXPECT_EQ(map.hash, my_hash);
	PV_EXPECT_EQ(map.put, map_int_int_put);
	PV_EXPECT_EQ(map.contains, map_int_int_contains);
	PV_EXPECT_EQ(map.get, map_int_int_get);
	PV_EXPECT_EQ(map.get_or_default, map_int_int_get_or_default);
	PV_EXPECT_EQ(map.remove, map_int_int_remove);
	PV_EXPECT_EQ(map.foreach, map_int_int_foreach);
	PV_EXPECT_EQ(map.compare_key, map_int_compare_key);

	uint64_t map_hash_result = map.hash(0);
	uint64_t my_hash_result = my_hash(0);

	PV_EXPECT_EQ(map_hash_result, my_hash_result);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

PV_TEST(free_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hashmap free");

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	map_free((map_generic_t*)(&map));

	PV_EXPECT_EQ(map.data, NULL);
	PV_EXPECT_EQ(map.size, 0);
	PV_EXPECT_EQ(map.capacity, 0);
	
	PV_RETURN_SUCCESS;
}

PV_TEST(hash_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hash functions");

	uint64_t int_hash1 = map_hash_int(1);
	uint64_t int_hash2 = map_hash_int(1);
	PV_EXPECT_EQ(int_hash1, int_hash2);

	uint64_t double_hash1 = map_hash_double(1.5);
	uint64_t double_hash2 = map_hash_double(1.5);
	PV_EXPECT_EQ(double_hash1, double_hash2);

	int a = 9;
	uint64_t pointer_hash1 = map_hash_pointer_t(&a);
	uint64_t pointer_hash2 = map_hash_pointer_t(&a);
	PV_EXPECT_EQ(pointer_hash1, pointer_hash2);

	const char* b = "Hello, World\n";
	uint64_t string_hash1 = map_hash_string_t(b);
	uint64_t string_hash2 = map_hash_string_t(b);
	PV_EXPECT_EQ(string_hash1, string_hash2);

	PV_RETURN_SUCCESS;
}

PV_TEST(put_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hashmap put");

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	bool_t put_5_10 = map.put(&map, 5, 10, NULL);
	PV_EXPECT_EQ(put_5_10, FALSE);

	int put_6_12_old_value = 999;
	bool_t put_6_12 = map.put(&map, 6, 12, &put_6_12_old_value);
	PV_EXPECT_EQ(put_6_12, FALSE);
	PV_EXPECT_EQ(put_6_12_old_value, 999);

	bool_t put_7_14 = map.put(&map, 7, 14, NULL);
	int put_7_13_old_value = 999;
	size_t initial_size = map.size;
	bool_t put_7_13 = map.put(&map, 7, 13, &put_7_13_old_value);
	PV_EXPECT_EQ(put_7_14, FALSE);
	PV_EXPECT_EQ(put_7_13, TRUE);
	PV_EXPECT_EQ(put_7_13_old_value, 14);
	PV_EXPECT_EQ(map.size, initial_size);

	size_t capacity = map.capacity;

	for (int i = 0; i < capacity; i++)
	{
		map.put(&map, i, i, NULL);
	}

	PV_EXPECT_NEQ(map.capacity, capacity);
	PV_EXPECT_EQ(map.capacity, capacity * 2);

	PV_EXPECT_EQ(map.size, capacity);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

PV_TEST(get_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hashmap get");

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	map.put(&map, 5, 10, NULL);
	int* value = map.get(&map, 5);
	PV_EXPECT_EQ(*value, 10);
	
	map.put(&map, 5, 13, NULL);
	PV_EXPECT_EQ(*value, 13);

	int* no_value = map.get(&map, 7);
	PV_EXPECT_EQ(no_value, NULL);

	int default_value = 999;
	int* get_or_default = map.get_or_default(&map, 7, &default_value);
	PV_EXPECT_EQ(*get_or_default, default_value);

	map_free((map_generic_t*)(&map));
	PV_RETURN_SUCCESS;
}

PV_TEST(remove_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hashmap remove");

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	map.put(&map, 5, 10, NULL);
	map.remove(&map, 5, NULL);
	int* put_remove_null_value = map.get(&map, 5);
	PV_EXPECT_EQ(put_remove_null_value, NULL);
	PV_EXPECT_EQ(map.data[map.hash(5)].key, 0);
	PV_EXPECT_EQ(map.data[map.hash(5)].value, 0);
	PV_EXPECT_EQ(map.data[map.hash(5)].occupied, FALSE);

	map.put(&map, 5, 10, NULL);
	int old_value = 999;
	map.remove(&map, 5, &old_value);
	PV_EXPECT_EQ(old_value, 10);

	PV_RETURN_SUCCESS;
}

struct foreach_test_data
{
	bool_t good;
	int iterations;
};

static void foreach_biconsumer(void* dataptr, int key, void* value)
{
	struct foreach_test_data* data = (struct foreach_test_data*)(dataptr);
	int* v = (int*)(value);
	data->good = v != NULL && ((key == 5 && *v == 10) || (key == 6 && *v == 12));
	data->iterations++;
}

PV_TEST(foreach_test)
{
	PV_REGISTRY;
	PV_DESCRIPTION("Test hashmap foreach");

	struct foreach_test_data data = (struct foreach_test_data){0};

	MAP(int, int) map;
	MAP_INIT(int, int, &map);

	map.put(&map, 5, 10, NULL);
	map.put(&map, 6, 12, NULL);
	map.foreach(&map, &data, foreach_biconsumer);

	PV_EXPECT_EQ(data.good, TRUE);
	PV_EXPECT_EQ(data.iterations, 2);
	PV_RETURN_SUCCESS;
}

PV_TEST_SUITE(map_tests, "Hashmap Tests", PV_DEFAULT_CONFIG,
              init_test,
              init_with_capacity_test,
              init_with_hash_test,
              init_with_capacity_and_hash_test,
              free_test,
              hash_test,
              put_test,
              get_test,
              remove_test,
              foreach_test
)
