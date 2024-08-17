#include <stdio.h>
#include <assert.h>
#include "CliInterface.h"
#include "IoTool.h"
#include "SqEquation.h"
#include "ReturnCodes.h"

ReturnCode ci_run(const CliInterface *ci) {
  assert(ci != NULL);

  SqEquation eq = {};

  switch (ci->type) {
    case LOOP:
      return run_loop(ci, &eq);
    case ONCE_WITH_ATTEMPTS:
      return run_once(ci, &eq, 1);
    case ONCE_WITHOUT_ATTEMPTS:
      return run_once(ci, &eq, 0);
    default:
      fprintf(stderr, "ERROR: Uknonw type of CliInterface");
      return UNKNOWN_CI_TYPE;
  }
}

ReturnCode run_loop(const CliInterface *ci, SqEquation *eq) {
  ReturnCode code = OK;
  while ((code = run_once(ci, eq, 1)) == OK) {}

  return code;
}

ReturnCode run_once(const CliInterface *ci, SqEquation *eq, int with_attempts) {
  assert(ci != NULL);

  int cur_attempt = 0;

  while (cur_attempt < ci->max_attempts) {
    ReturnCode readCode = readEq(eq);

    if (readCode == OK) {
      solveEq(eq);
      printEqRes(eq);

      return OK;
    } else if (readCode == QUIT)
      return QUIT;

    if (with_attempts)
      fprintf(stderr, "ERORR: invalid input data, ATTEMPT %d from %d\n", ++cur_attempt, ci->max_attempts);
    else
      return INVALID_INPUT;
  }

  return INVALID_INPUT;
}

