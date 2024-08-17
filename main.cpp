#include <stdio.h>
#include "CliInterface.h"
#include "ReturnCodes.h"

int main(int argc, char **argv) {
  CliInterface ci = {LOOP, DEF_MAX_ATTEMPTS};

  ReturnCode runCode = ci_run(&ci);

  if (runCode == QUIT)
    printf("GoodBye!))))\n");
  else if (runCode != OK)
    fprintf(stderr, "ERORR: Can't run CliInterface with code %d\n", runCode);


  return 0;
}
