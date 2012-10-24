/**
 * \file   region.c 
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   August 2012
 * \brief  General source file for non-inline region handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <region.h>
#include <system.h>


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
  xRegisterPagesInRegion(addr, numberPages);
  region->current           = NULL;
  region->prev              = NULL;
  region->next              = NULL;
  region->initAddr          = addr;
  region->addr              = addr;
  region->numberInitPages   = numberPages;
  region->numberUsedPages   = 0;
  region->totalNumberPages  = numberPages;

#ifdef __XMALLOC_DEBUG
  info.availablePages +=  numberPages;
  info.currentRegionsAlloc++;
  if (info.currentRegionsAlloc > info.maxRegionsAlloc)
    info.maxRegionsAlloc  = info.currentRegionsAlloc;
#endif

  return region;
}

/************************************************
 * PAGE HANDLING IN REGIONS
 ***********************************************/
xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded) {
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
          __XMALLOC_ASSERT(NULL != prev);
          __XMALLOC_NEXT(prev)  = __XMALLOC_NEXT(iter);
        }
        return page;
      }
    }
    prev    = iter;
    current = __XMALLOC_NEXT(iter);
  }
  return NULL;
}

/**********************************************
 * FREEING OPERATIONS CONCERNING PAGES
 *********************************************/
void xFreePagesFromRegion(xPage page, int quantity) {
  xRegion region          =   page->region;
  region->numberUsedPages -=  quantity;
  if (0 == region->numberUsedPages) {
    if (xBaseRegion == region) {
      if (NULL != region->next) {
        xBaseRegion = region->next;
      } else {
        xBaseRegion = region->prev;
      }
    }
    xTakeOutRegion(region);
    xFreeRegion(region);
  } else {
    if ((xBaseRegion != region) && xIsRegionEmpty(region)) {
      xTakeOutRegion(region);
      xInsertRegionAfter(region, xBaseRegion);
    }
    if (quantity > 1) {
      int i = quantity;
      char *iterPage = (char *)page;

      while (i > 1) {
        __XMALLOC_NEXT(iterPage)  = iterPage + __XMALLOC_SIZEOF_SYSTEM_PAGE;
        iterPage  = __XMALLOC_NEXT(iterPage);
        i--;
      }
      __XMALLOC_NEXT(iterPage)  = region->current;
    } else {
      __XMALLOC_NEXT(page)  = region->current;
    }
    region->current = (void *)page;
  }
#ifndef __XMALLOC_NDEBUG
  info.availablePages +=  quantity;
  info.usedPages      -=  quantity;
#endif
}
