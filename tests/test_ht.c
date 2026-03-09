#include "ht_internal.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

/*
STATIC ht_table_t *table_init(void);
STATIC ht_item_t *item_lookup(const ht_table_t *, const char *, const size_t);
STATIC unsigned item_hash(const char *, const size_t, const unsigned);
STATIC size_t key_get_len(const char *);
*/

void test_ht_table_get_should_return_an_ht_table(void) {
  ht_table_t *ht = table_get();
}
void test_ht_item_lookup_should_return_an_ht_item(void) {}
void test_ht_item_hash_should_hash_an_item_key(void) {}
void test_ht_key_get_len_should_return_the_len_of_an_item_key(void) {}
void test_ht_table_init_should_initialize_a_table_if_not_exist_else_return_it(
    void) {}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ht_table_get_should_return_an_ht_table);
  RUN_TEST(test_ht_item_lookup_should_return_an_ht_item);
  RUN_TEST(test_ht_item_hash_should_hash_an_item_key);
  RUN_TEST(test_ht_key_get_len_should_return_the_len_of_an_item_key);
  RUN_TEST(
      test_ht_table_init_should_initialize_a_table_if_not_exist_else_return_it);

  return UNITY_END();
}
