#ifndef _HT_H
#define _HT_H 1

#define HT_MAX 1000
typedef struct ht_item ht_item_t;

// returns a table, but due to how c is handling ht_item as an opaque type
// I can't forward declare a table here and return the table
// so return pointer to first element of the table, insane and cool
ht_item_t *ht_get_table(void);
const char *ht_get_var(const char *);
int ht_put_var(const char *, const char *);
int ht_del_var(const char *);

enum ht_errors {
  ERRHTINIT = 100,
  ERRHTGET,
  ERRHTINS,
  ERRHTDEL,
};

#endif
