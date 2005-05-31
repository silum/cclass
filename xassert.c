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
 * @brief report_xassert() function and debug framework definition
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "xassert.h"
#include "xmalloc.h"

USE_XASSERT

bool XASSERT_INTERACTIVE = true;
bool XASSERT_FAILURE = false;

void
report_xassert(const char *file_name, int line)
{
	printf(" ** xassert: %s-%d ", file_name, line);
	XASSERT_FAILURE = true;
	if (XASSERT_INTERACTIVE) {
		printf("(Press Enter) ");
		while ('\n' != getchar()) {
			/* empty */
		}
	} else {
		printf("\n");
	}
}

int
debug_test(void (*test_func)())
{
	XASSERT_FAILURE = false;
	XASSERT_INTERACTIVE = false;

	test_func();

	XASSERT(xwalkheap() == 0);

	if (XASSERT_FAILURE)
		return EXIT_FAILURE;

	printf("\nAll tests passed\n");
	return EXIT_SUCCESS;
}

