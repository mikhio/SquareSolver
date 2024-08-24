#include <stdio.h>
#include "../inc/SS_Assert.h"
#include "../inc/CliInterface.h"
#include "../inc/IoTool.h"
#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"
#include "../inc/SS_Tester.h"
#include "../inc/CliColors.h"


/**
 * Calls ss_run_loop() or ss_run_once() depends on CliInterface mode
 * @param[in] ci const pointer to interface (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode ss_ci_run(const CliInterface *ci) {
  SS_ASSERT(ci);

  switch (ci->type) {
    case LOOP:
      return ss_run_loop(ci);
    case ONCE_WITH_ATTEMPTS:
      return ss_run_once(ci, 1);
    case ONCE_WITHOUT_ATTEMPTS:
      return ss_run_once(ci, 0);
    case SELF_TESTING:
      return ss_run_tests();
    default:
      fprintf(stderr, RED("ERROR") ": Uknonw type of CliInterface");
      return ERR_UNKNOWN_CI_TYPE;
  }
}

/**
 * Runs loop with calling run_once() untill quiting
 * @param[in]  ci const pointer to interface (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode ss_run_loop(const CliInterface *ci) {
  ReturnCode code = OK;

  do {
    code = ss_run_once(ci, 1);
  } while (code == OK);

  return code;
}

/**
 * Reads and solves equation once
 * @param[in]  ci const pointer to interface (can't be NULL)
 * @param[in]  with_attempts flag that defines mode: 1 - ONCE_WITH_ATTEMPTS, 0 - ONCE_WTIOUT_ATTEMPTS
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode ss_run_once(const CliInterface *ci, int with_attempts) {
  SS_ASSERT(ci);

  int cur_attempt = 0;

  SqEquation eq = {};

  while (cur_attempt < ci->max_attempts) {
    ReturnCode readCode = readEq(&eq);

    if (readCode == OK) {
      solveEq(&eq);
      printEqRes(&eq);

      return OK;
    } else if (readCode == QUIT) {
      return QUIT;
    }

    if (with_attempts)
      fprintf(stderr, RED("ERORR") ": invalid input data, ATTEMPT %d from %d\n", ++cur_attempt, ci->max_attempts);
    else
      return ERR_INVALID_INPUT;
  }

  return ERR_INVALID_INPUT;
}

