/**
 * \file   test-xDoRealloc.c
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
  p = xDoRealloc(p, 64, 128, 0);
  __XMALLOC_ASSERT(NULL != p);

  // realloc smaller
  p = xDoRealloc(p, 128, 64, 0);
  __XMALLOC_ASSERT(NULL != p);

  // realloc large and set zero
  p = xDoRealloc(p, 64, 10 * __XMALLOC_SIZEOF_PAGE, 1);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p+(5*__XMALLOC_SIZEOF_PAGE)));

  // realloc large to large
  p = xDoRealloc(p, 10 * __XMALLOC_SIZEOF_PAGE, 5 * __XMALLOC_SIZEOF_PAGE, 1);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + (5*__XMALLOC_SIZEOF_PAGE) - 1));

  xFree(p);

  return 0;
}
