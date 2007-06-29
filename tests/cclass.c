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

#include "config.h"
#include "dummy.h"
#include "redirect.h" /* redirect_dev_null() */
#include "verbose-argp.h" /* verbose,verbose_argp */

/**
 * @def PROGRAM_NAME
 * @brief program name
 */
#define PROGRAM_NAME "cclass"
/**
 * @def PROGRAM_DOC
 * @brief program documentation
 */
#define PROGRAM_DOC  PROGRAM_NAME " test program"

/** program version */
const char *argp_program_version =
PROGRAM_NAME " (" PACKAGE_NAME ") " PACKAGE_VERSION;

/** bug report address */
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/** argp children */
static const struct argp_child argp_children[] = {
	{
		.argp = &verbose_argp,
	},
	ARGP_CHILD_END
};

/** our argp parser */
static struct argp argp = {
	.doc = PROGRAM_DOC,
	.children = argp_children,
};

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
 * @brief Setup function for test suite
 */
static
void
setup(void)
{
	if (!verbose) {
		redirect_dev_null(stderr);
		redirect_dev_null(stdout);
	}
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
	tcase_add_checked_fixture(tc_core, setup, NULL);

	return s;
}

/**
 * @brief cclass test program
 *
 * No warnings/errors are expected.
 *
 * @param argc  number of arguments
 * @param argv  argument vector
 *
 * @return:
 * - EXIT_SUCCESS if all tests succeeded
 * - EXIT_FAILURE if any test fails
 */
int
main(int argc,
     char *argv[])
{
	XASSERT_INTERACTIVE = false;

	argp_parse(&argp, argc, argv, 0, 0, 0);

	int nf;
	Suite *s = cclass_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
