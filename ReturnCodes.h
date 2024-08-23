#ifndef RETURN_CODES_H
#define RETURN_CODES_H

/** @file ReturnCodes.h */

/// @enum ReturnCode
enum ReturnCode {
  OK                  = 0,  ///< All ok
  QUIT                = 1,  ///< Quit from program
  ERR_UNKNOWN_EQ_TYPE = 2,  ///< Unknown EqType value
  ERR_UNKNOWN_CI_TYPE = 4,  ///< Unknown CIType value
  ERR_INVALID_INPUT   = 5,  ///< Invalid input to program
  ERR_D_POSITIVE      = 6,  ///< Discriminant positive instead willing
  ERR_UNKNOWN_ARG     = 7,  ///< Unknonw cli flag or argument
  ERR_TEST_WRONG      = 8,  ///< Test wasn't passed
  ERR_OPEN_FILE       = 9,  ///< Can't open file
  ERR_BUF_OVERFLOW    = 10, ///< Buffer overflow
};

#endif // RETURN_CODE_H
