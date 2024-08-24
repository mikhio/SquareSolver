#ifndef IO_TOOL_H
#define IO_TOOL_H

/** @file IoTool.h */

#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"


ReturnCode checkQuit   (); ///< Checks entering quit command
ReturnCode clearBuffer (); ///< Clear stdin buffer

ReturnCode readEq     (SqEquation *eq);       ///< Reads equation
ReturnCode printEqRes (const SqEquation *eq); ///< Prints equation result

ReturnCode printWrongTestSS (const SqEquation *test_eq, const SqEquation *expected_eq); /// Prits wrong test info

ReturnCode printShortHelp (); ///< Prints important help info
ReturnCode printLongHelp  (); ///< Prints detailed help info

#endif // IO_TOOL_H
