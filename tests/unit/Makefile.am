# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_builddir)
AM_CPPFLAGS = -g3 -ggdb -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer -pthread

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
# a benchmarker, not to be included in check.
UNIT_TESTS =																\
				test-size-alignments								\
				test-system-allocation							\
				test-region-insertion								\
				test-consecutive-pages-from-region	\
				test-region-allocation							\
				test-is-static-bin									\
				test-is-bin-addr										\
				test-bin-page-addr									\
				test-is-sticky-bin									\
				test-page-of-addr										\
				test-small-blocks										\
				test-large-blocks										\
				test-malloc-small-blocks						\
				test-malloc-large-blocks						\
				test-Realloc-small-blocks						\
				test-Realloc-large-blocks						\
				test-realloc-small-blocks						\
				test-realloc-large-blocks						\
				test-Realloc-size-small-blocks			\
				test-Realloc-size-large-blocks			\
				test-malloc-zero										\
				test-realloc-zero										\
				test-spec-bins-small-blocks					\
				test-spec-bins-large-blocks

BENCHMARKS =            

EXTRA_PROGRAMS = $(NON_COMPILING_TESTS) $(BENCHMARKS)

bin_PROGRAMS = $(UNIT_TESTS)

test_small_blocks_SOURCES =											\
   test-small-blocks.c

test_large_blocks_SOURCES =											\
   test-large-blocks.c

test_malloc_small_blocks_SOURCES =							\
   test-malloc-small-blocks.c

test_malloc_large_blocks_SOURCES =							\
   test-malloc-large-blocks.c

test_Realloc_small_blocks_SOURCES =							\
   test-Realloc-small-blocks.c

test_Realloc_large_blocks_SOURCES =							\
   test-Realloc-large-blocks.c

test_realloc_small_blocks_SOURCES =							\
   test-realloc-small-blocks.c

test_realloc_large_blocks_SOURCES =							\
 		test-realloc-large-blocks.c

test_malloc_zero_SOURCES =											\
		test-malloc-zero.c

test_realloc_zero_SOURCES =											\
		test-realloc-zero.c

test_Realloc_size_small_blocks_SOURCES =				\
   	test-Realloc-size-small-blocks.c

test_Realloc_size_large_blocks_SOURCES =				\
  	test-Realloc-size-large-blocks.c

test_spec_bins_small_blocks_SOURCES =						\
   	test-spec-bins-small-blocks.c

test_spec_bins_large_blocks_SOURCES =						\
    test-spec-bins-large-blocks.c

test_is_sticky_bin_SOURCES =										\
    test-is-sticky-bin.c

test_page_of_addr_SOURCES =											\
    test-page-of-addr.c

test_bin_page_addr_SOURCES =										\
    test-bin-page-addr.c

test_is_bin_addr_SOURCES =											\
    test-is-bin-addr.c

test_is_static_bin_SOURCES =										\
    test-is-static-bin.c

test_region_allocation_SOURCES =								\
    test-region-allocation.c

test_consecutive_pages_from_region_SOURCES =		\
    test-consecutive-pages-from-region.c

test_region_insertion_SOURCES =									\
    test-region-insertion.c

test_system_allocation_SOURCES =								\
    test-system-allocation.c

test_size_alignments_SOURCES =									\
		test-size-alignments.c

noinst_HEADERS =	
