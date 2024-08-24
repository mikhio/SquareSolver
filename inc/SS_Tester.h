#ifndef SS_TESTER_H
#define SS_TESTER_H

/** @file SS_Tester.h */

#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"

const int   TESTS_CHUNK_SIZE = 100;                 ///< Size of tests that will be allocated after overflowed
const char *TESTS_FILE_PATH = "tests/ss_tests2.txt"; ///< Path to file with tests

/// @struct SS_Tests
/**
 * Helps to store array of tests with its size. And change memory dynamically
 */
struct SS_Tests {
  int amount;   ///< Amount of real tests
  int buf_size; ///< Size of allocated memory for array

  SqEquation *tests; ///< Array with tests
};

ReturnCode ss_run_tests (); ///< Runs tests for SolveSquare
ReturnCode ss_run_test  (int test_index, SqEquation *test_eq, SS_Tests *ss_tests); ///< Runs one test for SolveSquare

ReturnCode readTests   (const char *file_path, SS_Tests *ss_tests); ///< Reads tests from file
ReturnCode addTest     (const SqEquation *eq,  SS_Tests *ss_tests); ///< Add test to array with tests
ReturnCode parseEqType (char *type_str, SqEquation *eq);            ///< Parses equation type in file with tests

ReturnCode testsAllocateMore (SS_Tests *ss_tests, int chunk_size);   ///< Allocate more memory for tests
#endif // SS_TESTER_H
