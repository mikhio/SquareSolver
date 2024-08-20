#include <stdio.h>
#include "CliInterface.h"
#include "ReturnCodes.h"

int main(int argc, char **argv) {
  CliInterface ci = {LOOP, DEF_MAX_ATTEMPTS};

  ReturnCode runCode = ss_ci_run(&ci);

  if (runCode == QUIT)
    printf("GoodBye!))))\n");
  else if (runCode != OK)
    fprintf(stderr, "ERORR: CliInterface crashed with code %d\n", runCode);


  return 0;
}
