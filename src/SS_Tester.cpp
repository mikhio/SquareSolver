#include <stdio.h>
#include <string.h>
#include "../inc/SS_Assert.h"
#include "../inc/SS_Tester.h"
#include "../inc/ReturnCodes.h"
#include "../inc/SqEquation.h"
#include "../inc/IoTool.h"
#include "../inc/CliColors.h"

/**
 * Creates local array with tests, reads tests from tests/ss_tests.txt and adds them to array.\n
 * After runs all tests from that array and prints result.
 * @param[in] file_path path to file with tests
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode ss_run_tests(const char *file_path) {
  SS_ASSERT(file_path);
  printf("Run %s:\n", file_path);
  SS_Tests ss_tests = {};

  readTests(file_path, &ss_tests);

  SqEquation eq = {};

  int passed_tests_amount = 0;

  for (int i = 0; i < ss_tests.amount; i++) {
    if (ss_run_test(i, &eq, &ss_tests) == OK) {
      printf("Test %d is " GREEN("OK") "\n", i+1);
      passed_tests_amount++;
    } else {
      printf("Test %d is " RED("WRONG") "\n", i+1);
      printWrongTestSS(&eq, &(ss_tests.tests[i]));
    }
  }

  printf("%d of %d tests are passed\n", passed_tests_amount, ss_tests.amount);

  freeTests(&ss_tests);

  return OK;
}

/**
 * Reads coefs from ss_tests[tests_i] equation to tests_eq equation, solves it and compares them\n
 * @param[in]  test_index  index of running test in ss_tests array
 * @param[out] test_eq     pointer to current test's equationy
 * @param[in]  ss_tests    pointer to ss_tests sturcture with tests
 * @return Erorr code (if ok return ReturnCode::OK, if wrong return ReturnCode::ERR_TEST_WRONG)
 */
ReturnCode ss_run_test(int test_index, SqEquation *test_eq, SS_Tests *ss_tests) {
  SS_ASSERT(test_eq);
  SS_ASSERT(ss_tests);

  SqEquation cur_test = ss_tests->tests[test_index];

  test_eq->a = cur_test.a;
  test_eq->b = cur_test.b;
  test_eq->c = cur_test.c;

  solveEq(test_eq);


  if (test_eq->type !=  cur_test.type)
    return ERR_TEST_WRONG;
  
  switch (test_eq->type) {
    case ANY:
    case NO_ROOTS:
    case D_NEGATIVE:
      return OK;
    case LINEAR:
    case FULL_SQUARE:
      if (isEqual(test_eq->x1, cur_test.x1))
        return OK;
      return ERR_TEST_WRONG;
    case SQUARE:
      if (isEqual(test_eq->x1, cur_test.x1) && isEqual(test_eq->x2, cur_test.x2))
        return OK;
      return ERR_TEST_WRONG;
    case NONE:
      return ERR_TEST_WRONG;
    default:
      return ERR_UNKNOWN_EQ_TYPE;
  }
}

/**
 * Fill array with data from file
 * @param[in]  file_path path to file 
 * @param[out] ss_tests  pointer to sturcture with tests
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode readTests(const char *file_path, SS_Tests *ss_tests) {
  SS_ASSERT(file_path);
  SS_ASSERT(ss_tests);

  FILE *tests_file = fopen(file_path, "r");
  if (!tests_file)
    return ERR_OPEN_FILE;

  char  *read_line = NULL;
  size_t line_len  = 0;

  int line_num = 0;

  int is_started = 0;

  while (getline(&read_line, &line_len, tests_file) != EOF) {
    line_num++;

    if (strcmp(read_line, "#START\n") == 0) {
      is_started = 1;
    } else if (strcmp(read_line, "#END\n") == 0) {
      is_started = 0;
    } else if (is_started) {
      SqEquation eq = {};

      char type_str[100] = {}; 
      const int ARGS_AMOUNT = 6; 

      int args = sscanf(read_line, "%lg %lg %lg %lg %lg %s", &eq.a, &eq.b, &eq.c, &eq.x1, &eq.x2, type_str);

      if ((args == ARGS_AMOUNT) && (parseEqType(type_str, &eq) == OK)) {
        if (addTest(&eq, ss_tests) != OK)
          fprintf(stderr, "Can't add test: tests' buffer are overflowed\n");
      } else {
        read_line[strlen(read_line) - 1] = '\0';

        fprintf(stderr, 
            MAGENTA("Warning:") " Can't read test " BLACK("line %d") " in %s: '%s'\n",
            line_num, file_path, read_line
        );
      }
    }
  }

  return OK;
}

/**
 * @param[in]  eq         const pointer to test's equation that add
 * @param[out] ss_tests   pointer to structure with tests
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode addTest(const SqEquation *eq, SS_Tests *ss_tests) {
  SS_ASSERT(eq);
  SS_ASSERT(ss_tests);

  if (ss_tests->amount <= ss_tests->buf_size) {
    if (testsAllocateMore(ss_tests, TESTS_CHUNK_SIZE) != OK)
      return ERR_TESTS_ALLOCATION;
  }

  SqEquation *cur_test = &(ss_tests->tests[ss_tests->amount]);

  cur_test->a    = eq->a;
  cur_test->b    = eq->b;
  cur_test->c    = eq->c;
  cur_test->x1   = eq->x1;
  cur_test->x2   = eq->x2;
  cur_test->type = eq->type;

  ss_tests->amount++;

  return OK;
}

/**
 * @param[in] ss_tests    pointer to sturucte with tests
 * @param[in] chunck_size size of memory that will be additionally allocated
 * @return Erorr code (if ok return ReturnCode::OK)
 */ 
ReturnCode testsAllocateMore(SS_Tests *ss_tests, int chunk_size) {
  SS_ASSERT(ss_tests);
  SS_ASSERT(chunk_size >= 0);
  
  ss_tests->buf_size += chunk_size;

  if (ss_tests->tests == NULL)
    ss_tests->tests = (SqEquation *)calloc(ss_tests->buf_size, sizeof(SqEquation));
  else
     ss_tests->tests = (SqEquation *)realloc(ss_tests->tests, ss_tests->buf_size);

  return OK;
}

/**
 * Calls free() for array with tests
 * @param[in] ss_tests pointer to sturcture with tests
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode freeTests(SS_Tests *ss_tests) {
  SS_ASSERT(ss_tests);
  free(ss_tests->tests);

  return OK;
}

/**
 * Parses from source string and writes to dest equation
 * @param[in]  type_str source string with type
 * @param[out] eq       dest equation
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode parseEqType(char *type_str, SqEquation *eq) {
  SS_ASSERT(type_str);
  SS_ASSERT(eq);

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
