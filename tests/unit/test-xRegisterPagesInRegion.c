/**
 * \file   test-xRegisterPagesInRegion.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test of registering pages in regionin xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  // preparation
  void *p         = xVallocFromSystem(512 * __XMALLOC_SIZEOF_SYSTEM_PAGE);
  
  // registration
  xRegisterPagesInRegion(p, 512);

  // check
  char *q = (char*)p + 511 * __XMALLOC_SIZEOF_SYSTEM_PAGE;
  // startIndex < endIndex
  unsigned long startIndex  = xGetPageIndexOfAddr(p);
  unsigned long endIndex    = xGetPageIndexOfAddr(q);
  unsigned long shift       = xGetPageShiftOfAddr(p);
  
  for (shift = startIndex + 1; shift < endIndex; shift++)
    __XMALLOC_ASSERT(xPageShifts[shift - xMinPageIndex] == ULLONG_MAX);

  __XMALLOC_ASSERT(xMinPageIndex < xMaxPageIndex);

  xVfreeToSystem(p, 512 * __XMALLOC_SIZEOF_SYSTEM_PAGE);

  return 0;
}
