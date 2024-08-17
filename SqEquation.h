#ifndef SQ_EQUATION_H
#define SQ_EQUATION_H

#include <math.h>
#include "ReturnCodes.h"

const double EPSILON = 1e-8;
#define IS_EQUAL(a, b) (fabs(a - b) < EPSILON)



enum EqType {
  NONE        = 0,
  ANY         = 1,
  LINEAR      = 2,
  SQUARE      = 3,
  FULL_SQUARE = 4,
  D_NEGATIVE  = 5
};

struct SqEquation {
  double a, b, c;
  double D;
  double x1, x2;
  EqType type;
};

ReturnCode checkDis   (SqEquation *eq);
ReturnCode defineType (SqEquation *eq);
ReturnCode calcSquare (SqEquation *eq);
ReturnCode calcLinear (SqEquation *eq);
ReturnCode solveEq    (SqEquation *eq);


#endif // SQ_EQUATION_H
