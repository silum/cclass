## Makefile.am -- Process this file with automake to produce Makefile.in
## $Id$
## Copyright (C) 2005 Deneys S. Maartens <dsm@tlabs.ac.za>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software Foundation,
## Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

AM_CFLAGS = -std=gnu99 -Wall -Wextra -Werror


XFAIL_TESTS = \
    test_leak

TESTS = \
    test \
    $(XFAIL_TESTS)

noinst_PROGRAMS = \
    $(TESTS)

include_HEADERS = \
    classdef.h \
    xassert.h \
    xmalloc.h

lib_LTLIBRARIES = \
    libcclass.la

libcclass_la_LDFLAGS = -version-info @LIBVERSION@
libcclass_la_SOURCES = \
    xassert.c \
    xmalloc.c

test_LDADD = \
    $(top_builddir)/libcclass.la
test_SOURCES = \
    test.c

test_LDADD = \
    $(top_builddir)/libcclass.la
test_leak_SOURCES = \
    test_leak.c

# .PHONY: doc
# doc:
# 	doxygen doxygen.conf

# maintainer-clean-local:
# 	-rm -rf doc/html/ doc/latex/

AUX_DIR = @ac_aux_dir@

EXTRA_DIST = \
    $(AUX_DIR)/bootstrap \
    $(AUX_DIR)/clobber \
    $(AUX_DIR)/subdir

AUX_DIST = \
    $(AUX_DIR)/compile \
    $(AUX_DIR)/config.guess \
    $(AUX_DIR)/config.sub \
    $(AUX_DIR)/depcomp \
    $(AUX_DIR)/install-sh \
    $(AUX_DIR)/ltmain.sh \
    $(AUX_DIR)/missing \
    $(AUX_DIR)/mkinstalldirs

DISTCLEANFILES = \
    stamp-h \
    stamp-h[0-9]*

MAINTAINERCLEANFILES = \
    aclocal.m4 \
    config.h.in \
    configure \
    Makefile.in \
    $(AUX_DIST)

## -fin-
