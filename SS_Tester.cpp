#include <stdio.h>
#include "SS_Tester.h"
#include "ReturnCodes.h"
#include "SqEquation.h"
#include "IoTool.h"

ReturnCode ss_run_tests() {
  printf("Run tests:\n");

  SqEquation test_eq = {};

  for (int i = 0; i < TESTS_AMOUNT; i++) {
    if (ss_run_test(i, &test_eq) == OK) {
      printf("Test %d is OK\n", i+1);
    } else {
      printf("Test %d is WRONG\n", i+1);
      printWrongTestSS(&test_eq, &SS_TESTS[i]);

      return ERR_TEST_WRONG; 
    }
  }

  return OK;
}

ReturnCode ss_run_test(int test_i, SqEquation *test_eq) {
  test_eq->a = SS_TESTS[test_i].a;
  test_eq->b = SS_TESTS[test_i].b;
  test_eq->c = SS_TESTS[test_i].c;

  solveEq(test_eq);

  if (test_eq->type !=  SS_TESTS[test_i].type)
    return ERR_TEST_WRONG;
  
  switch (test_eq->type) {
    case ANY:
    case NO_ROOTS:
    case D_NEGATIVE:
      return OK;
    case LINEAR:
    case FULL_SQUARE:
      if (IS_EQUAL(test_eq->x1, SS_TESTS[test_i].x1))
        return OK;
      return ERR_TEST_WRONG;
    case SQUARE:
      if (IS_EQUAL(test_eq->x1, SS_TESTS[test_i].x1) && IS_EQUAL(test_eq->x2, SS_TESTS[test_i].x2))
        return OK;
      return ERR_TEST_WRONG;
    case NONE:
      return ERR_TEST_WRONG;
    default:
      return ERR_UNKNOWN_EQ_TYPE;
  }
}

