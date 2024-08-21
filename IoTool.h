#ifndef IO_TOOL_H
#define IO_TOOL_H

#include "SqEquation.h"
#include "ReturnCodes.h"

const int BUFF_SIZE = 20;

ReturnCode check_quit ();

ReturnCode readEq           (SqEquation *eq);
ReturnCode printEqRes       (const SqEquation *eq);
ReturnCode printWrongTestSS (const SqEquation *test_eq, const SqEquation *expected_eq);

#endif // IO_TOOL_H
