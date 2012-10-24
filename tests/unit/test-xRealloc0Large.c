/**
 * \file   test-xRealloc0Large.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
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
  void *p = xMalloc0(2 * __XMALLOC_SIZEOF_PAGE);
  
  // realloc large
  p = xRealloc0Large(p, __XMALLOC_SIZEOF_PAGE);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + __XMALLOC_SIZEOF_PAGE -1));

  // realloc large again
  p = xRealloc0Large(p, 10 * __XMALLOC_SIZEOF_PAGE);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + __XMALLOC_SIZEOF_PAGE -1));
  __XMALLOC_ASSERT(0 == *((char *)p + (10 * __XMALLOC_SIZEOF_PAGE) -1));

  xFree(p);

  return 0;
}
