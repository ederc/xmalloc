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
  if (NULL == addr)
    // try it once more
    addr  = malloc(size);
  return addr; // possibly addr == NULL
}

void* xReallocSizeFromSystem(void *addr, size_t oldSize, size_t newSize) {
  void *newAddr = realloc(addr, newSize);
  if (NULL == newAddr) {
    newAddr = realloc(addr, newSize);
    if (NULL == newAddr)
      exit(1);
  }
  return newAddr;
}

void* xVallocFromSystem(size_t size) {
  void *addr  = valloc(size);
  if (NULL == addr)
    // try it once more
    addr = valloc(size);
  return addr; // possibly addr == NULL
}

void xVfreeToSystem(void *addr, size_t size) {
  assert(xIsAddrPageAligned(addr));
  munmap(addr, size);
}

void xFreeSizeToSystem(void *addr) {
  free(addr);
}