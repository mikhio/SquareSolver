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

