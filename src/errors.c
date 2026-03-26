#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

int err_exit(char *msg, unsigned err) {
  fprintf(stderr, "i.sh: %s: code %d\n", msg, err);
  exit(err);
}
