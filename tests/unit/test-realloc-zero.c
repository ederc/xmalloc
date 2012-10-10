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
  int *p = (int*) xMalloc0(sizeof(int));
  __XMALLOC_ASSERT(NULL != p && 0 == *p && "Should be allocated and set to zero");
  int i, j;
  // reallocate the memory as long as the reallocated block size fits in
  // xmallocs bins
  for (i = i + __XMALLOC_SIZEOF_INT ; 
      i < __XMALLOC_MAX_SMALL_BLOCK_SIZE; 
      i = i + __XMALLOC_SIZEOF_INT) {
    p = xRealloc0(p,i);
    __XMALLOC_ASSERT(NULL != p &&
        "xRealloc should have allocated addr != NULL.");
    for(j = 0; j <= i; j = j + __XMALLOC_SIZEOF_INT) {
      printf("p+j = %ld\n",*(p+j));
      printf("j = %ld\n",j);
      __XMALLOC_ASSERT(0 == *(p + j));
    }
  }
  xFree(p);
  return 0;
}
