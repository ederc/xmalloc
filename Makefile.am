# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

AUTOMAKE_OPTIONS=color-tests

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_builddir)

SUBDIRS= . m4 src doc tests

OBJEXT=".lo .o"
ACLOCAL_AMFLAGS=-I m4

bin_SCRIPTS=xmalloc-config

EXTRA_DIST=PROJECTS

CLEANFILES=				\
	tags						\
	*~

distclean-local:
	rm -rf autom4te.cache

DISTCLEANFILES= 									\
	_configs.sed										\
	config.sub											\
	config.guess										\
	configure.in										\
	configure												\
	Makefile.in											\
	xmalloc-config xmalloc-config~	\
	include/xmalloc-config.h*				\
	include/stamp-h1a         			\
	doc/index.html									\
	*~

doc:
	(cd doc; make)

ctags:
	ctags -R *

all-am: ctags
