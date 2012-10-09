# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_builddir)
AM_CPPFLAGS = -g3 -ggdb -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer

BENCHMARK_CXXFLAGS = -O2 -pthread

SUBDIRS =

LDADD = $(top_builddir)/src/.libs/libxmalloc_debug.la

test_malloc_test_LDFLAGS = -pthread
# Put an entry for your test-mycomponent.C here (or in one of the other test groups).  
# Don't forget to add a test_mycomponent_SOURCES entry below.
#
# Once present, tests should remain present, being moved from one group to another.
# Note that among the available groups are NONCOMPILING_TESTS and FAILING_TESTS, which
# will be ignored by "make check" and can be temporary storage for problematic tests.
UNIT_TESTS =																	\
				unit-test-small-blocks								\
				unit-test-large-blocks								\
				unit-test-malloc-small-blocks					\
				unit-test-malloc-large-blocks					\
				unit-test-Realloc-small-blocks				\
				unit-test-Realloc-large-blocks				\
				unit-test-realloc-small-blocks				\
				unit-test-realloc-large-blocks				\
				unit-test-Realloc-size-small-blocks		\
				unit-test-Realloc-size-large-blocks		\
				unit-test-Realloc-zero								\
				unit-test-spec-bins-small-blocks			\
				unit-test-spec-bins-large-blocks
# a benchmarker, not to be included in check.
BENCHMARKS =            

EXTRA_PROGRAMS = $(NON_COMPILING_TESTS) $(BENCHMARKS)

TESTS =                               		\
        $(UNIT_TESTS)

check_PROGRAMS = $(TESTS)

CLEANFILES = $(TESTS)

unit_test_small_blocks_SOURCES =								\
        unit-test-small-blocks.c

unit_test_large_blocks_SOURCES =								\
        unit-test-large-blocks.c

unit_test_malloc_small_blocks_SOURCES =					\
        unit-test-malloc-small-blocks.c

unit_test_malloc_large_blocks_SOURCES =					\
        unit-test-malloc-large-blocks.c

unit_test_Realloc_small_blocks_SOURCES =				\
        unit-test-Realloc-small-blocks.c

unit_test_Realloc_large_blocks_SOURCES =				\
        unit-test-Realloc-large-blocks.c

unit_test_realloc_small_blocks_SOURCES =				\
        unit-test-realloc-small-blocks.c

unit_test_realloc_large_blocks_SOURCES =				\
			unit-test-realloc-large-blocks.c

unit_test_Realloc_zero_SOURCES =								\
			unit-test-Realloc-zero.c

unit_test_Realloc_size_small_blocks_SOURCES =		\
        unit-test-Realloc-size-small-blocks.c

unit_test_Realloc_size_large_blocks_SOURCES =		\
        unit-test-Realloc-size-large-blocks.c

unit_test_spec_bins_small_blocks_SOURCES =			\
        unit-test-spec-bins-small-blocks.c

unit_test_spec_bins_large_blocks_SOURCES =			\
        unit-test-spec-bins-large-blocks.c

test_t3_SOURCES =																\
        test-t3.c

test_t4_SOURCES =																\
        test-t4.c

test_malloc_test_SOURCES =											\
        test-malloc_test.c

noinst_HEADERS =	
