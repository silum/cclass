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
 * @brief cclass_assert_report() function and debug framework definition
 */
#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "assert.h"
#include "malloc.h"

#ifndef DOXYGEN_SKIP
USE_XASSERT
#endif

bool XASSERT_INTERACTIVE = true;
bool XASSERT_FAILURE = false;

int
cclass_assert_test(void (*test_func)())
{
	XASSERT_FAILURE = false;
	XASSERT_INTERACTIVE = false;

	test_func();

	XASSERT(cclass_walk_heap() == 0) {
		/* empty */
	}

	if (XASSERT_FAILURE) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void
cclass_assert_fail(const char *fmt,
		   ...)
{
	va_list args;
	va_start(args, fmt);
	verrx(EXIT_FAILURE, fmt, args);
	va_end(args);
}

void
cclass_assert_report(const char *file_name,
		     int line)
{
	printf(" ** cclass_assert: %s-%d ", file_name, line);
	XASSERT_FAILURE = true;
	if (XASSERT_INTERACTIVE) {
		printf("(Press ENTER) ");
		while ('\n' != getchar()) {
			usleep(250000);
		}
	} else {
		printf("\n");
	}
}
