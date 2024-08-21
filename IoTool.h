#ifndef IO_TOOL_H
#define IO_TOOL_H

#include "SqEquation.h"
#include "ReturnCodes.h"

const int BUFF_SIZE = 20;

ReturnCode check_quit ();
ReturnCode readEq     (SqEquation *eq);
ReturnCode printEqRes (const SqEquation *eq);
ReturnCode printHelp  ();

#endif // IO_TOOL_H
