/**
 * \file   test-xReallocSizeFromSystem.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for reallocations done by the system.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  // alloc a memory block
  void *p = xAllocFromSystem(2048);
  __XMALLOC_ASSERT(NULL != p);
  
  // realloc memory from the system
  p = xReallocSizeFromSystem(p, 2048, 8192);
  __XMALLOC_ASSERT(NULL != p);

  xFreeSizeToSystem(p, 8192);

  return 0;
}
