# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_builddir)
AM_CPPFLAGS = -g3 -ggdb -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer

BENCHMARK_CXXFLAGS = -O2 -pthread

SUBDIRS = data

LDADD = $(top_builddir)/src/.libs/libxmalloc_debug.la

malloc_test_LDFLAGS = -pthread
# Put an entry for your test-mycomponent.C here (or in one of the other test groups).  
# Don't forget to add a test_mycomponent_SOURCES entry below.
#
# Once present, tests should remain present, being moved from one group to another.
# Note that among the available groups are NONCOMPILING_TESTS and FAILING_TESTS, which
# will be ignored by "make check" and can be temporary storage for problematic tests.
BASIC_TESTS =  						\
				small-block-alloc \
				large-block-alloc	\
				spec-bin					\
				t3								\
				t4								\
				malloc_test

# a benchmarker, not to be included in check.
BENCHMARKS =            

EXTRA_PROGRAMS = $(NON_COMPILING_TESTS) $(BENCHMARKS)

TESTS =                               \
        $(BASIC_TESTS)

check_PROGRAMS = $(TESTS)

CLEANFILES = $(TESTS)

small_block_alloc_SOURCES = \
        small-block-alloc.c           

large_block_alloc_SOURCES = \
        large-block-alloc.c           

spec_bin_SOURCES =      		\
        spec-bin.c

t3_SOURCES =                \
        t3.c

t4_SOURCES =                \
        t4.c

malloc_test_SOURCES =     	\
        malloc_test.c

noinst_HEADERS =	
