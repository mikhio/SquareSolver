#include <stdio.h>
#include <stdlib.h>
#include "../inc/SS_Assert.h"

/**
 * @param[in] flag       if flag is 1 then make assert
 * @param[in] __expr     string with checking expression
 * @param[in] __line     number of expression line
 * @param[in] __function name of function with expression
 */
void ss_assert_func(int flag, const char *__expr,
    const char *__file, unsigned int __line, const char *__function)
{
 if (flag) {
   fprintf(stderr, "%d %s %s SS_Assertion: in %s \n", __line, __file, __function, __expr);
   exit(1);
 }
}
