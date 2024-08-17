#include <stdio.h>
#include "CliInterface.h"

int main() {
  CliInterface ci = {};

  ci.type = LOOP;
  ci.max_attempts = DEF_MAX_ATTEMPTS;

  if (ci_run(&ci) == -1)
    fprintf(stderr, "ERORR: Can't run CliInterface");

  return 0;
}
