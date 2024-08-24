#ifndef SS_ASSERT_H
#define SS_ASSERT_H

/** @file SS_Assert.h */

/// Calling assert macros
#define SS_ASSERT(x) ss_assert_func( x ? 0 : 1, #x, __FILE__, __LINE__, __func__);

/// My assert function
void ss_assert_func(int x, const char *__expr, const char *__file, unsigned int __line, const char *__function);

#endif // SS_ASSERT_H 
