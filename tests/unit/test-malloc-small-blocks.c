/**
 * \file   unit-test-malloc-small-blocks.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for small block allocations for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main()
{
  // alloc small memory block
  void *p = xMalloc(1);
  int i;
  // reallocate the memory as long as the reallocated block size fits in
  // xmallocs bins
  for (i = 2; i < __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++)
  {
    p = xRealloc(p,i);
    __XMALLOC_ASSERT(NULL != p &&
        "xRealloc should have allocated addr != NULL.");
  }
  xFree(p);
  return 0;
}
