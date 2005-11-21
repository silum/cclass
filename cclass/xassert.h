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
 * @brief xassert_report() function and debug framework declaration
 */
#ifndef ITL_CCLASS_XASSERT_H
#define ITL_CCLASS_XASSERT_H

#include <stdbool.h> /* bool */
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * @brief Macro to avoid compiler warning.
 *
 * Macro to silence "empty body in an else-statement" warning, when
 * using xassert in the form \c xassert(expr);
 */
#define XASSERT(expr) xassert(expr){}

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
int xassert_test(void (*user_func)());

/**
 * @brief Fail with given error message
 *
 * This function does not return.
 *
 * @param fmt  printf-like format of error message
 * @param ...  printf-like arguments
 */
void xassert_fail(const char *fmt,
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
void xassert_report(const char *file,
		    int line);

__END_DECLS

#endif /* ITL_CCLASS_XASSERT */
