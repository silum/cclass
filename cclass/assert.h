/* $Id$
 * Copyright (C) 2005 Deneys S. Maartens <dsm@tlabs.ac.za>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
/**
 * @file
 * @brief cclass_assert_report() function and debug framework declaration
 */
#ifndef ITL_CCLASS_ASSERT_H
#define ITL_CCLASS_ASSERT_H

#include <stdbool.h> /* bool */
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * @def USE_XASSERT
 * @brief Enables cclass_assert support in a source file
 *
 * By calling this macro at the top of a source file, the
 * _do_cclass_assert macro is declared.  \c cclass_assert() uses the
 * _do_cclass_assert macro to print a run-time error message and by
 * calling the user defined cclass_assert_report() function with the
 * file name and line number where the assertion failure occurred.
 */
#define USE_XASSERT                  \
  static char SRCFILE[] = __FILE__; \
  static void _do_cclass_assert(int line) { \
    cclass_assert_report(SRCFILE, line);    \
  }
#define asserterror() _do_cclass_assert(__LINE__)
#define cclass_assert(exp) if (!(exp)) { asserterror(); } else

/**
 * @def XASSERT
 * @brief cclass_assert() utility macro
 */
#define XASSERT(expr) cclass_assert(expr)

/**
 * @def cclass_compiler_assert(exp)
 * @brief Assert during compile-time (not run-time)
 *
 * Will produce a compiler error of assertion does not hold.
 *
 * @param exp  expression to be asserted
 */
#define cclass_compiler_assert(exp) \
  extern char _cclass_compiler_assert[(exp)?1:-1]

/**
 * @brief Set to true when an assertion failure has occured
 */
extern bool XASSERT_FAILURE;
/**
 * @brief Flag to enable or disable pausing for user input on assertion
 * failure report
 */
extern bool XASSERT_INTERACTIVE;

/**
 * @brief Test framework function
 *
 * Call the user function and tests for assertion failures and memory
 * allocation on return.
 *
 * @param user_func  user defined function
 *
 * @return EXIT_SUCCESS if no errors occurred, else EXIT_FAILURE
 */
int cclass_assert_test(void (*user_func)());

/**
 * @brief Fail with given error message
 *
 * This function does not return.
 *
 * @param fmt  printf-like format of error message
 * @param ...  printf-like arguments
 */
void
cclass_assert_fail(const char *fmt,
		   ...);

/**
 * @brief User defined assertion failure report
 *
 * Print an error message refering to the file name and line number
 * where the error has occured.
 *
 * @param file  name of file where error occured
 * @param line  line number where error occured
 */
void
cclass_assert_report(const char *file,
		     int line);

__END_DECLS

#endif /* ITL_CCLASS_ASSERT */
