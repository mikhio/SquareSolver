#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "SqEquation.h"

int checkDis(SqEquation *eq) {
  assert(eq != NULL);

  if (eq->type == SQUARE) {
    eq->D = eq->b*eq->b - 4*eq->a*eq->c;
    
    if (eq->D < 0) 
      eq->type = D_NEGATIVE;
    else if (IS_EQUAL(eq->D, 0))
      eq->type = FULL_SQUARE;
  }

  return 0;
}

int defineType(SqEquation *eq) {
  assert(eq != NULL);

  eq->type = NONE;

  if (IS_EQUAL(eq->a, 0) && IS_EQUAL(eq->b, 0))
    eq->type = ANY;
  if (IS_EQUAL(eq->a, 0) && !IS_EQUAL(eq->b, 0))
    eq->type = LINEAR;
  if (!IS_EQUAL(eq->a, 0)) {
    eq->type = SQUARE;
    checkDis(eq);
  }

  return 0;
}

int readEq(SqEquation *eq) {
  assert(eq != NULL);

  double a = 0, b = 0, c = 0;

  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    eq->a = a;
    eq->b = b;
    eq->c = c;

    defineType(eq);

    return 1;
  }

  return 0;
}

int calcSquare(SqEquation *eq) {
  assert(eq != NULL);

  double D_sqrt = sqrt(eq->D);

  eq->x1 = (-eq->b + D_sqrt) / (2*eq->a);
  eq->x2 = (-eq->b - D_sqrt) / (2*eq->a);

  return 0;
}

int calcLinear(SqEquation *eq) {
  assert(eq != NULL);

  eq->x1 = eq->x2 = -eq->c/eq->b;
  return 0;
}

int solveEq(SqEquation *eq) {
  assert(eq != NULL);

  if (eq->type == LINEAR)
    calcLinear(eq);
  else if ((eq->type == SQUARE) || (eq->type == FULL_SQUARE)) {
    calcSquare(eq);
  }

  return 0;
}

int printEqRes(const SqEquation *eq) {
  assert(eq != NULL);

  switch (eq->type) {
    case NONE:
      printf("Result: NONE type\n");
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
    default:
      fprintf(stderr, "ERORR: Unknown type of equation");
  }

  return 0;
}
