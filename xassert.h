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
 *
 *
 * report_xassert function and debug framework
 */
#ifndef DSM_DEBUG_XASSERT_H
#define DSM_DEBUG_XASSERT_H 1

#include <stdbool.h> /*  bool  */
#include <sys/cdefs.h>

__BEGIN_DECLS

/* macro to silence "empty body in an else-statement" warning, when
 * using xassert in the form `xassert(expr);' */
#define XASSERT(expr) xassert(expr){}

/**
 * @brief flag to enable or disable pausing for user input on assertion
 * failure report
 */
extern bool XASSERT_INTERACTIVE;
/**
 * @brief set to true when an assertion failure has occured
 */
extern bool XASSERT_FAILURE;

/**
 * @brief user defined assertion failure report
 *
 * prints an error message refering to the file name and line number
 * where the error has occured
 *
 * @param file  name of file where error occured
 * @param line  line number where error occured
 */
void report_xassert(const char *file,
		    int line);

/**
 * @brief test framework function
 *
 * calls the user function and tests for assertion failures and memory
 * allocation on return
 *
 * @param user_func  user defined function
 *
 * @return EXIT_SUCCESS if no errors occurred, else EXIT_FAILURE
 */
int debug_test(void (*user_func)());

__END_DECLS

#endif /* DSM_DEBUG_XASSERT */
