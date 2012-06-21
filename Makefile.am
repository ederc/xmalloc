# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

SUBDIRS=src m4 tests doc

ACLOCAL_AMFLAGS=-I m4

bin_SCRIPTS=xmalloc-config

DISTCLEANFILES=_configs.sed

EXTRA_DIST=PROJECTS

clean-local:
	rm -f xmalloc-config xmalloc-config~
	rm -f include/xmalloc-config.h*
	rm -f include/stamp-h1
