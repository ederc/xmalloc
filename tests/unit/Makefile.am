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
				test-xGetSpecBin										\
				test-xAreAddressesOnSamePage				\
				test-xAllocFromNonEmptyPage					\
				test-xAddressIsAligned							\
				test-xAlignSize											\
				test-xAllocFromSystem								\
				test-xReallocSizeFromSystem					\
				test-xVallocFromSystem							\
				test-xTakeOutRegion									\
				test-xInsertRegionAfter							\
				test-xInsertRegionBefore						\
				test-xPageIndexFault								\
				test-xAllocSmallBigBlockPagesForBin	\
				test-xAllocNewRegion								\
				test-xIsStaticBin										\
				test-xIsBinAddr											\
				test-xGetBinPageOfPageAddr	  			\
				test-xIsStickyBin										\
				test-xGetPageOfAddr									\
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
				test-xMalloc0												\
				test-xMalloc												\
				test-xmalloc												\
				test-xRealloc0											\
				test-xRealloc												\
				test-xrealloc												\
				test-xReallocSize										\
				test-xRealloc0Size									\
				test-xReallocLarge									\
				test-xRealloc0Large									\
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

test_xMalloc0_SOURCES =													\
		test-xMalloc0.c

test_xRealloc0_SOURCES =												\
		test-xRealloc0.c

test_xMalloc_SOURCES =													\
		test-xMalloc.c

test_xmalloc_SOURCES =													\
		test-xmalloc.c

test_xRealloc_SOURCES =													\
		test-xRealloc.c

test_xReallocSize_SOURCES =											\
		test-xReallocSize.c

test_xRealloc0Size_SOURCES =										\
		test-xRealloc0Size.c

test_xReallocLarge_SOURCES =										\
		test-xReallocLarge.c

test_xRealloc0Large_SOURCES =										\
		test-xRealloc0Large.c

test_xrealloc_SOURCES =													\
		test-xRealloc.c

test_Realloc_size_small_blocks_SOURCES =				\
   	test-Realloc-size-small-blocks.c

test_Realloc_size_large_blocks_SOURCES =				\
  	test-Realloc-size-large-blocks.c

test_spec_bins_small_blocks_SOURCES =						\
   	test-spec-bins-small-blocks.c

test_spec_bins_large_blocks_SOURCES =						\
    test-spec-bins-large-blocks.c

test_xIsStickyBin_SOURCES =											\
    test-xIsStickyBin.c

test_xGetPageOfAddr__SOURCES =									\
    test-xGetPageOfAddr.c

test_xGetBinPageOfPageAddr_SOURCES =						\
    test-xGetBinPageOfPageAddr.c

test_xIsBinAddr_SOURCES =												\
    test-xIsBinAddr.c

test_xIsStaticBin_SOURCES =											\
    test-xIsStaticBin.c

test_xAllocNewRegion_SOURCES =									\
		test-xAllocNewRegion.c

test_xAllocSmallBigBlockPagesForBin_SOURCES =		\
    test-xAllocSmallBigBlockPagesForBin.c

test_xInsertRegionAfter_SOURCES =								\
    test-xInsertRegionAfter.c

test_xInsertRegionBefore_SOURCES =							\
    test-xInsertRegionBefore.c

test_xTakeOutRegion_SOURCES =										\
    test-xTakeOutRegion.c

test_xAllocFromSystem_SOURCES =									\
    test-xAllocFromSystem.c

test_xReallocSizeFromSystem_SOURCES =						\
    test-xReallocSizeFromSystem.c

test_xVallocFromSystem_SOURCES =								\
    test-xVallocFromSystem.c

test_xAlignSize_SOURCES =												\
		test-xAlignSize.c

test_xAddressIsAligned_SOURCES =								\
		test-xAddressIsAligned.c

test_xAllocFromNonEmptyPage_SOURCES =						\
		test-xAllocFromNonEmptyPage.c

test_xAreAddressesOnSamePage_SOURCES =					\
		test-xAreAddressesOnSamePage.c

test_xPageIndexFault_SOURCES =									\
		test-xPageIndexFault.c

test_xGetSpecBin_SOURCES =											\
		test-xGetSpecBin.c

noinst_HEADERS =	
