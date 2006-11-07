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
#ifndef ITL_CCLASS_MALLOC_H
#define ITL_CCLASS_MALLOC_H

#include <cclass/assert.h> /* bool */

__BEGIN_DECLS

/**
 * @brief Free memory allocated memory for an object
 *
 * @param obj  object to free
 *
 * For example:
 * @code
 * FREEOBJ(obj);
 * @endcode
 */
#define FREEOBJ(obj) (obj = cclass_free(obj))

/**
 * @def ISPOWER(x)
 * @brief Test if a number is a power of two
 *
 * @param x  number to check
 */
#ifndef DOXYGEN_SKIP
#define ISPOWER2(x) (!((x)&((x)-1)))
#else
#define ISPOWER2(x)
#endif /* DOXYGEN_SKIP */

/**
 * @brief MALLOC utility macro
 */
#define MALLOC(size) \
     cclass_malloc(size, 0, __FILE__, __LINE__)

/**
 * @brief Allocate memory to contain N (size) array elements
 *
 * @param array  new array
 * @param size  number of elements to allocate
 */
#define NEWARRAY(array, size) \
  (array = cclass_malloc((size_t)(sizeof(*(array))*(size)), \
  0,SRCFILE,__LINE__))

/**
 * @brief Allocate memory for an object
 *
 * @param obj  object to allocate
 *
 * For example:
 * @code
 * obj_t obj;
 * NEWOBJ(obj);
 * @endcode
 */
#define NEWOBJ(obj) \
  (obj = cclass_malloc(sizeof(*obj),&_CD(obj),SRCFILE,__LINE__))

/**
 * @brief Allocates memory for a string of size - 1 bytes
 *
 * @param dest  new string
 * @param size  number of bytes to allocate
 */
#define NEWSTRING(dest, size) \
  (dest = cclass_malloc((size_t)(size),0,SRCFILE,__LINE__))

/**
 * @def NUMSTATICELS(array)
 * @brief Number of static elements in an array
 *
 * @param array  array to check
 */
#define NUMSTATICELS(array) (sizeof(array)/sizeof(*array))

/**
 * @brief Resize an array so contain N (size) array elements
 *
 * @param array  resized array
 * @param size  number of elements
 */
#define RESIZEARRAY(array, size) \
  (array = cclass_realloc((array), \
  (size_t)(sizeof(*(array))*(size)),SRCFILE,__LINE__))

/**
 * @brief Duplicate a string
 *
 * @param dest  duplicated string
 * @param source  string to duplicate
 */
#define STRDUP(dest, source) \
  (dest = cclass_strdup(source,SRCFILE,__LINE__))

/**
 * @brief Memory Free
 *
 * Free a block of memory that was previously allocated through xnew().
 *
 * @param p  heap pointer to free or 0
 *
 * @return 0
 */
void *cclass_free(void *p);

/**
 * @brief Class descriptor
 */
#ifndef DOXYGEN_SKIP
typedef struct classdesc_tag {
	char *name;
} classdesc;
#endif /* DOXYGEN_SKIP */

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
cclass_malloc(size_t size,
	      classdesc *desc,
	      const char *file,
	      int line);

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
void *
cclass_realloc(void *p,
	       size_t size,
	       const char *file,
	       int line);

/**
 * @brief Memory string duplicator
 *
 * @param s  string to duplicate (or 0)
 * @param file  filename where string is being duplicated
 * @param line  line number where string is being duplicated
 *
 * @return a pointer to the duplicated string or 0
 */
void *
cclass_strdup(const char *s,
	      const char *file,
	      int line);

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
cclass_test_pointer(void *p);

/**
 * @brief Walk heap
 *
 * Display a symbolic dump of the heap by walking the heap and
 * displaying all objects in the heap.
 */
int
cclass_walk_heap();

__END_DECLS

#endif /* ITL_CCLASS_MALLOC_H */
