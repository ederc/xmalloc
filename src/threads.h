/**
 * @file   threads.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   September 2012
 * @brief  Threading business for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_THREAD_H
#define XMALLOC_THREAD_H

#include "xassert.h"

static inline unsigned int xGetNumberCpus() {
  long result;

#ifdef _WIN32
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  result  = si.dwNumberOfProcessors;
#else
#ifdef _SC_NPROCESSORS_ONLN
  result  = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROCESSORS_CONF)
  result  = sysconf(_SC_NPROCESSORS_CONF);
#endif
  // if we don't get useful data, i.e. an error happens we trigger the number of
  // available cpus to be at least 1
  if (-1 == result)
    result  = 1;
#endif

  return (unsigned int) result;
}
#endif
