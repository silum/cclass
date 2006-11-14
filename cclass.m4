dnl $Id$
dnl Copyright (C) 2006  Deneys S. Maartens  <dsm@tlabs.ac.za>
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2, or (at your option)
dnl any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

dnl AM_LIB_CCLASS([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
dnl Test for CCLASS, and define CCLASS_CPPFLAGS and CCLASS_LIBS

AC_DEFUN([AM_LIB_CCLASS], [
  AC_ARG_WITH([cclass],
    [AC_HELP_STRING([--with-cclass@<:@=PATH@:>@],
      [prefix where cclass is installed [default=auto]])])

  AC_ARG_WITH([cclass-include],
    [AC_HELP_STRING([--with-cclass-include=PATH],
      [cclass include directory])])

  AC_ARG_WITH([cclass-lib],
    [AC_HELP_STRING([--with-cclass-lib=PATH],
      [cclass library directory])])

  if test "x$with_cclass_include" = "xno"; then
    with_cclass="no"
  fi

  if test "x$with_cclass_lib" = "xno"; then
    with_cclass="no"
  fi

  if test "x$with_cclass" != "xno"; then
    if test "x$with_cclass" = "xyes"; then
      with_cclass=
    fi

    # Prefix does not take precedence over include and lib.
    if test "x$with_cclass" != "x" ; then
      if test "x$with_cclass_include" = "x"; then
        with_cclass_include="$with_cclass/include"
      fi

      if test "x$with_cclass_lib" = "x"; then
        with_cclass_lib="$with_cclass/lib"
      fi
    fi

    # Set include directory.
    if test "x$with_cclass_include" != "x" ; then
      CCLASS_CPPFLAGS="-I$with_cclass_include"
    fi

    # Set library directory.
    if test "x$with_cclass_lib" != "x" ; then
      CCLASS_LIBS="-L$with_cclass_lib -lcclass"
    else
      CCLASS_LIBS="-lcclass"
    fi

    # Check for library.
    ac_save_LIBS="$LIBS"
    LIBS="$CCLASS_LIBS $LIBS"
    AC_CHECK_LIB(
      [cclass],
      [cclass_malloc],
      [],
      [with_cclass="no"]
    )
    LIBS="$ac_save_LIBS"

    # Check for headers.
    ac_save_CPPFLAGS="$CPPFLAGS"
    CPPFLAGS="$CCLASS_CPPFLAGS $CPPFLAGS"
    AC_CHECK_HEADERS(
      [cclass/assert.h cclass/classdef.h cclass/malloc.h],
      [],
      [with_cclass="no"]
    )
    CPPFLAGS="$ac_save_CPPFLAGS"
  fi

  if test "x$with_cclass" != "xno"; then
    ifelse([$1], [], [:], [$1])
  else
    CCLASS_CPPFLAGS=""
    CCLASS_LIBS=""
    ifelse([$2], [], [:], [$2])
  fi

  AC_SUBST(CCLASS_CPPFLAGS)
  AC_SUBST(CCLASS_LIBS)
])

dnl -fin-
dnl vim:sts=2:sw=2:
