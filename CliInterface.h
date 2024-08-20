#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "SqEquation.h"
#include "ReturnCodes.h"

const int DEF_MAX_ATTEMPTS = 10;

enum CIType {
  LOOP                 = 0,
  ONCE_WITH_ATTEMPTS    = 1,
  ONCE_WITHOUT_ATTEMPTS = 2
};

struct CliInterface {
  CIType type;
  int max_attempts;
};

ReturnCode ss_ci_run   (const CliInterface *ci);
ReturnCode ss_run_loop (const CliInterface *ci, SqEquation *eq);
ReturnCode ss_run_once (const CliInterface *ci, SqEquation *eq, int with_attempts);

#endif // CLI_INTERFACE_H
