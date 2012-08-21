# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_builddir)

#AM_CXXFLAGS = -g -Wall -DDEBUG -O0 -fomit-frame-pointer

SUBDIRS=

BASIC_HDRS =				\
	xDataStructures.h \
	xGlobals.h 				\
	xPage.h 					\
	xBin.h 						\
	xRegion.h 				\
	xSystem.h 				\
	xmalloc.h

pkginclude_HEADERS =			\
	$(BASIC_HDRS)

if ENABLE_DEBUG
lib_LTLIBRARIES=libxmalloc.la libxmalloc_debug.la
else
lib_LTLIBRARIES=libxmalloc.la
endif


libxmalloc_debug_la_CPPFLAGS= -g -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer $(INCLUDES)

SOURCES=		\
	xPage.c		\
	xBin.c		\
	xRegion.c	\
	xSystem.c	\
	xmalloc.c

libxmalloc_la_SOURCES=	\
	$(SOURCES)

libxmalloc_debug_la_SOURCES=	\
	$(SOURCES)

libxmalloc_la_LIBADD= 

libxmalloc_debug_la_LIBADD=
