/**
 * \file   test-xReallocLarge.c
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
  
  // alloc large memory block
  void *p = xMalloc(2 * __XMALLOC_SIZEOF_PAGE);
  
  // realloc large
  p = xReallocLarge(p, __XMALLOC_SIZEOF_PAGE);
  __XMALLOC_ASSERT(NULL != p);

  // realloc large again
  p = xReallocLarge(p, 10 * __XMALLOC_SIZEOF_PAGE);
  __XMALLOC_ASSERT(NULL != p);

  xFree(p);

  return 0;
}
