#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../inc/IoTool.h"
#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"
#include "../inc/CliColors.h"


/**
 * @param[in] eq pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode readEq(SqEquation *eq) {
  assert(eq);

  double a = 0, b = 0, c = 0;

  printf("Enter a b c (or q to quit): ");
  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    eq->a = a;
    eq->b = b;
    eq->c = c;

    return OK;
  } 

  if (checkQuit() == QUIT)
    return QUIT;

  clearBuffer();

  return ERR_INVALID_INPUT;
}

/**
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode clearBuffer() {
  fseek(stdin, 0, SEEK_END);

  if (ftell(stdin) <= 0)
    return OK;

  return OK;
}

/**
 * If user entered "q" or "quit", then return ReturnCode::QUIT\n
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode checkQuit() {
  char buffer[BUFF_SIZE] = {};
  fgets(buffer, BUFF_SIZE, stdin);

  if ((strcmp(buffer, "quit\n") == 0) || (strcmp(buffer, "q\n") == 0))
    return QUIT;

  return OK;
}

/**
 * @param[in] eq const pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode printEqRes(const SqEquation *eq) {
  assert(eq);

  switch (eq->type) {
    case NO_ROOTS:
      printf("Result: No roots\n");
      break;
    case ANY:
      printf("Result: Any\n");
      break;
    case LINEAR:
      printf("Result: x=%.4lg (Linear)\n", eq->x1);
      break;
    case SQUARE:
      printf("Result: x1=%.4lg x2=%.4lg\n", eq->x1, eq->x2);
      break;
    case FULL_SQUARE:
      printf("Result: x=%.4lg (Full square)\n", eq->x1);
      break;
    case D_NEGATIVE:
      printf("Result: None (D < 0)\n");
      break;
    case NONE:
      printf(MAGENTA("Warrning") ": Equation is undefined\n");
      break;
    default:
      fprintf(stderr, RED("ERORR") ": Unknown type of equation\n");
      return ERR_UNKNOWN_EQ_TYPE;
  }

  return OK;
}

/**
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode printShortHelp() {
  printf("usage: SquareSolver [-o | --once_without_attempts] [-ow | --once_with_attempts]\n"
         "                    [-l | --loop] [-t | --self_testing] [-h | --help]\n"
         "\n"
         "All flags override each other: the last one specified determines the mode\n"
         "\n"
         "Default mode: LOOP\n"
         "For more information run: SquareSolver --help \n"
  );

  return OK;
}

/**
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode printLongHelp() {
  printf("usage: SquareSolver [-o | --once_without_attempts] [-ow | --once_with_attempts]\n"
         "                    [-l | --loop] [-t | --self_testing] [-h | --help]\n"
         "\n"
         "All flags override each other: the last one specified determines the mode\n"
         "\n"
         "Default mode: LOOP\n"
         "\n"
         "About modes:\n"
         "  User modes:\n"
         "* LOOP - running with infinite loop, that can be stopped with quit command or after reaching MAX_ATTEMPTS(deault:10) invalid inputs in row\n"
         "* ONCE_WITHOUT_ATTEMPTS - running once and after quit automatically always\n"
         "* ONCE_WITH_ATTEMPTS - running also once, but with invalid input attemps like in loop\n"
         "  Automatic modes:\n"
         "* SELF_TESTING - run bunch of unit tests for equation solver\n"
  );

  return OK;
}

/**
 * @param[in] test_eq     pointer to test's equation (can't be NULL)
 * @param[in] expected_eq pointer to expected equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode printWrongTestSS(const SqEquation *test_eq, const SqEquation *expected_eq) {
  assert(test_eq != expected_eq);
  printf(
    MAGENTA("EXPECTED") ": a=%.4lg, b=%.4lg, c=%.4lg, type=%d, x1=%.4lg, x2=%.4lg\n"
    MAGENTA("GOT") ":      a=%.4lg, b=%.4lg, c=%.4lg, type=%d, x1=%.4lg, x2=%.4lg\n",
    expected_eq->a, expected_eq->b, expected_eq->c, expected_eq->type, expected_eq->x1, expected_eq->x2,
    test_eq->a, test_eq->b, test_eq->c, test_eq->type, test_eq->x1, test_eq->x2
  );

  return OK;
}
