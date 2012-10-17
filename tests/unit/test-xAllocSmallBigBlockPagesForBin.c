/**
 * \file   test-xAllocSmallBigBlockPagesForBin.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test getting consecutive pages from a region.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int numberPages = __XMALLOC_MIN_NUMBER_PAGES_PER_REGION;
  void *currPage;
  xPage page;
  // => region is set to be the xBaseRegion
  xRegion region  = xAllocNewRegion(numberPages);
  xBaseRegion = region; 
  // get some big block pages from region
  currPage  = region->initAddr;
  page      = xAllocBigBlockPagesForBin(3);
  __XMALLOC_ASSERT(page->region == region);
  __XMALLOC_ASSERT(region->numberUsedPages == 3);
  __XMALLOC_ASSERT(region->initAddr == 
      (currPage + (3 * __XMALLOC_SIZEOF_SYSTEM_PAGE)));
  
  // get 1 small block page from region
  currPage  = region->initAddr;
  page      = xAllocSmallBlockPageForBin();
  __XMALLOC_ASSERT(page->region == region);
  __XMALLOC_ASSERT(region->numberUsedPages == 4);
  __XMALLOC_ASSERT(region->initAddr == 
      (currPage + (1 * __XMALLOC_SIZEOF_SYSTEM_PAGE)));
  // get more big block pages than are left in the region
  currPage  = region->initAddr;
  page      = xAllocBigBlockPagesForBin(510);
  // page is on another region!
  __XMALLOC_ASSERT(page->region != region);
  // for the old region only the 4 pages from above should be in use
  __XMALLOC_ASSERT(region->numberUsedPages == 4);

  xFreeRegion(region);

  return 0;
}
