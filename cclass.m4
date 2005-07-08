dnl $Id$
dnl Copyright (C) 2005 Deneys S. Maartens <dsm@tlabs.ac.za>

dnl AM_LIB_CCLASS([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
dnl Test for CCLASS, and define CCLASS_LIBS
dnl
AC_DEFUN([AM_LIB_CCLASS],
[AC_ARG_WITH([cclass],
    [AC_HELP_STRING([--with-cclass=DIR],
        [cclass base directory, or:])],
    [cclass="$withval"])

AC_ARG_WITH([cclass-include],
    [AC_HELP_STRING([--with-cclass-include=DIR],
        [cclass headers directory])],
    [cclass_include="$withval"])

# Disable cclass support.
if test "x$with_cclass_include" = "xno"; then
    with_cclass="no"
fi

AC_ARG_WITH([cclass-lib],
    [AC_HELP_STRING([--with-cclass-lib=DIR],
        [cclass library directory])],
    [cclass_lib="$withval"])

# Disable cclass support.
if test "x$with_cclass_lib" = "xno"; then
    with_cclass="no"
fi

AC_SUBST(CCLASS_LIBS)
if test "x$with_cclass" != "xno"; then
    if test "x$cclass" = "xyes"; then
        cclass=
    fi

    # Base directory takes precendence over lib and include.
    if test "x$cclass" != "x" ; then
#        AC_MSG_NOTICE([using cclass base directory $cclass])

        if test "x$cclass_include" = "x"; then
            cclass_include=$cclass/include
        fi

        if test "x$cclass_lib" = "x"; then
            cclass_lib=$cclass/lib
        fi
    fi

    # set include directory
    if test "x$cclass_include" != "x" ; then
        if test -d "$cclass_include"; then
            CPPFLAGS="$CPPFLAGS -I$cclass_include"
#            if test "x$cclass" = "x"; then
#                AC_MSG_NOTICE([using cclass include directory $cclass_include])
#            fi
        fi
    fi

    # set library directory
    if test "x$cclass_lib" != "x" ; then
        if test -d "$cclass_lib"; then
            LDFLAGS="$LDFLAGS -L$cclass_lib"
#            if test "x$cclass" = "x"; then
#                AC_MSG_NOTICE([using cclass library directory $cclass_lib])
#            fi
        fi
    fi

    # Check for library.
    AC_CHECK_LIB([cclass], [xfree])
    if test "$ac_cv_lib_cclass_xfree" != "yes" ; then
        with_cclass="no"
    fi

    # Check for headers.
    AC_CHECK_HEADERS([classdef.h xassert.h xmalloc.h],,
        with_cclass="no"
    )

    if test "x$with_cclass" != "xno"; then
        CCLASS_LIBS="-lcclass"
        ifelse([$1], , :, [$1])
    else
        CCLASS_LIBS=
        ifelse([$2], , :, [$2])
    fi
fi])

dnl -fin-
