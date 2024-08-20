#ifndef RETURN_CODES_H
#define RETURN_CODES_H

enum ReturnCode {
  OK                  = 0,
  QUIT                = 1,
  ERR_UNKNOWN_EQ_TYPE = 2,
  ERR_UNKNOWN_CI_TYPE = 4,
  ERR_INVALID_INPUT   = 5,
  ERR_D_POSITIVE      = 6
};

#endif // RETURN_CODE_H
