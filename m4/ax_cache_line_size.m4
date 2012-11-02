# SYNOPSIS
#
#   AX_CACHE_LINE_SIZE
#
# DESCRIPTION
#
#   Find the length of a cache line.
#
#   This macro depends on AC_PROG_SED, AC_PROG_CC.
#
# LAST MODIFICATION
#
#   2012-11-02
#
# COPYLEFT
#
#   Copyright (c) 2009,2010 Christian Eder <ederc@mathematik.uni-kl.de>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_CACHE_LINE_SIZE],
[ AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_SED])

  AC_LANG_PUSH([C])
  AC_CACHE_CHECK(for cache line size, ax_cv_cache_line_size,
  [AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <stddef.h>

#if defined(__APPLE__) // Mac OS X
#include <sys/sysctl.h>
size_t xCacheLineSize() {
  size_t line_size = 0;
  size_t sizeof_line_size = sizeof(line_size);
  sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, 0, 0);
  return line_size;
}

#elif defined(_WIN32) // Windows
#include <stdlib.h>
#include <windows.h>
size_t xCacheLineSize() {
  size_t line_size = 0;
  DWORD buffer_size = 0;
  DWORD i = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;
    
  GetLogicalProcessorInformation(0, &buffer_size);
  buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
  if (buffer == 0)
    return 64; // default value
  GetLogicalProcessorInformation(&buffer[0], &buffer_size);
    
  for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
    if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
      line_size = buffer[i].Cache.LineSize;
      break;
    }
  }
  free(buffer);
  return line_size;
}
    
#elif defined(linux) // Linux
#include <stdio.h>
size_t xCacheLineSize() {
  FILE * p = 0;
  p = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
  unsigned int i = 0;
  if (p) {
    fscanf(p, "%d", &i);
    fclose(p);
  }
  return i;
}
#else
size_t xCacheLineSize() {
  return 64;
}
#endif

unsigned int xCacheLineSizeLog(size_t line) {
  unsigned int i = 0;
  while (line > 1) {
    line = line >> 1;
    i++;
  }
  return i;
}
  ]],
  [[
  FILE *f;
  //printf("\n");
  size_t line = xCacheLineSize();
  size_t lineLog = xCacheLineSizeLog(line);
  f = fopen("conftest_cache_line_size", "w"); if (!f) return 1;
  fprintf(f,"%lu:%lu\n",(unsigned long)(line),(unsigned long)(lineLog));
  fclose(f);
  return 0;
   ]])],
    [ax_cv_cache_line_size=`cat conftest_cache_line_size`; rm -f conftest_cache_line_size],
    [ax_cv_cache_line_size=64:6; rm -f conftest_cache_line_size],
    [ax_cv_cache_line_size=64:6])])
  AC_LANG_POP([C])
  AC_MSG_CHECKING(the cache line size)
  ax_cache_line_size=`echo $ax_cv_cache_line_size | $SED 's/\:.*//g'`
  AC_MSG_RESULT( $ax_cache_line_size Bytes)
  AC_MSG_CHECKING(the cache line log size)
  ax_cache_line_log_size=`echo $ax_cv_cache_line_size | $SED 's/.*\://g'`
  AC_MSG_RESULT( $ax_cache_line_log_size)

  XMALLOC_CPU_CACHE_LINE=${ax_cache_line_size}
  XMALLOC_LOG_CPU_CACHE_LINE=${ax_cache_line_log_size}
  AC_SUBST(XMALLOC_CPU_CACHE_LINE)
  AC_SUBST(XMALLOC_LOG_CPU_CACHE_LINE)
])
