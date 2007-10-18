## $Id$
## Copyright (C) 2005, 2006 Deneys S. Maartens <dsm@tlabs.ac.za>
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

## Process this file with automake to produce Makefile.in.

ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = \
    -std=gnu99 \
    -Wall \
    -Werror \
    -Wextra

DIST_SUBDIRS = \
    cclass \
    tests

aclocaldir = \
    $(datadir)/aclocal
dist_aclocal_DATA = \
    m4/cclass.m4

nobase_include_HEADERS = \
    cclass/classdef.h \
    cclass/assert.h \
    cclass/malloc.h

noinst_HEADERS = \
    tests/dummy.h \
    tests/redirect.h \
    tests/verbose-argp.h

lib_LTLIBRARIES = \
    cclass/libcclass.la

check_PROGRAMS = \
    $(TESTS)

if TESTS
TESTS = \
    tests/cclass
endif

cclass_libcclass_la_LDFLAGS = \
    -version-info $(LIBVERSION)
cclass_libcclass_la_SOURCES = \
    cclass/assert.c \
    cclass/malloc.c

tests_cclass_LDADD = \
    cclass/libcclass.la \
    $(CHECK_LIBS)
tests_cclass_SOURCES = \
    tests/cclass.c \
    tests/dummy.c \
    tests/verbose-argp.c

.PHONY: doc
doc: doc/doxy/doxygen.conf
	doxygen $< > /dev/null

maintainer-clean-local:
	-rm -rf doc/html/ doc/latex/

.PHONY: dist-rpm
dist-rpm: distcheck
	rpmbuild -ta $(distdir).tar.gz

ChangeLog:
	cd $(srcdir) ; \
    svn log -v --xml \
        | aux/bin/svn2log.py \
            --only-date \
            --output $(top_builddir)/$@ \
            --prefix='/(branches/[^/]+|trunk)' \
            --users=aux/users

EXTRA_DIST = \
    $(ac_aux_dir)/autogen.sh \
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
    ChangeLog \
    config.h.in \
    configure \
    COPYING \
    INSTALL \
    Makefile.in \
    $(AUX_DIST)

## -fin-
