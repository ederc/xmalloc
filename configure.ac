# Copyright 2010 members of the LinBox group
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

AC_PREREQ(2.50)
AC_INIT(xmalloc,0.0.1,ederc@mathematik.uni-kl.de)
AM_INIT_AUTOMAKE([1.8 gnu no-dependencies])
AM_CONFIG_HEADER([include/xmalloc-config.h])
AX_PREFIX_CONFIG_H(include/xmalloc-config.h, __XMALLOC)
AC_PATH_PROG(RM, rm, $FALSE)
RM="$RM -f"

AC_CONFIG_MACRO_DIR([m4])

AM_MAINTAINER_MODE
AM_DEP_TRACK
AM_OUTPUT_DEPENDENCY_COMMANDS 

# Give a sane default for CFLAGS and CXXFLAGS
# The sane thing is to define the flags differenly in tests, examples, interfaces, etc.  -bds
#DEFAULT_CFLAGS="-O2 -Wall"

CFLAGS=${CFLAGS:-$DEFAULT_CFLAGS}
CXXFLAGS=${CXXFLAGS:-$DEFAULT_CFLAGS}

# work around to fix the backward compatibility issue of automake 1.10 with 1.9 (pb with MKDIR_P)
AC_SUBST([MKDIR_P])
AC_PROG_CC
AC_PROG_CXX
AC_STDC_HEADERS
#LT_INIT()
LT_INIT([disable-shared])

# check for mmap, ...
AC_FUNC_MMAP

if test "$ac_cv_func_mmap_fixed_mapped"  = "yes"; then
  AC_DEFINE([VALLOC],[xVallocMmap],[valloc uses mmap])
else
  AC_DEFINE([VALLOC],[xVallocNoMmap],[valloc does not use mmap])
fi

AC_ARG_ENABLE([debug],
              [AC_HELP_STRING([--disable-debug],
                              [Disable debug version])],
              [],
              [enable_debug=yes])


AM_CONDITIONAL(ENABLE_DEBUG, test "x$enable_debug" = xyes)

# Do not enable allocation from DSS by default.
AC_ARG_ENABLE([dss],
  [AS_HELP_STRING([--enable-dss], [Enable allocation from DSS])],
[if test "x$enable_dss" = "xno" ; then
  enable_dss="0"
else
  enable_dss="1"
fi
],
[enable_dss="0"]
)

# Check whether the BSD/SUSv1 sbrk() exists.  If not, disable DSS support.
AC_CHECK_FUNC([sbrk], [have_sbrk="1"], [have_sbrk="0"])
if test "x$have_sbrk" = "x1" ; then
  AC_DEFINE([HAVE_SBRK], [1],[sbrk available ?])
else
  enable_dss="0"
fi

if test "x$enable_dss" = "x1" ; then
  AC_DEFINE([DSS], [1], [dss available])
fi
AC_SUBST([enable_dss])

# Support the junk/zero filling option by default.
AC_ARG_ENABLE([fill],
  [AS_HELP_STRING([--disable-fill],
                  [Disable support for junk/zero filling, quarantine, and redzones])],
[if test "x$enable_fill" = "xno" ; then
  enable_fill="0"
else
  enable_fill="1"
fi
],
[enable_fill="1"]
)
if test "x$enable_fill" = "x1" ; then
  AC_DEFINE([FILL], [1],[junk / zero filling enabled])
fi
AC_SUBST([enable_fill])


# check assert setting
AC_HEADER_ASSERT

# Machine characteristics

AC_CHECK_SIZEOF(char, 8)
AC_CHECK_SIZEOF(short, 16)
AC_CHECK_SIZEOF(int, 32)
AC_CHECK_SIZEOF(void*, 32)
AC_CHECK_SIZEOF(long, 32)
AC_CHECK_SIZEOF(long long, 64)
AC_CHECK_SIZEOF(__int64, 64)
AC_CHECK_SIZEOF(__uint128_t, 128)
AC_CHECK_SIZEOF(__uint256_t, 256)

# check endianness of the architecture
AC_C_BIGENDIAN(
  [AC_DEFINE(HAVE_BIG_ENDIAN, 1, [Define that architecture uses big endian storage])],
  [AC_DEFINE(HAVE_LITTLE_ENDIAN, 1, [Define that architecture uses little endian storage])],[])

# Create some useful data types of fixed, known lengths

XMALLOC_SIZEOF_SYSTEM_PAGE=4096;
XMALLOC_PAGES_PER_REGION=512;
XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE=12;
XMALLOC_BIT_SIZEOF_CHAR=8;
XMALLOC_MIN_NUMBER_PAGES_PER_REGION=512;
XMALLOC_SIZEOF_ALIGNMENT=8;
XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE=7;
XMALLOC_LOG_SIZEOF_ALIGNMENT=3;
XMALLOC_SIZEOF_STRICT_ALIGNMENT=8;

# for xmalloc's specialized assert functionality
XMALLOC_STRINGIFICATION_OF_X="#x";
XMALLOC_ASSERT="xAssert(x,__FILE__,__LINE__)";

# maximal indexi resp. block size in xStaticBin array
# these values should depend on architecture, thus there needs to be implemented
# a more flexible choice of these values
XMALLOC_MAX_BIN_INDEX=22;
XMALLOC_MAX_SMALL_BLOCK_SIZE=1008;

# We hereby assume that a character is always one byte
XMALLOC_INT8="char";

case $ac_cv_sizeof_char in
  1)
     TWO_BYTES=2;
     FOUR_BYTES=4;
     EIGHT_BYTES=8;
     SIXTEEN_BYTES=16;
     THIRTY_TWO_BYTES=32;
     ;;
  8)
     TWO_BYTES=16;
     FOUR_BYTES=32;
     EIGHT_BYTES=64;
     SIXTEEN_BYTES=128;
     THIRTY_TWO_BYTES=256;
esac

case $TWO_BYTES in
  $ac_cv_sizeof_short)
     XMALLOC_INT16="short";
     ;;
  $ac_cv_sizeof_int)
     XMALLOC_INT16="int";
     ;;
esac

case $FOUR_BYTES in
  $ac_cv_sizeof_short)
     XMALLOC_INT32="short";
     ;;
  $ac_cv_sizeof_int)
     XMALLOC_INT32="int";
     ;;
  $ac_cv_sizeof_long)
     XMALLOC_INT32="long";
     XMALLOC_LOG_BIT_SIZEOF_LONG=5;
     XMALLOC_LOG_SIZEOF_LONG=2;
     ;;
esac

case $EIGHT_BYTES in
  $ac_cv_sizeof_short)
     XMALLOC_INT64="short";
     ;;
  $ac_cv_sizeof_int)
     XMALLOC_INT64="int";
     ;;
  $ac_cv_sizeof_long)
     XMALLOC_INT64="long";
     XMALLOC_LOG_BIT_SIZEOF_LONG=6;
     XMALLOC_LOG_SIZEOF_LONG=3;
     ;;
  $ac_cv_sizeof_long_long)
     XMALLOC_INT64="long long";
     ;;
  $ac_cv_sizeof___int64)
     XMALLOC_INT64="__int64";
     ;;
esac

case $SIXTEEN_BYTES in
  $ac_cv_sizeof___uint128_t)
     XMALLOC_UINT128="__uint128_t";
     ;;
esac

case $THIRTY_TWO_BYTES in
  $ac_cv_sizeof___uint256_t)
     XMALLOC_UINT256="__uint256_t";
     ;;
esac


AC_DEFINE_UNQUOTED(PAGES_PER_REGION, $XMALLOC_PAGES_PER_REGION, Depending on
    SIZEOF_LONG)
AC_DEFINE_UNQUOTED(MAX_SMALL_BLOCK_SIZE, $XMALLOC_MAX_SMALL_BLOCK_SIZE, Depending on
    SIZEOF_LONG)
AC_DEFINE_UNQUOTED(SIZEOF_SYSTEM_PAGE, $XMALLOC_SIZEOF_SYSTEM_PAGE, Size of
    system page)
AC_DEFINE_UNQUOTED(BIT_SIZEOF_CHAR, $XMALLOC_BIT_SIZEOF_CHAR, bitsize of char)
AC_DEFINE_UNQUOTED(BIT_SIZEOF_LONG,
    (__XMALLOC_BIT_SIZEOF_CHAR * __XMALLOC_SIZEOF_LONG),
    depends on bitsize of char and size of long)
AC_DEFINE_UNQUOTED(LOG_BIT_SIZEOF_SYSTEM_PAGE,
    $XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE, Log bit size of system page)
AC_DEFINE_UNQUOTED(LOG_BIT_SIZEOF_LONG, $XMALLOC_LOG_BIT_SIZEOF_LONG, Depending on
    SIZEOF_LONG)
AC_DEFINE_UNQUOTED(LOG_SIZEOF_LONG, $XMALLOC_LOG_SIZEOF_LONG, Depending on
    SIZEOF_LONG)
AC_DEFINE_UNQUOTED(SIZEOF_INDEX_PAGE_MINUS_ONE,
    ((__XMALLOC_SIZEOF_SYSTEM_PAGE << __XMALLOC_LOG_BIT_SIZEOF_LONG) - 1), Depending on
    LOG_BIT_SIZEOF_LONG)
AC_DEFINE_UNQUOTED(SIZEOF_PAGE_HEADER,
    (5*__XMALLOC_SIZEOF_VOIDP + __XMALLOC_SIZEOF_LONG), Depending on
    SIZEOF_LONG and SIZEOF_VOIDP)
AC_DEFINE_UNQUOTED(SIZEOF_PAGE,
    (__XMALLOC_SIZEOF_SYSTEM_PAGE - __XMALLOC_SIZEOF_PAGE_HEADER), Depending on
    SIZEOF_SYSTEM_PAGE and SIZEOF_PAGE_HEADER)
AC_DEFINE_UNQUOTED(INDEX_PAGE_SHIFT,
    (__XMALLOC_LOG_BIT_SIZEOF_LONG + __XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE), Depending on
    LOG_BIT_SIZEOF_LONG)
AC_DEFINE_UNQUOTED(MIN_NUMBER_PAGES_PER_REGION,
    $XMALLOC_MIN_NUMBER_PAGES_PER_REGION, default minimal value of the number of
    pages allocated for a new region)
AC_DEFINE_UNQUOTED(SIZEOF_ALIGNMENT,
    $XMALLOC_SIZEOF_ALIGNMENT, bitsize of alignment of memory allocated by
    xmalloc)
AC_DEFINE_UNQUOTED(SIZEOF_ALIGNMENT_MINUS_ONE,
    $XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE, bitsize of alignment of memory allocated by
    xmalloc)
AC_DEFINE_UNQUOTED(LOG_SIZEOF_ALIGNMENT,
    $XMALLOC_LOG_SIZEOF_ALIGNMENT, log bitsize of alignment of memory allocated by
    xmalloc)
AC_DEFINE_UNQUOTED(SIZEOF_STRICT_ALIGNMENT,
    $XMALLOC_SIZEOF_STRICT_ALIGNMENT, size of strict alignment of memory allocated by
    xmalloc)
AC_DEFINE_UNQUOTED(SIZEOF_VOIDP_MINUS_ONE,
    (__XMALLOC_SIZEOF_VOIDP - 1), depending on sizeof(void*))
AC_DEFINE_UNQUOTED(MAX_BIN_INDEX,
    $XMALLOC_MAX_BIN_INDEX, depending on the chosen size classes and their
    subdivision)
AC_DEFINE_UNQUOTED(STRINGIFICATION(x),
    $XMALLOC_STRINGIFICATION_OF_X, macro stringification mainly used by xassert)
AC_DEFINE_UNQUOTED(ASSERT(x),
    $XMALLOC_ASSERT, it is a macro in order to print out the correct file and
    line)
AC_DEFINE_UNQUOTED(INT8, $XMALLOC_INT8, Canonical 8-bit data type)
AC_DEFINE_UNQUOTED(INT16, $XMALLOC_INT16, Canonical 16-bit data type)
AC_DEFINE_UNQUOTED(INT32, $XMALLOC_INT32, Canonical 32-bit data type)
AC_DEFINE_UNQUOTED(INT64, $XMALLOC_INT64, Canonical 64-bit data type)
if test "x$XMALLOC_UINT128" != "x"; then
  AC_DEFINE_UNQUOTED(UINT128, $XMALLOC_UINT128, Canonical 128-bit data type)
fi
if test "x$XMALLOC_UINT256" != "x"; then
  AC_DEFINE_UNQUOTED(UINT256, $XMALLOC_UINT256, Canonical 256-bit data type)
fi
AC_DEFINE_UNQUOTED(NEXT(addr), *((void**) addr), Jump to next entry)
AC_DEFINE_UNQUOTED(MAX(a,b), ((a) > (b) ? (a) : (b)), maximum of two comparable
    values)
AC_DEFINE_UNQUOTED(MIN(a,b), ((a) > (b) ? (b) : (a)), minimum of two comparable
    values)

# Feature checks
# LB_MISC
# LB_DRIVER

AC_LANG_CPLUSPLUS
# LB_CHECK_GMP

AC_PATH_PROG(XMLTO,xmlto,"no")

if test "x$XMLTO" = "xno" ; then
  echo "Note: xmlto not found. Cannot rebuild documentation."
  XMLTO=
fi

AC_PATH_PROG(DOXYGEN,doxygen,"no")

if test "x$DOXYGEN" = "xno" ; then
  echo "Note: doxygen not found. Cannot rebuild reference-documentation."
  DOXYGEN=
fi

AM_CONDITIONAL(BUILD_DOCS,[test x$XMLTO != x])
AM_CONDITIONAL(BUILD_REFS,[test x$DOXYGEN != x])

# this is bogus so far as I can tell.  -bds
AM_CXXFLAGS="${CXXFLAGS}"
AC_SUBST([AM_CXXFLAGS])


AC_OUTPUT([
Makefile
xmalloc-config
src/Makefile
tests/Makefile
tests/unit-tests/Makefile
tests/data/Makefile
m4/Makefile
doc/Makefile
])
