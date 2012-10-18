/**
 * \file   unit-xmalloc.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for small block allocations for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {

  void *p;
  // alloc small memory block
  p = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
  __XMALLOC_ASSERT(NULL != p);
  xFree(p);
  
  // alloc big memory block
  p = xmalloc(10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE);
  __XMALLOC_ASSERT(NULL != p);
  xFree(p);
  
  // alloc size zero
  p = xmalloc(0);
  __XMALLOC_ASSERT(NULL == p);
  
  return 0;
}
