/**
 * @file   xRegion.c 
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  General source file for non-inline region handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <xBin.h>
#include <xSystem.h>


/************************************************
 * REGION ALLOCATION
 ***********************************************/
xRegion xAllocNewRegion(int minNumberPages) {
  xRegion region  = xAllocFromSystem(sizeof(xRegionType));
  void *addr;
  int numberPages = __XMALLOC_MAX(minNumberPages, 
                      __XMALLOC_MIN_NUMBER_PAGES_PER_REGION);
  
  addr  = xVallocFromSystem(numberPages * __XMALLOC_SIZEOF_SYSTEM_PAGE);
  if (NULL == addr) {
    numberPages = minNumberPages;
    addr  = xVallocFromSystem(numberPages * __XMALLOC_SIZEOF_SYSTEM_PAGE);
  }

  // register and initialize the region
  xRegisterPages(addr, numberPages); // TOODOO
  region->current           = NULL;
  region->prev              = NULL;
  region->next              = NULL;
  region->initAddr          = addr;
  region->addr              = addr;
  region->numberInitPages   = numberPages;
  region->numberUsedPages   = 0;
  region->totalNumberPages  = numberPages;

  return region;
}

/************************************************
 * PAGE HANDLING IN REGIONS
 ***********************************************/
xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded) { // TOODOO
  void  *current, *page, *prev = NULL;
  char  *iter;
  int   found;
  current = region->current;
  while (NULL != current) {
    found = 1;
    iter  = current;
    while (__XMALLOC_NEXT(iter) == (iter + __XMALLOC_SIZEOF_SYSTEM_PAGE)) {
      iter  = __XMALLOC_NEXT(iter);
      // it is possible that (iter + __XMALLOC_SIZEOF_SYSTEM_PAGE == 0
      if (NULL == iter)
        return NULL;
      found++;
      if (found == numberNeeded) {
        page  = current;
        if (region->current == current) {
          region->current = __XMALLOC_NEXT(iter);
        } else {
          assert(0 == 1);
  return page;
}
