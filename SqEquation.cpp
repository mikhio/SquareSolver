#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "SqEquation.h"
#include "ReturnCodes.h"

ReturnCode calcDiscriminant(SqEquation *eq) {
  assert(eq);

  if (eq->type == SQUARE) {
    eq->D = eq->b*eq->b - 4*eq->a*eq->c;
    
    if (eq->D < 0) 
      eq->type = D_NEGATIVE;
    else if (IS_EQUAL(eq->D, 0))
      eq->type = FULL_SQUARE;
    else 
      return ERR_D_POSITIVE;
  } else {
    return ERR_UNKNOWN_EQ_TYPE;
  }

  return OK;
}

ReturnCode defineType(SqEquation *eq) {
  assert(eq);

  eq->type = NONE;

  if (IS_EQUAL(eq->a, 0) && IS_EQUAL(eq->b, 0)) {
    if (IS_EQUAL(eq->c, 0))
      eq->type = ANY;
    else
      eq->type = NO_ROOTS;
  } else if (IS_EQUAL(eq->a, 0) && !IS_EQUAL(eq->b, 0)) {
    eq->type = LINEAR;
  } else if (!IS_EQUAL(eq->a, 0)) {
    eq->type = SQUARE;
    calcDiscriminant(eq);
  }

  return OK;
}


ReturnCode calcSquare(SqEquation *eq) {
  assert(eq);

  double D_sqrt = sqrt(eq->D);

  eq->x1 = (-eq->b + D_sqrt) / (2*eq->a);
  eq->x2 = (-eq->b - D_sqrt) / (2*eq->a);

  return OK;
}

ReturnCode calcLinear(SqEquation *eq) {
  assert(eq);

  eq->x1 = eq->x2 = -eq->c/eq->b;

  return OK;
}

ReturnCode solveEq(SqEquation *eq) {
  assert(eq);

  defineType(eq);

  if (eq->type == LINEAR)
    calcLinear(eq);
  else if ((eq->type == SQUARE) || (eq->type == FULL_SQUARE))
    calcSquare(eq);
  else
    return ERR_UNKNOWN_EQ_TYPE;

  return OK;
}

