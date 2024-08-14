#ifndef SQ_EQUATION_H
#define SQ_EQUATION_H

enum EqType {
  NONE,
  ANY,
  LINEAR,
  SQUARE,
  FULL_SQUARE,
  D_NEGATIVE
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
