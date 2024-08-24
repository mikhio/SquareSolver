#include <string.h>
#include <assert.h>
#include "../inc/CliArgsHandler.h"
#include "../inc/ReturnCodes.h"
#include "../inc/CliInterface.h"
#include "../inc/IoTool.h"

/**
 * Set interface mode and print help info
 * @param[out] ci   pointer to interface
 * @param[in]  argc amount of arguments
 * @param[in]  argv array of arguments
 * @return Erorr code (if ok return ReturnCode::OK)
 */
ReturnCode handleProgramArgs(CliInterface *ci, int argc, char **argv) {
  assert(ci);
  assert(argv);
  assert(argc > 0);

  if (argc == 1)
    return OK;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--once_without_attempts") == 0) {
      ci->type = ONCE_WITHOUT_ATTEMPTS;
    } else if (strcmp(argv[i], "-ow") == 0 || strcmp(argv[i], "--once_with_attempts") == 0) {
      ci->type = ONCE_WITH_ATTEMPTS;
    } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--loop") == 0) {
      ci->type = LOOP;
    } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--self_testing") == 0) {
      ci->type = SELF_TESTING;
    } else if (strcmp(argv[i], "-h") == 0) {
      printShortHelp();
      return QUIT;
    } else if (strcmp(argv[i], "--help") == 0) {
      printLongHelp();
      return QUIT;
    } else {
      return ERR_UNKNOWN_ARG;
    }
  }

  return OK;
}
