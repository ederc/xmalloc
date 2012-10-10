# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_builddir)
AM_CPPFLAGS = -g3 -ggdb -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer -pthread

BENCHMARK_CXXFLAGS = -O2 -pthread

# all tests are done in the corresponding subdirectories
SUBDIRS = unit basic data

UNIT_DIR=unit
BASIC_DIR=basic
LDADD = $(top_builddir)/src/.libs/libxmalloc_debug.la

# Put an entry for your test-mycomponent.C here (or in one of the other test groups).  
# Don't forget to add a test_mycomponent_SOURCES entry below.
check:
	./run-all-tests.sh

# Once present, tests should remain present, being moved from one group to another.
# Note that among the available groups are NONCOMPILING_TESTS and FAILING_TESTS, which
# will be ignored by "make check" and can be temporary storage for problematic tests.
noinst_HEADERS =	
