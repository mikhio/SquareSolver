#ifndef SS_ASSERT_H
#define SS_ASSERT_H

#include <stdio.h>
#include <stdarg.h>


/** @file SS_Assert.h */

#ifdef SS_NDEBUG

/// If not debug mode, then ignore asserts
#define SS_ASSERT(x) ()

#endif // SS_NDEBUG

#ifndef SS_NDEBUG

/// Calling assert macros

#define SS_ASSERT(x) {\
  ss_assert_func( x ? 0 : 1, #x, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
}

#endif // SS_NDEBUG

/// My assert function
void ss_assert_func(int x, const char *expr, const char *file, unsigned int line, const char *function);

#endif // SS_ASSERT_H
