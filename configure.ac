# Copyright 2010 members of the LinBox group
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

dnl X_CFLAGS_APPEND(cflag)
AC_DEFUN([X_CFLAGS_APPEND],
[
AC_MSG_CHECKING([whether compiler supports $1])
TCFLAGS="${CFLAGS}"
if test "x${CFLAGS}" = "x" ; then
  CFLAGS="$1"
else
  CFLAGS="${CFLAGS} $1"
fi
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
[[
]], [[
    return 0;
]])],
              AC_MSG_RESULT([yes]),
              AC_MSG_RESULT([no])
              [CFLAGS="${TCFLAGS}"]
)
])

dnl X_COMPILABLE(label, hcode, mcode, rvar)
dnl
dnl Use AC_LINK_IFELSE() rather than AC_COMPILE_IFELSE() so that linker errors
dnl cause failure.
AC_DEFUN([X_COMPILABLE],
[
AC_CACHE_CHECK([whether $1 is compilable],
               [$4],
               [AC_LINK_IFELSE([AC_LANG_PROGRAM([$2],
                                                [$3])],
                               [$4=yes],
                               [$4=no])])
])


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


dnl If CFLAGS isn't defined, set CFLAGS to something reasonable.  Otherwise,
dnl just prevent autoconf from molesting CFLAGS.
CFLAGS=$CFLAGS
AC_PROG_CC
if test "x$GCC" != "xyes" ; then
  AC_CACHE_CHECK([whether compiler is MSVC],
                 [je_cv_msvc],
                 [AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
                                                     [
#ifndef _MSC_VER
  int fail[-1];
#endif
])],
                               [je_cv_msvc=yes],
                               [je_cv_msvc=no])])
fi

if test "x$CFLAGS" = "x" ; then
  no_CFLAGS="yes"
  if test "x$GCC" = "xyes" ; then
    X_CFLAGS_APPEND([-std=gnu99])
    X_CFLAGS_APPEND([-Wall])
    X_CFLAGS_APPEND([-pipe])
    X_CFLAGS_APPEND([-g3])
  elif test "x$je_cv_msvc" = "xyes" ; then
    CC="$CC -nologo"
    X_CFLAGS_APPEND([-Zi])
    X_CFLAGS_APPEND([-MT])
    X_CFLAGS_APPEND([-W3])
    CPPFLAGS="$CPPFLAGS -I${srcroot}/include/msvc_compat"
  fi
fi
dnl Append EXTRA_CFLAGS to CFLAGS, if defined.
if test "x$EXTRA_CFLAGS" != "x" ; then
  X_CFLAGS_APPEND([$EXTRA_CFLAGS])
fi
AC_PROG_CPP


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

dnl Only optimize if not debugging.
if test "x$no_CFLAGS" = "xyes" ; then
  dnl Make sure that an optimization flag was not specified in EXTRA_CFLAGS.
  optimize="no"
  echo "$EXTRA_CFLAGS" | grep "\-O" >/dev/null || optimize="yes"
  if test "x${optimize}" = "xyes" ; then
    if test "x$GCC" = "xyes" ; then
      X_CFLAGS_APPEND([-O3])
      X_CFLAGS_APPEND([-funroll-loops])
    elif test "x$je_cv_msvc" = "xyes" ; then
      X_CFLAGS_APPEND([-O2])
    else
      X_CFLAGS_APPEND([-O])
    fi
  fi
fi

dnl Do not silence irrelevant compiler warnings by default, since enabling this
dnl option incurs a performance penalty.
AC_ARG_ENABLE([cc-silence],
  [AS_HELP_STRING([--enable-cc-silence],
                  [Silence irrelevant compiler warnings])],
[if test "x$enable_cc_silence" = "xno" ; then
  enable_cc_silence="0"
else
  enable_cc_silence="1"
fi
],
[enable_cc_silence="0"]
)
if test "x$enable_cc_silence" = "x1" ; then
  AC_DEFINE([CC_SILENCE], [ ], "not silencing irrelevant compiler warnings by
      default, since enabling this option incurs a performance penalty")
fi

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

dnl ===========================================================================
dnl CPU-specific settings.
CPU_SPINWAIT=""
case "${host_cpu}" in
  i[[345]]86)
	;;
  i686)
	X_COMPILABLE([__asm__], [], [[__asm__ volatile("pause"); return 0;]],
	              [je_cv_asm])
	if test "x${je_cv_asm}" = "xyes" ; then
	    CPU_SPINWAIT='__asm__ volatile("pause")'
	fi
	;;
  x86_64)
	X_COMPILABLE([__asm__ syntax], [],
	              [[__asm__ volatile("pause"); return 0;]], [je_cv_asm])
	if test "x${je_cv_asm}" = "xyes" ; then
	    CPU_SPINWAIT='__asm__ volatile("pause")'
	fi
	;;
  *)
	;;
esac
AC_DEFINE_UNQUOTED([CPU_SPINWAIT], [$CPU_SPINWAIT], "spinwait macro for xmalloc")

LD_PRELOAD_VAR="LD_PRELOAD"
so="so"
importlib="${so}"
o="$ac_objext"
a="a"
exe="$ac_exeext"
libprefix="lib"
DSO_LDFLAGS='-shared -Wl,-soname,$(@F)'
RPATH='-Wl,-rpath,$(1)'
SOREV="${so}.${rev}"
PIC_CFLAGS='-fPIC -DPIC'
CTARGET='-o $@'
LDTARGET='-o $@'
EXTRA_LDFLAGS=
MKLIB='ar crus $@'
CC_MM=1

dnl Platform-specific settings.  abi and RPATH can probably be determined
dnl programmatically, but doing so is error-prone, which makes it generally
dnl not worth the trouble.
dnl
dnl Define cpp macros in CPPFLAGS, rather than doing AC_DEFINE(macro), since the
dnl definitions need to be seen before any headers are included, which is a pain
dnl to make happen otherwise.
default_munmap="1"
case "${host}" in
  *-*-darwin*)
	CFLAGS="$CFLAGS"
	abi="macho"
	AC_DEFINE([PURGE_MADVISE_FREE], [ ],"")
	RPATH=""
	LD_PRELOAD_VAR="DYLD_INSERT_LIBRARIES"
	so="dylib"
	importlib="${so}"
	force_tls="0"
	DSO_LDFLAGS='-shared -Wl,-dylib_install_name,$(@F)'
	SOREV="${rev}.${so}"
	;;
  *-*-freebsd*)
	CFLAGS="$CFLAGS"
	abi="elf"
	AC_DEFINE([PURGE_MADVISE_FREE], [ ],"")
	force_lazy_lock="1"
	;;
  *-*-linux*)
	CFLAGS="$CFLAGS"
	CPPFLAGS="$CPPFLAGS -D_GNU_SOURCE"
	abi="elf"
	AC_DEFINE([PURGE_MADVISE_DONTNEED], [ ],"")
	AC_DEFINE([THREADED_INIT], [ ],"")
	default_munmap="0"
	;;
  *-*-netbsd*)
	AC_MSG_CHECKING([ABI])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
[[#ifdef __ELF__
/* ELF */
#else
#error aout
#endif
]])],
                          [CFLAGS="$CFLAGS"; abi="elf"],
                          [abi="aout"])
	AC_MSG_RESULT([$abi])
	AC_DEFINE([PURGE_MADVISE_FREE], [ ],"")
	;;
  *-*-solaris2*)
	CFLAGS="$CFLAGS"
	abi="elf"
	RPATH='-Wl,-R,$(1)'
	dnl Solaris needs this for sigwait().
	CPPFLAGS="$CPPFLAGS -D_POSIX_PTHREAD_SEMANTICS"
	LIBS="$LIBS -lposix4 -lsocket -lnsl"
	;;
  *-ibm-aix*)
	if "$LG_SIZEOF_PTR" = "8"; then
	  dnl 64bit AIX
	  LD_PRELOAD_VAR="LDR_PRELOAD64"
	else
	  dnl 32bit AIX
	  LD_PRELOAD_VAR="LDR_PRELOAD"
	fi
	abi="xcoff"
	;;
  *-*-mingw*)
	abi="pecoff"
	force_tls="0"
	RPATH=""
	so="dll"
	if test "x$je_cv_msvc" = "xyes" ; then
	  importlib="lib"
	  DSO_LDFLAGS="-LD"
	  EXTRA_LDFLAGS="-link -DEBUG"
	  CTARGET='-Fo$@'
	  LDTARGET='-Fe$@'
	  MKLIB='lib -nologo -out:$@'
	  CC_MM=
        else
	  importlib="${so}"
	  DSO_LDFLAGS="-shared"
	fi
	a="lib"
	libprefix=""
	SOREV="${so}"
	PIC_CFLAGS=""
	;;
  *)
	AC_MSG_RESULT([Unsupported operating system: ${host}])
	abi="elf"
	;;
esac
AC_SUBST([abi])
AC_SUBST([RPATH])
AC_SUBST([LD_PRELOAD_VAR])
AC_SUBST([so])
AC_SUBST([importlib])
AC_SUBST([o])
AC_SUBST([a])
AC_SUBST([exe])
AC_SUBST([libprefix])
AC_SUBST([DSO_LDFLAGS])
AC_SUBST([EXTRA_LDFLAGS])
AC_SUBST([SOREV])
AC_SUBST([PIC_CFLAGS])
AC_SUBST([CTARGET])
AC_SUBST([LDTARGET])
AC_SUBST([MKLIB])
AC_SUBST([CC_MM])

if test "x$abi" != "xpecoff"; then
  dnl Heap profiling uses the log(3) function.
  LIBS="$LIBS -lm"
fi

X_COMPILABLE([__attribute__ syntax],
              [static __attribute__((unused)) void foo(void){}],
              [],
              [je_cv_attribute])
if test "x${je_cv_attribute}" = "xyes" ; then
  AC_DEFINE([HAVE_ATTR], [ ],"check if __attribute__ syntax is supported")
  if test "x${GCC}" = "xyes" -a "x${abi}" = "xelf"; then
    X_CFLAGS_APPEND([-fvisibility=hidden])
  fi
fi

dnl Check for tls_model attribute support (clang 3.0 still lacks support).
SAVED_CFLAGS="${CFLAGS}"
X_CFLAGS_APPEND([-Werror])
X_COMPILABLE([tls_model attribute], [],
              [static __thread int
               __attribute__((tls_model("initial-exec"))) foo;
               foo = 0;],
              [x_cv_tls_model])
CFLAGS="${SAVED_CFLAGS}"
if test "x${x_cv_tls_model}" = "xyes" ; then
  AC_DEFINE([TLS_MODEL],
            [__attribute__((tls_model("initial-exec")))], "model of tls
            attribute support ( clang 3.0 still lacks support )")
else
  AC_DEFINE([TLS_MODEL], [ ], "model of tls attribute support ( clang 3.0 still
  lacks support )")
fi

dnl Support optional additions to rpath.
AC_ARG_WITH([rpath],
  [AS_HELP_STRING([--with-rpath=<rpath>], [Colon-separated rpath (ELF systems only)])],
if test "x$with_rpath" = "xno" ; then
  RPATH_EXTRA=
else
  RPATH_EXTRA="`echo $with_rpath | tr \":\" \" \"`"
fi,
  RPATH_EXTRA=
)
AC_SUBST([RPATH_EXTRA])

dnl ============================================================================
dnl Configure pthreads.

if test "x$abi" != "xpecoff" ; then
  AC_CHECK_HEADERS([pthread.h], , [AC_MSG_ERROR([pthread.h is missing])])
  dnl Some systems may embed pthreads functionality in libc; check for libpthread
  dnl first, but try libc too before failing.
  AC_CHECK_LIB([pthread], [pthread_create], [LIBS="$LIBS -lpthread"],
               [AC_SEARCH_LIBS([pthread_create], , ,
                               AC_MSG_ERROR([libpthread is missing]))])
fi

CPPFLAGS="$CPPFLAGS -D_REENTRANT"

dnl Check whether the BSD-specific _malloc_thread_cleanup() exists.  If so, use
dnl it rather than pthreads TSD cleanup functions to support cleanup during
dnl thread exit, in order to avoid pthreads library recursion during
dnl bootstrapping.
AC_CHECK_FUNC([_malloc_thread_cleanup],
              [have__malloc_thread_cleanup="1"],
              [have__malloc_thread_cleanup="0"]
             )
if test "x$have__malloc_thread_cleanup" = "x1" ; then
  AC_DEFINE([THREAD_CLEANUP], [ ], "thread cleanup for xmalloc")
  force_tls="1"
fi

dnl Check whether the BSD-specific _pthread_mutex_init_calloc_cb() exists.  If
dnl so, mutex initialization causes allocation, and we need to implement this
dnl callback function in order to prevent recursive allocation.
AC_CHECK_FUNC([_pthread_mutex_init_calloc_cb],
              [have__pthread_mutex_init_calloc_cb="1"],
              [have__pthread_mutex_init_calloc_cb="0"]
             )
if test "x$have__pthread_mutex_init_calloc_cb" = "x1" ; then
  AC_DEFINE([MUTEX_INIT_CB], [], "checks if
      BSD-specific _pthread_mutex_init_calloc_cb() exists")
fi

# Disable lazy locking by default.
AC_ARG_ENABLE([lazy_lock],
  [AS_HELP_STRING([--enable-lazy-lock],
  [Enable lazy locking (only lock when multi-threaded)])],
[if test "x$enable_lazy_lock" = "xno" ; then
  enable_lazy_lock="0"
else
  enable_lazy_lock="1"
fi
],
[enable_lazy_lock="0"]
)
if test "x$enable_lazy_lock" = "x0" -a "x${force_lazy_lock}" = "x1" ; then
  AC_MSG_RESULT([Forcing lazy-lock to avoid allocator/threading bootstrap issues])
  enable_lazy_lock="1"
fi
if test "x$enable_lazy_lock" = "x1" ; then
  if test "x$abi" != "xpecoff" ; then
    AC_CHECK_HEADERS([dlfcn.h], , [AC_MSG_ERROR([dlfcn.h is missing])])
    AC_CHECK_FUNC([dlsym], [],
      [AC_CHECK_LIB([dl], [dlsym], [LIBS="$LIBS -ldl"],
                    [AC_MSG_ERROR([libdl is missing])])
      ])
  fi
  AC_DEFINE([LAZY_LOCK], [ ], "Macro for lazy locking: Lock only if
      multi-threaded")
fi
AC_SUBST([enable_lazy_lock])

AC_ARG_ENABLE([tls],
  [AS_HELP_STRING([--disable-tls], [Disable thread-local storage (__thread keyword)])],
if test "x$enable_tls" = "xno" ; then
  enable_tls="0"
else
  enable_tls="1"
fi
,
enable_tls="1"
)
if test "x${enable_tls}" = "x0" -a "x${force_tls}" = "x1" ; then
  AC_MSG_RESULT([Forcing TLS to avoid allocator/threading bootstrap issues])
  enable_tls="1"
fi
if test "x${enable_tls}" = "x1" -a "x${force_tls}" = "x0" ; then
  AC_MSG_RESULT([Forcing no TLS to avoid allocator/threading bootstrap issues])
  enable_tls="0"
fi
if test "x${enable_tls}" = "x1" ; then
AC_MSG_CHECKING([for TLS])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
[[
    __thread int x;
]], [[
    x = 42;

    return 0;
]])],
              AC_MSG_RESULT([yes]),
              AC_MSG_RESULT([no])
              enable_tls="0")
fi
AC_SUBST([enable_tls])
if test "x${enable_tls}" = "x1" ; then
  AC_DEFINE_UNQUOTED([TLS], [ ], "Macro for using thread-local storage in
      xmalloc.")
elif test "x${force_tls}" = "x1" ; then
  AC_MSG_ERROR([Failed to configure TLS, which is mandatory for correct function])
fi

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
AM_CFLAGS="${CFLAGS}"
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_CFLAGS])


AC_OUTPUT([
Makefile
xmalloc-config
src/Makefile
tests/Makefile
tests/basic/Makefile
tests/data/Makefile
tests/unit/Makefile
m4/Makefile
doc/Makefile
])
