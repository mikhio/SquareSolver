#include <stdio.h>
#include <assert.h>
#include "CliInterface.h"
#include "IoTool.h"
#include "SqEquation.h"

int ci_run(const CliInterface *ci) {
  assert(ci != NULL);

  SqEquation eq = {};

  switch (ci->type) {
    case LOOP:
      run_loop(ci, &eq);
      break;
    case ONCE_WITH_ATTEMPTS:
      run_once(ci, &eq, 1);
      break;
    case ONCE_WITHOUT_ATTEMPTS:
      run_once(ci, &eq, 0);
      break;
    default:
      fprintf(stderr, "ERROR: Uknonw type of CliInterface");
      return -1;
  }

  return 0;
}

int run_loop(const CliInterface *ci, SqEquation *eq) {
  while (run_once(ci, eq, 1) != -1) {}

  return 0;
}

int run_once(const CliInterface *ci, SqEquation *eq, int with_attempts) {
  assert(ci != NULL);

  int cur_attempt = 0;

  while (cur_attempt < ci->max_attempts) {
    if (readEq(eq)) {
      solveEq(eq);
      printEqRes(eq);

      return 0;
    }

    if (with_attempts)
      fprintf(stderr, "ERORR: invalid input data, ATTEMPT %d from %d\n", ++cur_attempt, ci->max_attempts);
    else
      return -1;
  }

  return -1;
}

