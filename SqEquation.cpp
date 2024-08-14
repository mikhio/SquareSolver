#include <stdio.h>
#include <math.h>
#include "SqEquation.h"

void checkDis(SqEquation *eq) {
  if (eq->type == SQUARE) {
    eq->D = eq->b*eq->b - 4*eq->a*eq->c;
    
    if (eq->D < 0) 
      eq->type = D_NEGATIVE;
    if (eq->D == 0)
      eq->type = FULL_SQUARE;
  }
}

void defineType(SqEquation *eq) {
  eq->type = NONE;

  if ((eq->a == 0) && (eq->b == 0))
    eq->type = ANY;
  if ((eq->a == 0) && (eq->b != 0))
    eq->type = LINEAR;
  if (eq->a != 0) {
    eq->type = SQUARE;
    checkDis(eq);
  }
}

bool readEq(SqEquation *eq) {
  double a = 0, b = 0, c = 0;

  printf("Enter a b c: ");
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
  double D_sqrt = sqrt(eq->D);

  eq->x1 = (-eq->b + D_sqrt) / eq->a;
  eq->x2 = (-eq->b - D_sqrt) / eq->a;
}

void solveEq(SqEquation *eq) {
  if (eq->type == LINEAR)
    eq->x1 = eq->x2 = -eq->c/eq->b;
  else if ((eq->type == SQUARE) || (eq->type == FULL_SQUARE)) {
    calcRoots(eq);
  }
}

void printEqRes(SqEquation *eq) {
  if (eq->type == NONE)
    printf("Error: Unknown type\n");
  else if (eq->type == ANY)
    printf("Result: Any\n");
  else if (eq->type == LINEAR)
    printf("Result: x=%lg (Linear)\n", eq->x1);
  else if (eq->type == SQUARE)
    printf("Result: x1=%lg x2=%lg\n", eq->x1, eq->x2);
  else if (eq->type == FULL_SQUARE)
    printf("Result: x=%lg (Full square)\n", eq->x1);
  else if (eq->type == D_NEGATIVE)
    printf("Result: None (D < 0)\n");
}
