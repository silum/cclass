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

#include <cclass/assert.h>
#include <cclass/malloc.h>

__BEGIN_DECLS

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
/* class descriptor name from object name utility macro */
#define _CD(obj) \
  obj##_classdesc
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
#define CLASS(object, handle) \
  struct handle
#endif

/* object verification macros */
/**
 * @def VERIFY(obj)
 * @brief Verify an object
 *
 * Verify that the object (variable name) matches the object type, as
 * declared to the heap manager.
 *
 * @param obj  object to verify
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
#define VERIFY(obj) cclass_assert(_VERIFY(obj))

/**
 * @def VERIFYZ(obj)
 * @brief Verify an object, allows NULL too
 *
 * Verify that the object (variable name) matches the object type, as
 * declared to the heap manager, or that the object is NULL.
 *
 * @param obj  object to verify
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
  ( cclass_test_pointer(obj) && \
    (((void *)obj) == *(void **)((char *)obj-_S8)) \
    && ((&_CD(obj)) == *(classdesc **)((char *)obj-_S4)) )
#endif /* DOXYGEN_SKIP */

__END_DECLS

#endif /* ITL_CCLASS_CLASSDEF_H */
