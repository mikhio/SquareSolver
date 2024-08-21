#ifndef CLI_ARGS_HANDLER_H
#define CLI_ARGS_HANDLER_H

#include "ReturnCodes.h"
#include "CliInterface.h"

ReturnCode handleProgramArgs(CliInterface *ci, int argc, char **argv);

#endif // CLI_ARGS_HANDLER_H
