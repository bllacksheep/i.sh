#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_MAX 1000
#define HT_MAX_KEY_LEN 20

enum ht_errors {
  ERRHTINIT = 100,
  ERRHTGET,
  ERRHTINS,
  ERRHTDEL,
  ERRHTNOKEYLEN,
  ERRHTNOTABLE,
  ERRHTNOBUF,
  ERRHTNOITEM,
};

typedef struct ht_item {
  char *key;
  char *value;
} ht_item_t;

typedef ht_item_t ht_table_t[HT_MAX];
static ht_table_t *ht_table = NULL;

static ht_table_t *table_init(void);
static ht_table_t *table_get(void);
static ht_item_t *item_lookup(const ht_table_t *, const char *, const size_t);
static unsigned item_hash(const char *, const size_t, const unsigned);
static size_t key_get_len(const char *);
