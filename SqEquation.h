#ifndef SQ_EQUATION_H
#define SQ_EQUATION_H

#include <math.h>

#define EPSILON 0.00000001
#define IS_EQUAL(a, b) (fabs(a - b) < EPSILON)

#define CHECK_NULL(ptr, func_name) if (ptr == NULL) { printf("\nERROR: got NULL arg in %s\n", func_name); exit(1); }

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

void checkDis(SqEquation *eq);
void defineType(SqEquation *eq);
bool readEq(SqEquation *eq);
void calcRoots(SqEquation *eq);
void solveEq(SqEquation *eq);
void printEqRes(SqEquation *eq);

#endif
