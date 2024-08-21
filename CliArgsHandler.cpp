#include <string.h>
#include <assert.h>
#include "CliArgsHandler.h"
#include "ReturnCodes.h"
#include "CliInterface.h"
#include "IoTool.h"

ReturnCode handleProgramArgs(CliInterface *ci, int argc, char **argv) {
  assert(ci);
  assert(argv);

  if (argc == 1)
    return OK;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--once_without_attempts") == 0) {
      ci->type = ONCE_WITHOUT_ATTEMPTS;
    } else if (strcmp(argv[i], "-ow") == 0 || strcmp(argv[i], "--once_with_attempts") == 0) {
      ci->type = ONCE_WITH_ATTEMPTS;
    } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--loop") == 0) {
      ci->type = ONCE_WITH_ATTEMPTS;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printHelp();
      return QUIT;
    } else {
      return ERR_UNKNOWN_ARG;
    }
  }

  return OK;
}
