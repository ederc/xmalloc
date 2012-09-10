/**
 * @file   system.c
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Source file for system allocations in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "src/page.h" // for xIsAddrPageAligned
#include "src/system.h"

void* xAllocFromSystem(size_t size) {
  void *addr  = malloc(size);
  if (NULL == addr) {
    // try it once more
    addr  = malloc(size);
    if (NULL == addr)
      exit(1);
  }

#ifndef __XMALLOC_NDEBUG
  // track some statistics if in debugging mode
  info.currentBytesFromMalloc +=  size;
  if (info.currentBytesFromMalloc > info.maxBytesFromMalloc) {
    info.maxBytesFromMalloc = info.currentBytesFromMalloc;
#ifdef __XMALLOC_HAVE_MMAP
    if (info.currentBytesFromValloc > info.maxBytesSystem)
      info.maxBytesSystem = info.currentBytesFromValloc;
#endif
#ifdef __XMALLOC_HAVE_SBRK
    if (0 == xSbrkInit)
      xSbrkInit = (unsigned long) sbrk(0) - size;
#ifndef __XMALLOC_HAVE_MMAP
    if (info.maxBytesFromMalloc + info.currentBytesFromValloc > info.maxBytesSbrk)
#else
    if (info.maxBytesFromMalloc > info.maxBytesSbrk)
#endif
      info.maxBytesSbrk = (unsigned long) sbrk(0) - xSbrkInit;
#endif
  }
#endif
  return addr; // possibly addr == NULL
}

void* xReallocSizeFromSystem(void *addr, size_t oldSize, size_t newSize) {
  void *newAddr = realloc(addr, newSize);
  if (NULL == newAddr) {
    newAddr = realloc(addr, newSize);
    if (NULL == newAddr)
      exit(1);
  }

#ifndef __XMALLOC_NDEBUG
  info.currentBytesFromMalloc +=  (long) newSize - (long) oldSize;

  if (info.currentBytesFromMalloc > info.maxBytesFromMalloc) {
    info.maxBytesFromMalloc = info.currentBytesFromMalloc;
#ifdef __XMALLOC_HAVE_MMAP
    if (info.currentBytesFromValloc > info.maxBytesSystem)
      info.maxBytesSystem = info.currentBytesFromValloc;
#endif
#if defined(__XMALLOC_HAVE_SBRK) && !defined(__XMALLOC_HAVE_MMAP)
    if (info.maxBytesFromMalloc + info.currentBytesFromValloc > info.maxBytesSbrk)
#else
    if (info.maxBytesFromMalloc > info.maxBytesSbrk)
#endif
      info.maxBytesSbrk = (unsigned long) sbrk(0) - xSbrkInit;
#endif
  return newAddr;
}

void* xVallocFromSystem(size_t size) {
  void *addr  = xValloc(size);
  if (NULL == addr)
    // try it once more
    addr = xValloc(size);

#ifndef __XMALLOC_NDEBUG
  assert(xIsAddrPageAligned(addr));

  // track some statistics if in debugging mode
  info.currentBytesFromMalloc +=  size;
  if (info.currentBytesFromMalloc > info.maxBytesFromMalloc) {
    info.maxBytesFromMalloc = info.currentBytesFromMalloc;
#ifdef __XMALLOC_HAVE_MMAP
    if (info.maxBytesFromValloc > info.maxBytesSystem)
      info.maxBytesSystem = info.maxBytesFromValloc;
#endif
#ifdef __XMALLOC_HAVE_SBRK
    if (0 == xSbrkInit)
      xSbrkInit = (unsigned long) sbrk(0) - size;
#ifndef __XMALLOC_HAVE_MMAP
    if (info.maxBytesFromMalloc + info.currentBytesFromValloc > info.maxBytesSbrk) {
#else
    if (info.maxBytesFromMalloc > info.maxBytesSbrk) {
#endif
      info.maxBytesSbrk = (unsigned long) sbrk(0) - xSbrkInit;
      assert(info.maxBytesSbrk >= info.currentBytesFromMalloc 
              + info.currentBytesFromValloc);
    }
#endif
  }
#endif
      
  return addr; // possibly addr == NULL
}

void xVfreeToSystem(void *addr, size_t size) {
  assert(xIsAddrPageAligned(addr));
  munmap(addr, size);
#ifndef __XMALLOC_NDEBUG
  info.currentBytesFromMalloc -=  size;
#endif
}

void xFreeSizeToSystem(void *addr, size_t size) {
  free(addr);
#ifndef __XMALLOC_NDEBUG
  info.currentBytesFromMalloc -=  size;
#endif
}

void* xValloc(size_t size) {
#ifdef __XMALLOC_HAVE_MMAP
  void *addr;
  addr  = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if ((void *)-1 == addr)
    return NULL;
  return addr;
#else
  return __libc_valloc(size);
#endif
}

