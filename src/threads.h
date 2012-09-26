/**
 * @file   threads.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   September 2012
 * @brief  Threading business for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */
static inline unsigned long xGetNumberCpus() {
  long result;

#ifdef _WIN32
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  result  = si.dwNumberOfProcessors;
#else
  result  = sysconf(_SC_NPROCESSORS_ONLN);
  // if we don't get useful data, i.e. an error happens we trigger the number of
  // available cpus to be at least 1
  if (-1 == result)
    result  = 1;
#endif

  return (unsigned long) result;
}
