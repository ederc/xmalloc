/**
 * \file   test-region-allocation.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for allocation of xRegions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int numberPages;
  int minNumberPages = __XMALLOC_MIN_NUMBER_PAGES_PER_REGION;
  // page number in region smaller than minimal set one
  // => regions should have minNumberPages
  for (numberPages = 1; numberPages <= minNumberPages; numberPages++) {
    xRegion region  = xAllocNewRegion(numberPages);
    __XMALLOC_ASSERT(region->numberInitPages == minNumberPages);
    __XMALLOC_ASSERT(region->totalNumberPages == minNumberPages);
    __XMALLOC_ASSERT(region->numberUsedPages == 0);
    xFreeRegion(region);
  }
  // page number in region greater than minimal set one
  // => regions should have numberPages
  for (numberPages; numberPages <= (5 * minNumberPages); numberPages++) {
    xRegion region  = xAllocNewRegion(numberPages);
    __XMALLOC_ASSERT(region->numberInitPages == numberPages);
    __XMALLOC_ASSERT(region->totalNumberPages == numberPages);
    __XMALLOC_ASSERT(region->numberUsedPages == 0);
    xFreeRegion(region);
  }
  return 0;
}
