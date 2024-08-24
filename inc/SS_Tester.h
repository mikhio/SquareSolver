#ifndef SS_TESTER_H
#define SS_TESTER_H

/** @file SS_Tester.h */

#include "../inc/SqEquation.h"
#include "../inc/ReturnCodes.h"

const int TESTS_AMOUNT = 6; ///< Amount of SolveSquare tests

ReturnCode ss_run_tests (); ///< Runs tests for SolveSquare
ReturnCode ss_run_test  (int test_i, SqEquation *test_eq, SqEquation ss_tests[TESTS_AMOUNT]); ///< Runs one test for SolveSquare

ReturnCode readTests   (const char *file_path, SqEquation eq_tests[TESTS_AMOUNT]); ///< Reads tests from file
ReturnCode addTest     (const SqEquation *eq, SqEquation eq_tests[TESTS_AMOUNT], int test_index); ///< Add test to array with tests
ReturnCode parseEqType (char *type_str, SqEquation *eq); ///< Parses equation type in file with tests

#endif // SS_TESTER_H
