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
 * @brief Dummy object definition
 */
#include "dummy.h" /* class implemented */
#include "cclass/xassert.h"
#include "cclass/xmalloc.h"

USE_XASSERT

/**
 * @brief dummy object
 */
CLASS(dummy, dummy_t) {
	char *data;
	int size;
};

dummy_t
dummy_create(int size)
{
	if (size < 0) {
		return 0;
	}

	dummy_t dummy = 0;
	NEWOBJ(dummy);

	if (dummy) {
		dummy->size = size;
		NEWSTRING(dummy->data, size);
	}

	return dummy;
}

dummy_t
dummy_destroy(dummy_t dummy)
{
	VERIFYZ(dummy) {
		xdelete(dummy->data);
		FREEOBJ(dummy);
	}

	return 0;
}

int
dummy_set(dummy_t dummy,
	  int value)
{
	(void) value;
	int status = 0;

	VERIFY(dummy) {
		for (int i = 0; i < dummy->size; i++) {
			dummy->data[i] = value;
		}
		status = 1;
	}

	return status;
}
