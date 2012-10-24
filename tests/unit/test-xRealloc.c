/**
 * \file   unit-xRealloc.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for small block allocations for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  // alloc small memory block
  void *p = xMalloc(1);

  p = xrealloc(p,64);
  __XMALLOC_ASSERT(NULL != p);

  p = xrealloc(p,32);
  __XMALLOC_ASSERT(NULL != p);

  xFreeSize(p,32);

  return 0;
}
