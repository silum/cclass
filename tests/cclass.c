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
 * @brief Test basic functionality of xmalloc and xassert
 */
#include <stdlib.h>
#include <cclass/xmalloc.h>
#include <cclass/xassert.h>

/**
 * @brief Allocate and free memory
 */
void
test_func()
{
	char *p = xmalloc(1);
	*p = 0;
	p = xfree(p);
}

/**
 * @brief Execute test_func()
 *
 * No warnigns/errors are expected.
 */
int
main()
{
	return debug_test(test_func);
}
