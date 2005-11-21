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
 * @brief Dummy object declaration
 */
#ifndef ITL_DUMMY_H
#define ITL_DUMMY_H

#include "cclass/classdef.h"

__BEGIN_DECLS

/**
 * @brief dummy object handle
 */
NEWHANDLE(dummy_t);

/**
 * @brief Create dummy object
 *
 * @param size  number of bytes to allocate
 *
 * @return newly created dummy object
 */
dummy_t
dummy_create(int size);

/**
 * @brief Destroy dummy object
 *
 * @param dummy  handle of object to be destroyed
 *
 * @return 0
 */
dummy_t
dummy_destroy(dummy_t dummy);

/**
 * @brief Access allocated memory
 *
 * @param dummy  object handle
 * @param val  value to set memory to
 *
 * @return
 * - 0 on invalid_handle, of failure, and
 * - 1 on success
 */
int
dummy_set(dummy_t dummy,
	  int val);

__END_DECLS

#endif /* ITL_DUMMY_H */
