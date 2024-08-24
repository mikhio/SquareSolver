#include <stdio.h>
#include "../inc/CliInterface.h"
#include "../inc/ReturnCodes.h"
#include "../inc/CliArgsHandler.h"
#include "../inc/CliColors.h"


int main(int argc, char **argv) {
  CliInterface ci = {LOOP, DEF_MAX_ATTEMPTS};

  ReturnCode handlerCode = handleProgramArgs(&ci, argc, argv);

  if (handlerCode == ERR_UNKNOWN_ARG) {
    fprintf(stderr, RED("ERROR") ": Unknown flags, run: SquareSolver --help\n");
    return 1;
  } else if (handlerCode == OK) { 
    ReturnCode runCode = ss_ci_run(&ci);

    if (runCode == QUIT)
      printf("GoodBye!))))\n");
    else if (runCode != OK)
      fprintf(stderr, RED("ERORR") ": CliInterface crashed with code %d\n", runCode);
  }

  return 0;
}
