# Copyright 2010 members of the LinBox group
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

AC_PREREQ(2.50)
AC_INIT(xmalloc,0.0.1,xmalloc@googlegroups.com) 
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
LT_INIT([disable-shared])

# Machine characteristics

AC_CHECK_SIZEOF(char, 8)
AC_CHECK_SIZEOF(short, 16)
AC_CHECK_SIZEOF(int, 32)
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
  XMALLOC_PAGES_PER_REGION="4080";
  XMALLOC_MAX_SMALL_BLOCK_SIZE="1016";
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
    XMALLOC_PAGES_PER_REGION="4068";
    XMALLOC_MAX_SMALL_BLOCK_SIZE="1008";
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
#CXXFLAGS="${GMP_CFLAGS} ${NTL_CFLAGS} ${GIVARO_CFLAGS} ${SACLIB_CFLAGS} ${CXXFLAGS}"
#AC_SUBST(CXXFLAGS)

AC_OUTPUT([
Makefile
xmalloc-config
src/Makefile
tests/Makefile
tests/data/Makefile
m4/Makefile
doc/Makefile
])
