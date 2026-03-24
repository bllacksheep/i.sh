#include "shell.h"

#ifndef TEST
int main(void) {
  init_shell();
  // shell state needs be propagated here
  while (1) {
    shell_start_repl();
  }

  return 0;
}
#endif
