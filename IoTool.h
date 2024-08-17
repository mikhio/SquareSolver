#ifndef IO_TOOL_H
#define IO_TOOL_H

#include "SqEquation.h"

const int BUFF_SIZE = 20;

int check_quit ();
int readEq     (SqEquation *eq);
int printEqRes (const SqEquation *eq);

#endif // IO_TOOL_H
