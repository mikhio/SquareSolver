#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "SqEquation.h"

const int BUFF_SIZE = 20;

int check_quit ();
int readEq     (SqEquation *eq);
int printEqRes (const SqEquation *eq);

#endif // CLI_INTERFACE_H
