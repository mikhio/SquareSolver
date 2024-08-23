#ifndef CLI_ARGS_HANDLER_H
#define CLI_ARGS_HANDLER_H

/** @file CliArgsHandler.h */

#include "ReturnCodes.h"
#include "CliInterface.h"

ReturnCode handleProgramArgs(CliInterface *ci, int argc, char **argv); ///< Handle cli flags and args

#endif // CLI_ARGS_HANDLER_H
