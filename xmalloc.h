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
 * @brief Memory allocation function declarations
 */
#ifndef ITL_XMALLOC_H
#define ITL_XMALLOC_H

#include <stdbool.h> /*  bool  */
#include <classdef.h>

__BEGIN_DECLS

/**
 * @brief xmalloc utility macro
 */
#define xmalloc(size) \
     xnew(size, 0, __FILE__, __LINE__)

/**
 * @brief Memory new
 *
 * Allocate a new block of memory from the heap.
 *
 * @param size  size of object to allocate
 * @param desc  class descriptor for object (or 0)
 * @param file  filename where object was allocated
 * @param line  line number where object was allocated
 *
 * @return a pointer to the memory object or 0
 */
void *
xnew(size_t size,
     classdesc *desc,
     const char *file,
     int line);

/**
 * @brief Memory Free
 *
 * Free a block of memory that was previously allocated through xnew().
 *
 * @param p  heap pointer to free or 0
 *
 * @return 0
 */
void *xfree(void *p);

/**
 * @brief Memory realloc
 *
 * Reallocate a block of memory.
 *
 * @param p  heap object to reallocate or 0
 * @param size  new size of the object
 * @param file  filename where realloc is taking place
 * @param line  line number where realloc is taking place
 *
 * @return a pointer to the reallocated memory or 0
 */
void *xrealloc(void *p,
	       size_t size,
	       const char *file,
	       int line);

/**
 * @brief Memory string dup
 *
 * Helper function for the xstrdup() macro.
 *
 * @param s  string to duplicate (or 0)
 * @param file  filename where string is being duplicated
 * @param line  line number where string is being duplicated
 *
 * @return a pointer to the duplicated string or 0
 */
void *xstrdup(const char *s,
	      const char *file,
	      int line);

/**
 * @brief Walk heap
 *
 * Display a symbolic dump of the heap by walking the heap and
 * displaying all objects in the heap.
 */
int
xwalkheap();

/**
 * @brief Does pointer point into the heap?
 *
 * Does the given memory pointer point anywhere into the heap.
 *
 * @param p  heap pointer to check
 *
 * @return true if pointer points into the heap, or false if not
 */
bool
xtestptr(void *p);

/**
 * @brief Prototype for user defined xassert report function
 *
 * @param file  name of file where assertion failed
 * @param line  line number where assertion failed
 */
void
report_xassert(const char *file,
	       int line);

__END_DECLS

#endif /* ITL_XMALLOC_H */
