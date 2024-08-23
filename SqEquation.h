#ifndef SQ_EQUATION_H
#define SQ_EQUATION_H

/** @file SqEquation.h */

#include <math.h>
#include "ReturnCodes.h"

const double EPSILON = 1e-4; ///< Constant for max difference between "equal" doubles

/// @enum EqType
/// Equation type enum
enum EqType {
  NONE        = 0, ///< Undefined type
  ANY         = 1, ///< Roots of equation can be any
  LINEAR      = 2, ///< Linear equation
  SQUARE      = 3, ///< Square equation
  FULL_SQUARE = 4, ///< Full square: x1 = x2
  D_NEGATIVE  = 5, ///< Discrimenant less 0
  NO_ROOTS    = 6  ///< No roots
};

/// @struct SqEquation
/// Structure with info about equation.
/**
 * Represents equation(ax^2 + bx + c = 0), it's solution and type.\n
 * If equation has no roots, x1 and x2 contains 0.\n
 * If equation is linear, x1 contains root, x2 contains 0.\n
 * If equation is quadratic, x1 and x2 contain roots (x1 < x2).
 */
struct SqEquation {
  double a;    ///< Quadratic coef
  double b;    ///< Linear coef
  double c;    ///< Constant
  double D;    ///< Discriminant
  double x1;   ///< First root
  double x2;   ///< Second root
  EqType type; ///< Type
};

int isEqual(double a, double b); ///< Compare doubles

ReturnCode calcDiscriminant (SqEquation *eq); ///< Calculates discrimminant
ReturnCode defineType       (SqEquation *eq); ///< Defines equation type
ReturnCode calcSquare       (SqEquation *eq); ///< Calculates roots of square equation
ReturnCode calcLinear       (SqEquation *eq); ///< Calculates roots of linear equation
ReturnCode solveEq          (SqEquation *eq); ///< Solves equation

#endif // SQ_EQUATION_H
