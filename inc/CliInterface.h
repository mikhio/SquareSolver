#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

/** @file CliInterface.h */ 

#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"

const int DEF_MAX_ATTEMPTS = 10; ///< Default max attempts of input coefs

/** @enum CIType
 * Defines mode of usage cli and inclunces to running function
 */
enum CIType {
  LOOP                  = 0, ///< Loop mode
  ONCE_WITH_ATTEMPTS    = 1, ///< Once with attempts mode
  ONCE_WITHOUT_ATTEMPTS = 2, ///< Once without attempts mode
  SELF_TESTING          = 3  ///< Self testing mode
};

/** @struct CliInterface
 * Defines settings of cli running
 */
struct CliInterface {
  CIType type;      ///< Mode
  int max_attempts; ///< Max amount of attempts
};

ReturnCode ss_ci_run   (const CliInterface *ci); ///< Runs CliInterface for SolveSquare task
ReturnCode ss_run_loop (const CliInterface *ci); ///< Runs CliInterface in loop mode
ReturnCode ss_run_once (const CliInterface *ci, int with_attempts); ///< Runs CliInterface in once modes

#endif // CLI_INTERFACE_H
