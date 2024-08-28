#include <stdio.h>
#include <math.h>
#include "../inc/SS_Assert.h"
#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"

/**
 * Needs eq->type to be equal SQUARE\n
 * Writes D = b^2 - 4ac to eq->D\n
 * If D < 0, then changes eq->type to D_NEGATIVE\n
 * If D == 0, then changes eq->type to FULL_SQUARE\n
 * If D > 0, then eq->type remains SQUARE
 * @param[in, out] eq pointer to equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode calcDiscriminant(SqEquation *eq) {
  SS_ASSERT(eq);

  if (eq->type == SQUARE) {
    eq->D = eq->b*eq->b - 4*eq->a*eq->c;
    
    if (eq->D < 0) 
      eq->type = D_NEGATIVE;
    else if (isEqual(eq->D, 0))
      eq->type = FULL_SQUARE;
    else 
      return ERR_D_POSITIVE;
  } else {
    return ERR_UNKNOWN_EQ_TYPE;
  }

  return OK;
}

/**
 * Changes type depends on coefs and amount of roots\n
 * @param eq pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode defineType(SqEquation *eq) {
  SS_ASSERT(eq);

  eq->type = NONE;

  if (!isfinite(eq->a) || !isfinite(eq->b) || !isfinite(eq->c)) {
    eq->type = NO_ROOTS;
  } else if (isEqual(eq->a, 0) && isEqual(eq->b, 0)) {
    if (isEqual(eq->c, 0))
      eq->type = ANY;
    else
      eq->type = NO_ROOTS;
  } else if (isEqual(eq->a, 0) && !isEqual(eq->b, 0)) {
    eq->type = LINEAR;
  } else if (!isEqual(eq->a, 0)) {
    eq->type = SQUARE;
    calcDiscriminant(eq);
  }

  return OK;
}

/**
 * Needs eq->type SQUARE or FULL_SQUARE\n
 * @param eq pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode calcSquare(SqEquation *eq) {
  SS_ASSERT(eq);

  if (eq->type == SQUARE || eq->type == FULL_SQUARE) {
    double D_sqrt = sqrt(eq->D);
    
    eq->x1 = (-eq->b + D_sqrt) / (2*eq->a);
    eq->x2 = (-eq->b - D_sqrt) / (2*eq->a);
  } else {
    return ERR_UNKNOWN_EQ_TYPE;
  }

  return OK;
}

/**
 * Needs eq->type LINEAR
 * @param eq pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode calcLinear(SqEquation *eq) {
  SS_ASSERT(eq);
  
  if (eq->type == LINEAR)
    eq->x1 = eq->x2 = -eq->c/eq->b;
  else
    return ERR_UNKNOWN_EQ_TYPE;

  return OK;
}

/**
 * Firstly, calls defineType() to define type\n
 * Secondly, depends on type calls calcSquare() or calcLinear()
 * @param eq pointer equation (can't be NULL)
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode solveEq(SqEquation *eq) {
  SS_ASSERT(eq);

  defineType(eq);

  if (eq->type == LINEAR)
    calcLinear(eq);
  else if ((eq->type == SQUARE) || (eq->type == FULL_SQUARE))
    calcSquare(eq);
  else
    return ERR_UNKNOWN_EQ_TYPE;

  return OK;
}

/**
 * @param[in] a first double
 * @param[in] b second double
 * @return 1 - equal, 0 - unequal
 */
int isEqual(double a, double b) {
  if ((isnan(a) && isnan(b)) || (isinf(a) && isinf(b)))
    return 1;
  if (!isfinite(a) || !isfinite(b))
    return 0;
  
  if (fabs(a - b) < EPSILON)
    return 1;

  return 0;
}
