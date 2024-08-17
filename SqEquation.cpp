#include <stdio.h>
#include <math.h>
#include "SqEquation.h"

#define CHECK_NULL(ptr, func_name) if (ptr == NULL) { printf("\nERROR: got NULL arg in %s\n", func_name); exit(1); }

void checkDis(SqEquation *eq) {
  CHECK_NULL(eq, "checkDis");

  if (eq->type == SQUARE) {
    eq->D = eq->b*eq->b - 4*eq->a*eq->c;
    
    if (eq->D < 0) 
      eq->type = D_NEGATIVE;
    else if (IS_EQUAL(eq->D, 0))
      eq->type = FULL_SQUARE;
  }
}

void defineType(SqEquation *eq) {
  CHECK_NULL(eq, "defineType");

  eq->type = NONE;

  if (IS_EQUAL(eq->a, 0) && IS_EQUAL(eq->b, 0))
    eq->type = ANY;
  if (IS_EQUAL(eq->a, 0) && !IS_EQUAL(eq->b, 0))
    eq->type = LINEAR;
  if (!IS_EQUAL(eq->a, 0)) {
    eq->type = SQUARE;
    checkDis(eq);
  }
}

bool readEq(SqEquation *eq) {
  CHECK_NULL(eq, "readEq")
  double a = 0, b = 0, c = 0;

  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    eq->a = a;
    eq->b = b;
    eq->c = c;

    defineType(eq);

    return true;
  }
  return false;
}

void calcRoots(SqEquation *eq) {
  CHECK_NULL(eq, "calcRoots");

  double D_sqrt = sqrt(eq->D);

  eq->x1 = (-eq->b + D_sqrt) / (2*eq->a);
  eq->x2 = (-eq->b - D_sqrt) / (2*eq->a);
}

void solveEq(SqEquation *eq) {
  CHECK_NULL(eq, "solveEq");

  if (eq->type == LINEAR)
    eq->x1 = eq->x2 = -eq->c/eq->b;
  else if ((eq->type == SQUARE) || (eq->type == FULL_SQUARE)) {
    calcRoots(eq);
  }
}

void printEqRes(SqEquation *eq) {
  CHECK_NULL(eq, "printEqRes");

  switch (eq->type) {
    case NONE:
      printf("Error: Unknown type\n");
      break;
    case ANY:
      printf("Result: Any\n");
      break;
    case LINEAR:
      printf("Result: x=%lg (Linear)\n", eq->x1);
      break;
    case SQUARE:
      printf("Result: x1=%lg x2=%lg\n", eq->x1, eq->x2);
      break;
    case FULL_SQUARE:
      printf("Result: x=%lg (Full square)\n", eq->x1);
      break;
    case D_NEGATIVE:
      printf("Result: None (D < 0)\n");
      break;
  }
}
