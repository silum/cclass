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
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "dummy.h"

/**
 * @brief Allocate and free memory
 */
static
void
alloc_free(void)
{
	dummy_t dummy;
	dummy = dummy_create(10);
	dummy_set(dummy, 0);
	dummy = dummy_destroy(dummy);
}

/**
 * @brief Allocate memory but do not free it
 */
static
void
alloc_nofree(void)
{
	dummy_t dummy;
	dummy = dummy_create(10);
	dummy_set(dummy, 0);
	/* induce memory leak by omitting dummy_destroy() */
}

/**
 * @brief Test alloc_free()
 */
START_TEST(test_alloc_free)
{
	fail_unless(EXIT_SUCCESS == cclass_assert_test(alloc_free));
}
END_TEST

/**
 * @brief Test alloc_nofree()
 */
START_TEST(test_alloc_nofree)
{
	fail_unless(EXIT_FAILURE == cclass_assert_test(alloc_nofree));
}
END_TEST

/**
 * @brief Create test suite
 *
 * @return test suite
 */
static
Suite *
cclass_suite(void)
{
	Suite *s = suite_create("cclass");

	TCase *tc_core = tcase_create("Core");
	suite_add_tcase(s, tc_core);
	tcase_add_test(tc_core, test_alloc_free);
	tcase_add_test(tc_core, test_alloc_nofree);

	return s;
}

/**
 * @brief cclass test program
 *
 * No warnings/errors are expected.
 *
 * @return:
 * - EXIT_SUCCESS if all tests succeeded
 * - EXIT_FAILURE if any test fails
 */
int
main(void)
{
	int nf;
	Suite *s = cclass_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
