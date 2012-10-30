# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_builddir)

#AM_CXXFLAGS = -g -Wall -DDEBUG -O0 -fomit-frame-pointer

SUBDIRS=

BASIC_HDRS =	\
	../include/xmalloc-config.h \
	xassert.h		\
	cache.h			\
	threads.h		\
	align.h			\
	data.h 			\
	globals.h 	\
	page.h 			\
	bin.h 			\
	region.h 		\
	system.h 		\
	xmalloc.h

SOURCES=		\
	threads.c	\
	cache.c		\
	globals.c	\
	page.c		\
	bin.c			\
	region.c	\
	system.c	\
	xmalloc.c

pkginclude_HEADERS =	\
	$(BASIC_HDRS)

libxmalloc_la_CPPFLAGS= $(AM_CXXFLAGS) -Wall -pthread -D__XMALLOC_NDEBUG -DNDEBUG $(INCLUDES)

libxmalloc_la_SOURCES=	\
	$(SOURCES)

libxmalloc_la_LIBADD=
if ENABLE_DEBUG
AM_CPPFLAGS= -g3 -ggdb -Wall -pthread -D__XMALLOC_DEBUG -DDEBUG $(INCLUDES)
lib_LTLIBRARIES=libxmalloc.la libxmalloc_debug.la
libxmalloc_debug_la_CPPFLAGS=$(AM_CPPFLAGS)
libxmalloc_debug_la_SOURCES=	\
	$(SOURCES)
libxmalloc_debug_la_LIBADD=
else
lib_LTLIBRARIES=libxmalloc.la
endif

