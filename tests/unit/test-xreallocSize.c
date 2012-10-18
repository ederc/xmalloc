/**
 * \file   test-xreallocSize.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for size reallocations for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  // alloc small memory block
  void *p = xMalloc(64);
  
  // realloc bigger
  p = xreallocSize(p, 64, 128);
  __XMALLOC_ASSERT(NULL != p);

  // realloc smaller
  p = xreallocSize(p, 128, 64);
  __XMALLOC_ASSERT(NULL != p);

  // realloc zero size
  p = xreallocSize(p, 64, 0);
  __XMALLOC_ASSERT(NULL != p);

  // realloc with NULL pointer
  p = xreallocSize(NULL, 1,128);
  __XMALLOC_ASSERT(NULL != p);

  xFree(p);

  return 0;
}
