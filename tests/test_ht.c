#include "ht.h"
#include "ht_internal.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

void setUp(void) {}

void tearDown(void) {
  if (ht_table != NULL)
    free(ht_table);
  ht_table = NULL;
}

void test_ht_ensure_ht_table_initializes_as_null() {
  TEST_ASSERT_NULL(ht_table);
}

void test_ht_table_init_should_init_a_table_if_not_exist() {
  ht_table_t *expected = calloc(1, sizeof(ht_table_t));
  TEST_ASSERT_NOT_NULL_MESSAGE(expected, "failed to allocate a test table");

  ht_table_t *actual = table_init();
  TEST_ASSERT_NOT_NULL_MESSAGE(actual, "failed to initialize table");

  TEST_ASSERT_EQUAL_MEMORY(expected, actual, sizeof(ht_table_t));

  free(expected);
  // actual is freed in teardown
}

void test_ht_table_get_should_return_an_ht_table(void) {
  ht_table_t *expected = calloc(1, sizeof(ht_table_t));
  TEST_ASSERT_NOT_NULL_MESSAGE(expected, "failed to allocate a test table");

  ht_table_t *actual = table_get();
  TEST_ASSERT_NOT_NULL_MESSAGE(actual, "failed to get new table");

  TEST_ASSERT_EQUAL_MEMORY(expected, actual, sizeof(ht_table_t));

  free(expected);
  // actual is freed in teardown
}

void test_ht_key_get_len_should_return_the_len_of_an_item_key(void) {
  struct test_case {
    char *key;
    size_t len;
  };
#define SHOULD_VERIFY_KEY_LEN 4

  struct test_case cases[SHOULD_VERIFY_KEY_LEN] = {
      {"1", strlen("1")},
      {"yolo", strlen("yolo")},
      {"diochuimhneachadh", strlen("diochuimhneachadh")},
      {"somereallylongstringeh", strlen("somereallylongstringeh")},
  };
  for (int i = 0; i < SHOULD_VERIFY_KEY_LEN; i++)
    TEST_ASSERT_EQUAL_size_t(cases[i].len, key_get_len(cases[i].key));
}

void test_ht_hash_should_hash_an_item_key(void) {
  struct test_case {
    char *key;
    unsigned expected;
  };

#define SHOULD_VERIFY_HASH_VALUES 5

  struct test_case prime_1_cases[SHOULD_VERIFY_HASH_VALUES] = {
      {"key", 19u},          {"key", 19u},           {"yolo", 17u},
      {"onomatopoeia", 20u}, {"somelongstring", 2u},
  };

  for (int i = 0; i < SHOULD_VERIFY_HASH_VALUES; i++) {
    unsigned actual = hash(prime_1_cases[i].key,
                           strnlen(prime_1_cases[i].key, 20), HT_PRIME_1);
    TEST_ASSERT_EQUAL_UINT(prime_1_cases[i].expected, actual);
  }

  struct test_case prime_2_cases[SHOULD_VERIFY_HASH_VALUES] = {
      {"key", 33u},
      {"key", 33u},
      {"yolo", 7u},
      {"onomatopoeia", 21u},
      {"somelongstring", 33u},
  };

  for (int i = 0; i < SHOULD_VERIFY_HASH_VALUES; i++) {
    unsigned actual = hash(prime_2_cases[i].key,
                           strnlen(prime_2_cases[i].key, 20), HT_PRIME_2);
    TEST_ASSERT_EQUAL_UINT(prime_2_cases[i].expected, actual);
  }
}

void test_ht_item_hash_should_hash_an_item_key_and_probe_on_duplicates() {
  struct test_case {
    char *key;
    unsigned expected;
  };

#define SHOULD_VERIFY_DOUBLE_HASH_VALUES 6
  struct test_case cases[SHOULD_VERIFY_DOUBLE_HASH_VALUES] = {
      {"key", 19u},  {"key", 53u},          {"yolo", 17u},
      {"yolo", 25u}, {"onomatopoeia", 20u}, {"onomatopeoia", 42u},
  };

  unsigned actual = 0;

  // simulate that an index is already occupied

  // first attempt with "key"
  actual = item_hash(cases[0].key, strnlen(cases[0].key, 20), 0);
  TEST_ASSERT_EQUAL_UINT(cases[0].expected, actual);

  // second attempt with "key"
  actual = item_hash(cases[1].key, strnlen(cases[1].key, 20), 1);
  TEST_ASSERT_EQUAL_UINT(cases[1].expected, actual);

  // first attempt with "yolo"
  actual = item_hash(cases[2].key, strnlen(cases[2].key, 20), 0);
  TEST_ASSERT_EQUAL_UINT(cases[2].expected, actual);

  // second attempt with "yolo"
  actual = item_hash(cases[3].key, strnlen(cases[3].key, 20), 1);
  TEST_ASSERT_EQUAL_UINT(cases[3].expected, actual);

  // first attempt with "onomatopoeia"
  actual = item_hash(cases[4].key, strnlen(cases[4].key, 20), 0);
  TEST_ASSERT_EQUAL_UINT(cases[4].expected, actual);

  // second attempt with "onomatopoeia"
  actual = item_hash(cases[5].key, strnlen(cases[5].key, 20), 1);
  TEST_ASSERT_EQUAL_UINT(cases[5].expected, actual);
}

void test_ht_item_lookup_should_return_null() {
  ht_table_t *ht = table_get();
  const char key[] = "key";

  // not found
  const ht_item_t *ht_item_not_found = item_lookup(ht, key, strlen(key));
  TEST_ASSERT_NULL(ht_item_not_found);
}

void test_ht_item_lookup_should_return_ht_item() {
  ht_table_t *ht = table_get();
  const char key[] = "key";
  // found
  const unsigned try = 19;
  ht_item_t *item = (ht_item_t *)&(*ht)[try];
  item->key = key;
  item->value = "1";
  const ht_item_t *ht_item_found = item_lookup(ht, key, strlen(key));
  TEST_ASSERT_NOT_NULL(ht_item_found);
  TEST_ASSERT_EQUAL_STRING(item->key, ht_item_found->key);
  TEST_ASSERT_EQUAL_STRING(item->value, ht_item_found->value);
}

void test_ht_put_var_should_create_an_item_in_ht_table() {
  // int ht_put_var(const char *, const char *);
}

void test_ht_get_var_should_create_an_item_in_ht_table() {
  // const char *ht_get_var(const char *);
}

void test_ht_del_var_should_create_an_item_in_ht_table() {
  // int ht_del_var(const char *);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ht_ensure_ht_table_initializes_as_null);
  RUN_TEST(test_ht_table_init_should_init_a_table_if_not_exist);
  RUN_TEST(test_ht_table_get_should_return_an_ht_table);
  RUN_TEST(test_ht_item_lookup_should_return_null);
  RUN_TEST(test_ht_item_lookup_should_return_ht_item);
  RUN_TEST(test_ht_hash_should_hash_an_item_key);
  RUN_TEST(test_ht_item_hash_should_hash_an_item_key_and_probe_on_duplicates);
  RUN_TEST(test_ht_key_get_len_should_return_the_len_of_an_item_key);
  RUN_TEST(test_ht_get_var_should_create_an_item_in_ht_table);
  RUN_TEST(test_ht_put_var_should_create_an_item_in_ht_table);
  RUN_TEST(test_ht_del_var_should_create_an_item_in_ht_table);

  return UNITY_END();
}
