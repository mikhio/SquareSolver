#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "IoTool.h"
#include "SqEquation.h"
#include "ReturnCodes.h"

ReturnCode check_quit() {
  char buffer[BUFF_SIZE] = {};
  fgets(buffer, BUFF_SIZE, stdin);

  if ((strcmp(buffer, "quit\n") == 0) || (strcmp(buffer, "q\n") == 0))
    return QUIT;

  return OK;
}

ReturnCode readEq(SqEquation *eq) {
  assert(eq);

  double a = 0, b = 0, c = 0;

  printf("Enter a b c (or q to quit: ");
  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    eq->a = a;
    eq->b = b;
    eq->c = c;

    defineType(eq);

    return OK;
  } 

  if (check_quit() == QUIT)
    return QUIT;

  fflush(stdin);

  return ERR_INVALID_INPUT;
}

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
      printf("Warrning: Equation is undefined");
      break;
    default:
      fprintf(stderr, "ERORR: Unknown type of equation");
      return ERR_UNKNOWN_EQ_TYPE;
  }

  return OK;
}
