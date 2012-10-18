/**
 * \file   test-xMalloc0.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for allocations with zero setting for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  // alloc small memory block
  int i, j;
  for (i = 1; i <= 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE ; i++) {
    void *p  = xMalloc0(i);
    __XMALLOC_ASSERT(NULL != p);
    for (j = 0; j < i; j++)
      __XMALLOC_ASSERT(0 == *((char*)(p + j)));
    xFree(p);
  }
  return 0;
}
