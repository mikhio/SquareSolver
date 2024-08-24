#ifndef CLI_ARGS_HANDLER_H
#define CLI_ARGS_HANDLER_H

/** @file CliArgsHandler.h */

#include "../inc/ReturnCodes.h"
#include "../inc/CliInterface.h"

ReturnCode handleProgramArgs(CliInterface *ci, int argc, char **argv); ///< Handle cli flags and args

#endif // CLI_ARGS_HANDLER_H
