/**
 * @file   threads.h
 * @author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   September 2012
 * @brief  Threading business for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_THREAD_H
#define XMALLOC_THREAD_H

#include "xassert.h"

/**
 * \fn static inline unsigned int xGetNumberCpus()
 *
 * \brief Returns the number of Cpus available on the system xmalloc is build on.
 *
 * \return number of cpus of type \c unsigned \c int .
 *
 */
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

/*************************************************
 * mutex locks & unlocks
 ************************************************/
/**
 * \fn static inline void xMutexLock(xMutex_t *mutex)
 *
 * \brief Get the lock of the mutex.
 *
 * \param mutex \c xMutex_t* the lock should be got from
 *
 * \note If macro __XMALLOC_THREADED is not defined then this function is just
 * empty: In a single-threaded application no locks have to be set.
 *
 */
static inline void xMutexLock(xMutex_t *mutex) {
#ifdef __XMALLOC_THREADED
#ifdef _WIN32
  EnterCriticalSection(&mutex->lock);
#elif (defined(__XMALLOC_OSSPIN))
  OSSpinLockLock(&mutex->lock);
#else
  pthread_mutex_lock(&mutex->lock);
#endif
}

/**
 * \fn static inline void xMutexUnlock(xMutex_t *mutex)
 *
 * \brief Unlocks the mutex.
 *
 * \param mutex \c xMutex_t* the lock should be released from
 *
 * \note If macro __XMALLOC_THREADED is not defined then this function is just
 * empty: In a single-threaded application no locks have to be set, and thus,
 * also none have to be released.
 *
 */
static inline void xMutexUnlock(xMutex_t *mutex) {
#ifdef __XMALLOC_THREADED
#ifdef _WIN32
  LeaveCriticalSection(&mutex->lock);
#elif (defined(__XMALLOC_OSSPIN))
  OSSpinLockUnlock(&mutex->lock);
#else
  pthread_mutex_unlock(&mutex->lock);
#endif
}
