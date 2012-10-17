/**
 * \file   test-xInsertRegionAfter.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for insertion of xRegions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  xRegion region1 = xMalloc(sizeof(xRegionType));
  __XMALLOC_ASSERT(region1->next == NULL);
  __XMALLOC_ASSERT(region1->prev == NULL);

  xRegion region2 = xMalloc(sizeof(xRegionType));
  __XMALLOC_ASSERT(region2->next == NULL);
  __XMALLOC_ASSERT(region2->prev == NULL);
  
  xRegion region3 = xMalloc(sizeof(xRegionType));
  __XMALLOC_ASSERT(region3->next == NULL);
  __XMALLOC_ASSERT(region3->prev == NULL);
  
  // inserts region1 after region2
  xInsertRegionAfter(region1, region2);
  __XMALLOC_ASSERT(region2->next == region1);
  __XMALLOC_ASSERT(region1->prev == region2);

  // inserts region3 after region2
  xInsertRegionAfter(region3, region2);
  __XMALLOC_ASSERT(region2->next == region3);
  __XMALLOC_ASSERT(region3->prev == region2);
  __XMALLOC_ASSERT(region1->prev == region3);
  __XMALLOC_ASSERT(region3->next == region1);

  xFree(region1);
  xFree(region2);
  xFree(region3);

  return 0;
}
