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
 * @mainpage
 * C private class methodology, based on the source presented in:
 *
 * "Writing Bug-Free C Code -- A Programming Style That Automatically
 * Detects Bugs in C Code" by Jerry Jongerius / January 1995
 *
 * http://www.duckware.com/bugfreec/
 * <last visited: Tue Sep 28 08:20:13 SAST 2004>
 */
/**
 * @file
 * @brief C-Class declaration
 */
#ifndef ITL_CCLASS_CLASSDEF_H
#define ITL_CCLASS_CLASSDEF_H

#include <sys/types.h> /* size_t */

__BEGIN_DECLS

/**
 * @brief Assert during compile-time (not run-time)
 *
 * Will produce a compiler error of assertion does not hold.
 *
 * @param exp  expression to be asserted
 */
#ifndef DOXYGEN_SKIP
#define compiler_assert(exp) extern char _compiler_assert[(exp)?1:-1]
#else
#define compiler_assert(exp)
#endif /* DOXYGEN_SKIP */

/**
 * @brief Absolute value utility definition
 */
#ifndef DOXYGEN_SKIP
#define ABS(x) (((x)>0)?(x):-(x))
#else
#define ABS(x)
#endif /* DOXYGEN_SKIP */

/**
 * @brief Test if a number is a power of two
 */
#ifndef DOXYGEN_SKIP
#define ISPOWER2(x) (!((x)&((x)-1)))
#else
#define ISPOWER2(x)
#endif /* DOXYGEN_SKIP */

/**
 * @brief Number of static elements in an array
 */
#define NUMSTATICELS(array) (sizeof(array)/sizeof(*array))

/**
 * @brief Enables xassert support in a source file
 *
 * By calling this macro at the top of a source file, the _do_xassert
 * macro declared.  \c xassert() uses the _do_xassert macro to print a
 * run-time error message and by calling the user defined
 * xassert_report() function with the file name and line number where
 * the assertion failure occured.
 */
#ifndef DOXYGEN_SKIP
# define USE_XASSERT                  \
  static char SRCFILE[] = __FILE__; \
  static void _do_xassert(int line) { \
    xassert_report(SRCFILE, line);    \
  }
#define asserterror() _do_xassert(__LINE__)
#define xassert(exp) if (!(exp)) { asserterror(); } else
#else
# define USE_XASSERT
#endif /* DOXYGEN_SKIP */

/**
 * @brief Class descriptor
 */
#ifndef DOXYGEN_SKIP
typedef struct classdesc_tag {
	char *name;
} classdesc;
#endif /* DOXYGEN_SKIP */

/**
 * @brief Declare a new handle
 *
 * NEWHANDLE() declarations are almost always placed in an
 * include file that gets included into all source files. NEWHANDLE() is
 * usually not used in source files.
 *
 * @param handle  new handle to declare
 *
 * For example:
 * @code
 * NEWHANDLE(list_t);
 * @endcode
 */
#define NEWHANDLE(handle) typedef struct tag_##handle *handle

#ifndef DOXYGEN_SKIP
/* class descriptor name from object name */
#define _CD(obj) obj##_classdesc
#endif /* DOXYGEN_SKIP */

/**
 * @brief The class macro
 *
 * The CLASS() macro is used only by source files that implement an
 * object.  The CLASS() macro is never used in include files.
 *
 * @param object  the object handle, to be used in the VERIFY* type
 * macros
 * @param handle  the object handle type, used to declare an object
 *
 * For example:
 * @code
 * CLASS(list, list_t)
 * @endcode
 */
#ifndef DOXYGEN_SKIP
#define CLASS(object,handle) \
    static classdesc _CD(object)={#object}; \
    struct tag_##handle
#else
#define CLASS(object, handle) struct handle
#endif

/* object verification macros */
/**
 * @brief Verify an object
 *
 * Verify that the object (variable name) matches the object type, as
 * declared to the heap manager.
 *
 * For example:
 * @code
 * VERIFY(obj);
 * // or
 * VERIFY(obj) {
 *     // only executed if verfication holds
 * }
 * @endcode
 */
#define VERIFY(obj) xassert(_VERIFY(obj))

/**
 * @brief Verify an object, allows NULL too
 *
 * Verify that the object (variable name) matches the object type, as
 * declared to the heap manager, or that the object is NULL.
 *
 * For example:
 * @code
 * VERIFYZ(obj);
 * // or
 * VERIFYZ(obj) {
 *     // only executed if verfication holds
 * }
 * @endcode
 */
#define VERIFYZ(obj) if (!(obj)) {} else VERIFY(obj)

/* WARNING: _VERIFY needs be tailored to your environment */
#ifndef DOXYGEN_SKIP
#define _S4 (sizeof(classdesc*))
#define _S8 (sizeof(classdesc*)+sizeof(void *))
#define _VERIFY(obj) \
    ( xtestptr(obj) && \
      (((void *)obj) == *(void **)((char *)obj-_S8)) \
      && ((&_CD(obj)) == *(classdesc **)((char *)obj-_S4)) )
#endif /* DOXYGEN_SKIP */

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
  (obj = xnew(sizeof(*obj),&_CD(obj),SRCFILE,__LINE__))

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
#define FREEOBJ(obj) (obj = xfree(obj))

/**
 * @brief Allocates memory for a string of size - 1 bytes
 *
 * @param dest  new string
 * @param size  number of bytes to allocate
 */
#define NEWSTRING(dest, size) \
  (dest = xnew((size_t)(size),NULL,SRCFILE,__LINE__))

/**
 * @brief Duplicate a string
 *
 * @param dest  duplicated string
 * @param source  string to duplicate
 */
#define STRDUP(dest, source) \
  (dest = xstrdup(source,SRCFILE,__LINE__))

/**
 * @brief Allocate memory to contain N (size) array elements
 *
 * @param array  new array
 * @param size  number of elements to allocate
 */
#define NEWARRAY(array, size) \
  (array = xnew((size_t)(sizeof(*(array))*(size)), \
  NULL,SRCFILE,__LINE__))

/**
 * @brief Resize an array so contain N (size) array elements
 *
 * @param array  resized array
 * @param size  number of elements
 */
#define RESIZEARRAY(array, size) \
  (array = xrealloc((array), \
  (size_t)(sizeof(*(array))*(size)),SRCFILE,__LINE__))

__END_DECLS

#endif /* ITL_CCLASS_CLASSDEF_H */
