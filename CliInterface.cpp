#include <stdio.h>
#include <assert.h>
#include "CliInterface.h"
#include "IoTool.h"
#include "SqEquation.h"
#include "ReturnCodes.h"

ReturnCode ss_ci_run(const CliInterface *ci) {
  assert(ci);

  SqEquation eq = {};

  switch (ci->type) {
    case LOOP:
      return ss_run_loop(ci, &eq);
    case ONCE_WITH_ATTEMPTS:
      return ss_run_once(ci, &eq, 1);
    case ONCE_WITHOUT_ATTEMPTS:
      return ss_run_once(ci, &eq, 0);
    default:
      fprintf(stderr, "ERROR: Uknonw type of CliInterface");
      return ERR_UNKNOWN_CI_TYPE;
  }
}

ReturnCode ss_run_loop(const CliInterface *ci, SqEquation *eq) {
  ReturnCode code = OK;

  do {
    code = ss_run_once(ci, eq, 1);
  } while (code == OK);

  return code;
}

ReturnCode ss_run_once(const CliInterface *ci, SqEquation *eq, int with_attempts) {
  assert(ci);

  int cur_attempt = 0;

  while (cur_attempt < ci->max_attempts) {
    ReturnCode readCode = readEq(eq);

    if (readCode == OK) {
      solveEq(eq);
      printEqRes(eq);

      return OK;
    } else if (readCode == QUIT) {
      return QUIT;
    }

    if (with_attempts)
      fprintf(stderr, "ERORR: invalid input data, ATTEMPT %d from %d\n", ++cur_attempt, ci->max_attempts);
    else
      return ERR_INVALID_INPUT;
  }

  return ERR_INVALID_INPUT;
}

