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
	globals.c	\
	page.c		\
	bin.c			\
	region.c	\
	system.c	\
	xmalloc.c

pkginclude_HEADERS =	\
	$(BASIC_HDRS)

if ENABLE_DEBUG
lib_LTLIBRARIES=libxmalloc.la libxmalloc_debug.la
libxmalloc_debug_la_CPPFLAGS= -g3 -ggdb -Wall -pthread -D__XMALLOC_DEBUG -DDEBUG -O0 -fomit-frame-pointer $(INCLUDES)
libxmalloc_debug_la_SOURCES=	\
	$(SOURCES)
libxmalloc_debug_la_LIBADD=
else
lib_LTLIBRARIES=libxmalloc.la
endif

libxmalloc_la_CPPFLAGS= $(AM_CXXFLAGS) -g -Wall -pthread -D__XMALLOC_NDEBUG -DNDEBUG -O3 -fomit-frame-pointer $(INCLUDES)

libxmalloc_la_SOURCES=	\
	$(SOURCES)

libxmalloc_la_LIBADD= 
