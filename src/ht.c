#include "ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ht_item {
  char *key;
  char *value;
} ht_item_t;

typedef ht_item_t ht_table_t[HT_MAX];
static ht_table_t *ht_table = NULL;

// returning first element of table due to opaque items
static ht_item_t *ht_init(void);
static int ht_set_key(ht_item_t *, char *);
static int ht_set_val(ht_item_t *, char *);
static char *lookup_val(const ht_item_t *, const char *, const size_t);
static unsigned get_hash(const char *, const size_t, const unsigned);

static unsigned get_hash(const char *k, const size_t kl, const unsigned at) {
  return 0;
}

// take table, key and key length and return value
static char *lookup_val(const ht_item_t *tbl, const char *item_key,
                        const size_t item_key_len) {
  unsigned attempt = 0;
  unsigned try = get_hash(item_key, item_key_len, attempt);

  const ht_item_t *item = &tbl[try];

  while (1) {
    if (attempt == HT_MAX)
      break;
    if (strcmp(item->key, item_key) == 0)
      return item->value;
    attempt++;
    // retry step by 1
    try = get_hash(item_key, item_key_len, attempt);
    item = &tbl[try];
  }
  return NULL;
}

// initialize a table if not already initialized and return pointer to first
// elem
static ht_item_t *ht_init() {
  if (ht_table != NULL) {
    return (ht_item_t *)ht_table;
  }
  ht_table = calloc(1, sizeof(ht_table_t));
  if (ht_table == NULL) {
    fprintf(stderr, "i.sh: failed to initialize ht table, code: %d", ERRHTINIT);
    exit(ERRHTINIT);
  }
  return (ht_item_t *)ht_table;
}

ht_item_t *ht_get_table() {
  if (ht_table == NULL) {
    return (ht_item_t *)ht_init();
  }
  return (ht_item_t *)ht_table;
}

const char *ht_get_var(const char *item_k) {
  ht_item_t *table = ht_get_table();
  if (table == NULL) {
    fprintf(stderr, "i.sh: failed to initialize ht table, code: %d", ERRHTGET);
    exit(ERRHTGET);
  }
  const size_t max_len = 20;
  const size_t item_kl = strnlen(item_k, max_len);

  char *val = lookup_val(table, item_k, item_kl);
  if (val == NULL) {
    return NULL;
  }
  return val;
}

static int ht_set_val(ht_item_t *item, char *v) {
  if (item == NULL || v == NULL) {
    fprintf(stderr, "i.sh: failed to set value %s, code: %d", v, ERRHTINS);
    return EXIT_FAILURE;
  }

  // if not null, and the same value, overwrite, else .... something else
  item->value = strdup(v);
  if (item->value == NULL) {
    fprintf(stderr, "i.sh: failed to initialize value %s, code: %d", v,
            ERRHTINS);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static int ht_set_key(ht_item_t *item, char *k) {
  if (item == NULL || k == NULL) {
    fprintf(stderr, "i.sh: failed to set key %s, code: %d", k, ERRHTINS);
    return EXIT_FAILURE;
  }

  // if not null, and the same value, overwrite, else .... something else
  item->key = strdup(k);
  if (item->key == NULL) {
    fprintf(stderr, "i.sh: failed to initialize key %s, code: %d", k, ERRHTINS);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int ht_put_var(const char *item_k, const char *item_v) {
  ht_item_t *table = ht_get_table();
  if (table == NULL) {
    fprintf(stderr, "i.sh: failed to initialize ht table, code: %d", ERRHTINS);
    exit(ERRHTINS);
  }

  if (ht_set_key(ht_item, k) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  if (ht_set_val(ht_item, v) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int ht_del_var(char *k) {
  ht_item_t *table = ht_get_table();
  if (table == NULL) {
    fprintf(stderr, "i.sh: failed to initialize ht table, code: %d", ERRHTDEL);
    exit(ERRHTDEL);
  }

  return 0;
}
