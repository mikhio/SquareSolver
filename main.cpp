#include <stdio.h>
#include "CliInterface.h"
#include "ReturnCodes.h"

int main() {
  CliInterface ci = {};

  ci.type = LOOP;
  ci.max_attempts = DEF_MAX_ATTEMPTS;

  ReturnCode runCode = ci_run(&ci);

  if (runCode == QUIT)
    printf("GoodBye!))))\n");
  else if (runCode != OK)
    fprintf(stderr, "ERORR: Can't run CliInterface with code %d\n", runCode);

  return 0;
}
