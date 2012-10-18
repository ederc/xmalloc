/**
 * \file   test-Realloc-size-large-blocks.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for large block reallocations for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  // alloc small memory block
  void *p = xMalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE - 1);
  int i;
  // reallocate the memory as long as the reallocated block size fits in
  // xmallocs bins
  for (i = __XMALLOC_MAX_SMALL_BLOCK_SIZE; i < 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    __XMALLOC_ASSERT((i-1) <= xSizeOfAddr(p) &&
        "Size of old addr is not correct.");
    p = xReallocSize(p,i-1,i);
    __XMALLOC_ASSERT(NULL != p &&
        "xRealloc should have allocated addr != NULL.");
  }
  xFree(p);
  return 0;
}
