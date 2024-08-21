#ifndef SS_TESTER_H
#define SS_TESTER_H

#include "SqEquation.h"

const int TESTS_AMOUNT = 7;
const SqEquation SS_TESTS[TESTS_AMOUNT] = {
  { .a = 1, .b = 2, .c =  1, .x1 = -1, .x2 = -1, .type = FULL_SQUARE },
  { .a = 0, .b = 1, .c =  1, .x1 = -1, .x2 =  0, .type = LINEAR      },
  { .a = 0, .b = 0, .c =  0, .x1 =  0, .x2 =  0, .type = ANY         },
  { .a = 0, .b = 0, .c =  1, .x1 =  0, .x2 =  0, .type = NO_ROOTS    },
  { .a = 1, .b = 2, .c =  3, .x1 =  0, .x2 =  0, .type = D_NEGATIVE  },
  { .a = 1, .b = 0, .c = -1, .x1 =  1, .x2 = -1, .type = SQUARE      },

  { .a = 1, .b = 2.99493, .c = -21.0561, .x1 = 3.32939, .x2 = -6.32432, .type = SQUARE },
};

ReturnCode ss_run_tests ();
ReturnCode ss_run_test  (int test_i, SqEquation *test_eq);

#endif // SS_TESTER_H
