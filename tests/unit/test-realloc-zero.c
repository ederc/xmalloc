/**
 * \file   test-Realloc-zero.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for reallocations with zero setting for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  // alloc small memory block
  void *p = xMalloc0(1);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *((char *)p));

  int i, j, maxWordSize;
  // reallocate the memory as long as the reallocated block size fits in
  // xmallocs bins
  for (i = 1 ; i < 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    p = xRealloc0(p,i);
    __XMALLOC_ASSERT(NULL != p);
    // get word size of corresponding bin
    if (i <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
      xBin bin  = xGetBinOfAddr(p);
      maxWordSize = bin->sizeInWords;
    } else {
      maxWordSize = xWordSizeOfAddr(p);
    }

    // check if memory is set to zero
    for (j = 0; j < maxWordSize; j++) {
      __XMALLOC_ASSERT(0 == *((char *)p + j));
    }
  }
  xFree(p);
  return 0;
}
