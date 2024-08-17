#ifndef SQ_EQUATION_H
#define SQ_EQUATION_H

#include <math.h>

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

int checkDis   (SqEquation *eq);
int defineType (SqEquation *eq);
int readEq     (SqEquation *eq);
int calcSquare (SqEquation *eq);
int calcLinear (SqEquation *eq);
int solveEq    (SqEquation *eq);

int printEqRes (const SqEquation *eq);

#endif // SQ_EQUATION_H
