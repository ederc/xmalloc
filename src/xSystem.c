/**
 * @file   xSystem.c
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Source file for system allocations in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <xSystem.h>

void* xAllocFromSystem(size_t size) {
  void *addr  = malloc(size);
  if(NULL == addr)
    // try it once more
    addr  = malloc(size);
  return addr; // possibly addr == NULL
}

void* xVallocFromSystem(size_t size) {
  void *addr  = valloc(size);
  if(NULL == addr)
    // try it once more
    addr = valloc(size);
  return addr; // possibly addr == NULL
}
