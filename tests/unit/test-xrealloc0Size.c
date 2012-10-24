/**
 * \file   test-xrealloc0Size.c
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
  p = xrealloc0Size(p, 64, 128);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p+127));

  // realloc smaller
  p = xrealloc0Size(p, 128, 64);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p+63));

  // realloc zero
  p = xrealloc0Size(p, 64, 0);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);

  // realloc NULL pointer
  p = xrealloc0Size(NULL, 1, 128);
  __XMALLOC_ASSERT(NULL != p);
  __XMALLOC_ASSERT(0 == *(char *)p);
  __XMALLOC_ASSERT(0 == *((char *)p + 127));

  xFree(p);

  return 0;
}
