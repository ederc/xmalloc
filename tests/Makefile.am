# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I$(top_builddir)
AM_CXXFLAGS = -g -Wall -DDEBUG -O0 -fomit-frame-pointer

BENCHMARK_CXXFLAGS = -O2

SUBDIRS = data

LDADD = $(top_builddir)/src/libxmalloc.la

# Put an entry for your test-mycomponent.C here (or in one of the other test groups).  
# Don't forget to add a test_mycomponent_SOURCES entry below.
#
# Once present, tests should remain present, being moved from one group to another.
# Note that among the available groups are NONCOMPILING_TESTS and FAILING_TESTS, which
# will be ignored by "make check" and can be temporary storage for problematic tests.
BASIC_TESTS =  \
				t1			\
				t2			\
				t3			\
				t4			\
				t5

# a benchmarker, not to be included in check.
BENCHMARKS =            

EXTRA_PROGRAMS = $(NON_COMPILING_TESTS) $(BENCHMARKS)

TESTS =                               \
        $(BASIC_TESTS)

check_PROGRAMS = $(TESTS)

CLEANFILES = $(TESTS)

t1_SOURCES =                \
        t1.c           

t2_SOURCES =                \
        t2.c           

t3_SOURCES =                \
        t3.c           

t4_SOURCES =                \
        t4.c           

t5_SOURCES =                \
        t5.c           

noinst_HEADERS =	
