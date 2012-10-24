# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_builddir)
AM_CPPFLAGS = -g3 -ggdb -Wall -D__XMALLOC_DEBUG -O0 -fomit-frame-pointer -pthread

BENCHMARK_CXXFLAGS = -O2 -pthread

SUBDIRS =

if ENABLE_DEBUG
LDADD = $(top_builddir)/src/.libs/libxmalloc_debug.la
else
LDADD = $(top_builddir)/src/.libs/libxmalloc.la
endif

# Put an entry for your test-mycomponent.C here (or in one of the other test groups).  
# Don't forget to add a test_mycomponent_SOURCES entry below.
#
# Once present, tests should remain present, being moved from one group to another.
# Note that among the available groups are NONCOMPILING_TESTS and FAILING_TESTS, which
# will be ignored by "make check" and can be temporary storage for problematic tests.
# a benchmarker, not to be included in check.
UNIT_TESTS =																\
				test-xPrintInfo											\
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
				test-xMalloc0												\
				test-xMalloc												\
				test-xmalloc												\
				test-xRegisterPagesInRegion					\
				test-xDoRealloc											\
				test-xRealloc0											\
				test-xRealloc												\
				test-xrealloc												\
				test-xreallocSize										\
				test-xReallocSize										\
				test-xrealloc0Size									\
				test-xRealloc0Size									\
				test-xReallocLarge									\
				test-xRealloc0Large

BENCHMARKS =            

EXTRA_PROGRAMS = $(NON_COMPILING_TESTS) $(BENCHMARKS)

check_PROGRAMS = $(UNIT_TESTS)

test_xMalloc0_SOURCES =													\
		test-xMalloc0.c

test_xRealloc0_SOURCES =												\
		test-xRealloc0.c

test_xMalloc_SOURCES =													\
		test-xMalloc.c

test_xmalloc_SOURCES =													\
		test-xmalloc.c

test_xDoRealloc_SOURCES =												\
		test-xDoRealloc.c

test_xRealloc_SOURCES =													\
		test-xRealloc.c

test_xreallocSize_SOURCES =											\
		test-xreallocSize.c

test_xReallocSize_SOURCES =											\
		test-xReallocSize.c

test_xrealloc0Size_SOURCES =										\
		test-xrealloc0Size.c

test_xRealloc0Size_SOURCES =										\
		test-xRealloc0Size.c

test_xReallocLarge_SOURCES =										\
		test-xReallocLarge.c

test_xRealloc0Large_SOURCES =										\
		test-xRealloc0Large.c

test_xrealloc_SOURCES =													\
		test-xRealloc.c

test_xIsStickyBin_SOURCES =											\
    test-xIsStickyBin.c

test_xGetPageOfAddr_SOURCES =										\
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

test_xRegisterPagesInRegion_SOURCES =						\
		test-xRegisterPagesInRegion.c

test_xPrintInfo_SOURCES =												\
		test-xPrintInfo.c

noinst_HEADERS =	
