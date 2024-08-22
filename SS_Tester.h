#ifndef SS_TESTER_H
#define SS_TESTER_H

#include "SqEquation.h"
#include "ReturnCodes.h"

const int TESTS_AMOUNT = 6;

ReturnCode ss_run_tests ();
ReturnCode ss_run_test  (int test_i, SqEquation *test_eq, SqEquation ss_tests[TESTS_AMOUNT]);

ReturnCode readTests   (const char *file_path, SqEquation eq_tests[TESTS_AMOUNT]);
ReturnCode addTest     (const SqEquation *eq, SqEquation eq_tests[TESTS_AMOUNT], int test_index);
ReturnCode parseEqType (char *type_str, SqEquation *eq);

#endif // SS_TESTER_H
