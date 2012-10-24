/**
 * \file   test-xAllocFromNonEmptyPage.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test of allocation from non-empty page in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  void *p;
  xPage page;
  void *pageNextBefore;
  long usedBlocksBefore;
  void *q;
  int i;
  for (i = 1; i <= __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    p     = xMalloc(i);
    page  = xGetPageOfAddr(p);
    // get information before next allocation from page
    pageNextBefore    = __XMALLOC_NEXT(page->current);
    usedBlocksBefore  = page->numberUsedBlocks;
    q                 = xAllocFromNonEmptyPage(page);
    __XMALLOC_ASSERT(page->current == pageNextBefore);
    __XMALLOC_ASSERT(page->numberUsedBlocks == usedBlocksBefore + 1);
    xFree(p);
    xFree(q);
  }
  return 0;
}

