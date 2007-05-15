# $Id$
# Copyright (C) 2005, 2006  Deneys S. Maartens  <dsm@tlabs.ac.za>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# Process this file with autoconf to produce a configure script.

AC_INIT([cclass], [0.6], [dsm@tlabs.ac.za])

dnl CURRENT:REVISION:AGE
dnl - library source changed -> inc REVISION
dnl - interfaces added/removed/changed -> inc CURRENT, REVISION = 0
dnl - interfaces added -> inc AGE
dnl - interfaces removed -> AGE = 0
LIBVERSION="1:0:0"
AC_SUBST([LIBVERSION])

AC_REVISION([$Rev$])

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_AUX_DIR([config])
AC_SUBST([ac_aux_dir])

AM_INIT_AUTOMAKE([subdir-objects])

# create a config.h file (Automake will add -DHAVE_CONFIG_H)
AM_CONFIG_HEADER([config.h])

dnl --------------------------------------------------------------------
dnl Checks for programs.

AC_PROG_CC
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

dnl --------------------------------------------------------------------
dnl Checks for libraries.

AM_PATH_CHECK([], [], [AC_MSG_ERROR([libcheck required])])

dnl --------------------------------------------------------------------
dnl Checks for header files.

AC_HEADER_STDC
AC_CHECK_HEADERS([sys/cdefs.h stdbool.h], [],
    AC_MSG_ERROR([required header file missing]))

dnl --------------------------------------------------------------------
dnl Checks for typedefs, structures, and compiler characteristics.

dnl --------------------------------------------------------------------
dnl Checks for library functions.

dnl --------------------------------------------------------------------
dnl Create output files.

AC_CONFIG_FILES([
    cclass.spec
    doc/doxy/doxygen.conf
    Makefile
    cclass/Makefile
    tests/Makefile
])
AC_OUTPUT

# -fin-
