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

#include <cclass/assert.h> /* USE_XASSERT */
#include <malloc.h> /* NULL */
#include <sys/types.h> /* size_t */

__BEGIN_DECLS

/**
 * @def FREEOBJ(obj)
 * @brief Free memory allocated memory for an object
 *
 * @param[in,out] obj  object to free
 *
 * Usage:
 * @code
 * obj_t obj;
 * NEWOBJ(obj);
 * // ...
 * FREEOBJ(obj);
 * @endcode
 */
#define FREEOBJ(obj) (obj = cclass_free(obj))

/**
 * @def ISPOWER(x)
 * @brief Test if a number is a power of two
 *
 * @param[in] x  number to check
 *
 * @return 0 if number is not a power of two
 *
 * Usage:
 * @code
 * int bar = rand();
 * if (ISPOWER2(bar)) {
 *     // bingo
 * }
 * @endcode
 */
#define ISPOWER2(x) \
  (!((x)&((x)-1)))

/**
 * @def MALLOC(size)
 * @brief MALLOC utility macro
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] size  number of bytes to allocate
 *
 * Usage:
 * @code
 * char *foo;
 * foo = MALLOC(42); // allocate 42 bytes
 * // ...
 * FREEOBJ(foo);
 * @endcode
 *
 * @return a pointer to allocated memory or NULL if the allocation
 * failed
 */
#define MALLOC(size) \
  cclass_malloc(size,NULL,SRCFILE,__LINE__)

/**
 * @def NEWARRAY(array,size)
 * @brief Allocate memory to contain N (size) array elements
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] array  new array
 * @param[in] size  number of elements to allocate
 *
 * Usage:
 * @code
 * int *foo;
 * NEWARRAY(foo,42); // allocate 42 elements
 * // ...
 * FREEOBJ(foo);
 * @endcode
 */
#define NEWARRAY(array,size) \
  (array = MALLOC((size_t)(sizeof(*(array))*(size))))

/**
 * @def NEWOBJ(obj)
 * @brief Allocate memory for an object
 *
 * @param[in] obj  object to allocate
 *
 * Usage:
 * @code
 * obj_t obj;
 * NEWOBJ(obj);
 * // ...
 * FREEOBJ(obj);
 * @endcode
 */
#define NEWOBJ(obj) \
  (obj = cclass_malloc(sizeof(*obj),&_CD(obj),SRCFILE,__LINE__))

/**
 * @brief Allocates memory for a string of size - 1 bytes
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] dest  new string
 * @param[in] size  number of bytes to allocate
 *
 * Usage:
 * @code
 * int *foo;
 * NEWSTRING(foo,42); // allocate 42 bytes
 * // ...
 * FREEOBJ(foo);
 * @endcode
 */
#define NEWSTRING(dest, size) \
  (dest = MALLOC((size_t)(size)))

/**
 * @def NUMSTATICELS(array)
 * @brief Number of static elements in an array
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] array  array to check
 *
 * Usage:
 * @code
 * int foo[42];
 * // ...
 * for (unsigned i = 0; i < NUMSTATICELS(foo); i++) {
 * // access foo[i]
 * }
 * @endcode
 */
#define NUMSTATICELS(array) (sizeof(array)/sizeof(*array))

/**
 * @brief Resize an array to contain N (size) array elements
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] array  resized array
 * @param[in] size  number of elements
 *
 * Usage:
 * @code
 * int *foo;
 * NEWARRAY(foo,42); // allocate 42 bytes
 * // ...
 * RESIZEARRAY(foo,n); // grow/shrink array
 * // ...
 * FREEOBJ(foo);
 * @endcode
 */
#define RESIZEARRAY(array, size) \
  (array = cclass_realloc((array),\
    (size_t)(sizeof(*(array))*(size)),SRCFILE,__LINE__))

/**
 * @brief Duplicate a string
 *
 * Call the USE_XASSERT macro at the top of the source file.
 *
 * @param[in] dest  duplicated string
 * @param[in] source  string to duplicate
 *
 * Usage:
 * @code
 * char *str = STRDUP("some sting");
 * // ...
 * FREEOBJ(str);
 * @endcode
 */
#define STRDUP(dest, source) \
  (dest = cclass_strdup(source,SRCFILE,__LINE__))

/**
 * @brief Memory Free
 *
 * Free a block of memory that was previously allocated through
 * cclass_malloc().
 *
 * @param[in] p  heap pointer to free or 0
 *
 * @return 0
 *
 * Usage:
 * @code
 * char *str = cclass_malloc(42,NULL,__FILE__,__LINE__);
 * // ...
 * str = cclass_free(str);
 * @endcode
 */
void *cclass_free(void *p);

/** Class descriptor */
typedef struct classdesc_tag {
	char *name; /**< class name tag */
} classdesc;

/**
 * @brief Memory new
 *
 * Allocate a new block of memory from the heap.
 *
 * @param[in] size  size of object to allocate
 * @param[in] desc  class descriptor for object (or 0)
 * @param[in] file  filename where object was allocated
 * @param[in] line  line number where object was allocated
 *
 * @return a pointer to the memory object or 0
 *
 * Usage: see NEWARRAY()
 */
void *cclass_malloc(size_t size,
		    classdesc *desc,
		    const char *file,
		    int line);

/**
 * @brief Memory realloc
 *
 * Reallocate a block of memory.
 *
 * @param[in] p  heap object to reallocate or 0
 * @param[in] size  new size of the object
 * @param[in] file  filename where realloc is taking place
 * @param[in] line  line number where realloc is taking place
 *
 * @return a pointer to the reallocated memory or 0
 *
 * Usage: see RESIZEARRAY()
 */
void *cclass_realloc(void *p,
		     size_t size,
		     const char *file,
		     int line);

/**
 * @brief Memory string duplicator
 *
 * @param[in] s  string to duplicate (or 0)
 * @param[in] file  filename where string is being duplicated
 * @param[in] line  line number where string is being duplicated
 *
 * @return a pointer to the duplicated string or 0
 *
 * Usage: see STRDUP()
 */
void *cclass_strdup(const char *s,
		    const char *file,
		    int line);

/**
 * @brief Does pointer point into the heap?
 *
 * Does the given memory pointer point anywhere into the heap.
 *
 * @param[in] p  heap pointer to check
 *
 * @return true if pointer points into the heap, or false if not
 */
bool cclass_test_pointer(void *p);

/**
 * @brief Walk heap
 *
 * Display a symbolic dump of the heap by walking the heap and
 * displaying all objects in the heap.
 *
 * @return
 */
int cclass_walk_heap();

__END_DECLS

#endif /* ITL_CCLASS_MALLOC_H */
