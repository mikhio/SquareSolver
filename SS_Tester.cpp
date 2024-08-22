#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SS_Tester.h"
#include "ReturnCodes.h"
#include "SqEquation.h"
#include "IoTool.h"
#include "CliColors.h"

ReturnCode ss_run_tests() {
  printf("Run tests/ss_test.txt:\n");
  SqEquation ss_tests[TESTS_AMOUNT] = {};

  readTests("tests/ss_tests.txt", ss_tests);

  SqEquation test_eq = {};

  for (int i = 0; i < TESTS_AMOUNT; i++) {
    if (ss_run_test(i, &test_eq, ss_tests) == OK) {
      printf("Test %d is " GREEN("OK") "\n", i+1);
    } else {
      printf("Test %d is " RED("WRONG") "\n", i+1);
      printWrongTestSS(&test_eq, &ss_tests[i]);

      return ERR_TEST_WRONG; 
    }
  }

  return OK;
}

ReturnCode ss_run_test(int test_i, SqEquation *test_eq, SqEquation ss_tests[TESTS_AMOUNT]) {
  assert(test_eq);

  test_eq->a = ss_tests[test_i].a;
  test_eq->b = ss_tests[test_i].b;
  test_eq->c = ss_tests[test_i].c;

  solveEq(test_eq);

  if (test_eq->type !=  ss_tests[test_i].type)
    return ERR_TEST_WRONG;
  
  switch (test_eq->type) {
    case ANY:
    case NO_ROOTS:
    case D_NEGATIVE:
      return OK;
    case LINEAR:
    case FULL_SQUARE:
      if (IS_EQUAL(test_eq->x1, ss_tests[test_i].x1))
        return OK;
      return ERR_TEST_WRONG;
    case SQUARE:
      if (IS_EQUAL(test_eq->x1, ss_tests[test_i].x1) && IS_EQUAL(test_eq->x2, ss_tests[test_i].x2))
        return OK;
      return ERR_TEST_WRONG;
    case NONE:
      return ERR_TEST_WRONG;
    default:
      return ERR_UNKNOWN_EQ_TYPE;
  }
}

ReturnCode readTests(const char *file_path, SqEquation eq_tests[TESTS_AMOUNT]) {
  assert(file_path);
  assert(eq_tests);
  assert(TESTS_AMOUNT > 0);

  FILE *tests_file = fopen(file_path, "r");
  if (!tests_file)
    return ERR_OPEN_FILE;

  char  *read_line = NULL;
  size_t line_len  = 0;

  int is_started = 0;
  int test_index = 0;

  while (getline(&read_line, &line_len, tests_file) != -1) {
    if (strcmp(read_line, "#START\n") == 0) {
      is_started = 1;
    } else if (strcmp(read_line, "#END\n") == 0) {
      is_started = 0;
    } else if (is_started) {
      SqEquation eq = {};
      char type_str[100]; 
      
      int args = sscanf(read_line, "%lg %lg %lg %lg %lg %s", &eq.a, &eq.b, &eq.c, &eq.x1, &eq.x2, type_str);

      if ((args == 6) && (parseEqType(type_str, &eq) == OK)) {
        if (addTest(&eq, eq_tests, test_index) == OK)
          test_index++;
        else
          fprintf(stderr, "Can't add test: tests' buffer are overflowed\n");
      } else {
        fprintf(stderr, 
            MAGENTA("Warning:") " Can't read test line in %s: '%s'",
            file_path, read_line
        );
      }
    }
  }

  return OK;
}

ReturnCode addTest(const SqEquation *eq, SqEquation eq_tests[TESTS_AMOUNT], int test_index) {
  assert(eq);
  assert(eq_tests);
  assert(TESTS_AMOUNT > 0);
  assert(test_index >= 0);

  if (test_index >= TESTS_AMOUNT) 
    return ERR_BUF_OVERFLOW;

  eq_tests[test_index].a    = eq->a;
  eq_tests[test_index].b    = eq->b;
  eq_tests[test_index].c    = eq->c;
  eq_tests[test_index].x1   = eq->x1;
  eq_tests[test_index].x2   = eq->x2;
  eq_tests[test_index].type = eq->type;

  return OK;
}

ReturnCode parseEqType(char *type_str, SqEquation *eq) {
  assert(type_str);
  assert(eq);

  if (strcmp(type_str, "SQ") == 0)
    eq->type = SQUARE;
  else if (strcmp(type_str, "FS") == 0)
    eq->type = FULL_SQUARE;
  else if (strcmp(type_str, "NR") == 0)
    eq->type = NO_ROOTS;
  else if (strcmp(type_str, "DN") == 0)
    eq->type = D_NEGATIVE;
  else if (strcmp(type_str, "A") == 0)
    eq->type = ANY;
  else if (strcmp(type_str, "L") == 0)
    eq->type = LINEAR;
  else
    return ERR_UNKNOWN_EQ_TYPE;

  return OK;
}
