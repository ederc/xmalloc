/**
 * \file   test-xTakeOutRegion.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for taking out xRegions.
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
  
  // inserts region1 before region2
  xInsertRegionBefore(region1, region2);
  __XMALLOC_ASSERT(region1->next == region2);
  __XMALLOC_ASSERT(region2->prev == region1);

  // inserts region3 before region2
  xInsertRegionBefore(region3, region2);
  __XMALLOC_ASSERT(region3->next == region2);
  __XMALLOC_ASSERT(region2->prev == region3);
  __XMALLOC_ASSERT(region1->next == region3);
  __XMALLOC_ASSERT(region3->prev == region1);

  // removes region3 from list
  xTakeOutRegion(region3);
  __XMALLOC_ASSERT(region2->next == NULL);
  __XMALLOC_ASSERT(region2->prev == region1);
  __XMALLOC_ASSERT(region1->next == region2);
  __XMALLOC_ASSERT(region1->prev == NULL);

  // removes region1 from list
  xTakeOutRegion(region1);
  __XMALLOC_ASSERT(region2->next == NULL);
  __XMALLOC_ASSERT(region2->prev == NULL);

  xFree(region1);
  xFree(region2);
  xFree(region3);

  return 0;
}
