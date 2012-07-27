# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_builddir)

AM_CXXFLAGS = -g -Wall -DDEBUG -O0 -fomit-frame-pointer 

SUBDIRS=

BASIC_HDRS =				\
	xDataStructures.h \
	xGlobals.h 				\
	xPage.h 					\
	xmalloc.h

pkginclude_HEADERS =			\
	$(BASIC_HDRS)

lib_LTLIBRARIES=libxmalloc.la


libxmalloc_la_SOURCES=xmalloc.c

libxmalloc_la_LIBADD= 
