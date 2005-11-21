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

DIST_SUBDIRS = \
    cclass \
    tests

TESTS = \
    tests/cclass \
    $(XFAIL_TESTS)

XFAIL_TESTS = \
    tests/cclass_leak

aclocaldir = \
    $(datadir)/aclocal
dist_aclocal_DATA = \
    cclass.m4

nobase_include_HEADERS = \
    cclass/classdef.h \
    cclass/xassert.h \
    cclass/xmalloc.h

lib_LTLIBRARIES = \
    cclass/libcclass.la

noinst_PROGRAMS = \
    $(TESTS)

cclass_libcclass_la_LDFLAGS = \
    -version-info $(LIBVERSION)
cclass_libcclass_la_SOURCES = \
    cclass/xassert.c \
    cclass/xmalloc.c

tests_cclass_LDADD = \
    cclass/libcclass.la
tests_cclass_SOURCES = \
    tests/cclass.c \
    tests/dummy.c

tests_cclass_leak_LDADD = \
    cclass/libcclass.la
tests_cclass_leak_SOURCES = \
    tests/cclass_leak.c \
    tests/dummy.c

.PHONY: doc
doc: doc/doxy/doxygen.conf
	doxygen $< > /dev/null

maintainer-clean-local:
	-rm -rf doc/html/ doc/latex/

.PHONY: distrpm
distrpm: distcheck
	rpmbuild -ta $(distdir).tar.gz

EXTRA_DIST = \
    $(ac_aux_dir)/autogen.sh \
    $(ac_aux_dir)/bootstrap \
    $(ac_aux_dir)/clobber \
    BUILD \
    $(PACKAGE_NAME).spec

AUX_DIST = \
    $(ac_aux_dir)/compile \
    $(ac_aux_dir)/config.guess \
    $(ac_aux_dir)/config.sub \
    $(ac_aux_dir)/depcomp \
    $(ac_aux_dir)/install-sh \
    $(ac_aux_dir)/ltmain.sh \
    $(ac_aux_dir)/missing \
    $(ac_aux_dir)/mkinstalldirs

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
