/**
 * \file   test-xRealloc0Size.c
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
  
  // alloc small memory block
  void *p = xMalloc0(64);
  
  // realloc bigger
  p = xRealloc0Size(p, 64, 128);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + 127));

  // realloc smaller
  p = xRealloc0Size(p, 128, 64);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + 63));

  // realloc large
  p = xRealloc0Size(p, 64, 10 * __XMALLOC_SIZEOF_PAGE);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + (5 * __XMALLOC_SIZEOF_PAGE)));

  xFree(p);

  return 0;
}
