/**
 * \file   test-Realloc-large-blocks.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
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
  void *p = xMalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
  int i;
  // reallocate the memory with reallocated block size greater than
  // the biggest size class xmalloc's bins can handle
  for (i = __XMALLOC_MAX_SMALL_BLOCK_SIZE; i < 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++)
  {
    p = xRealloc(p,i);
    __XMALLOC_ASSERT(NULL != p &&
        "xRealloc should have allocated addr != NULL.");
  }
  xFree(p);
  return 0;
}
