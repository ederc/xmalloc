/**
 * @file   bin.c
 * @Author Christian Eder ( ederd@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline bin handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include "src/bin.h"

// extern declaration in globals.h
xPage xPageForMalloc  = (xPage)1;
xRegion xBaseRegion    = NULL;


//void xUnGetSpecBin(xBin* bin) {
//  if (*bin  ==  NULL) {
//    printf("xUnGetSpecBin(NULL\n");
//  } else {
//    if ((*bin)->currentPage == xPageForMalloc) {
//      /* TODO */
//      free(*bin);
//    }
//  }
//  *bin  = NULL;
//}

/************************************************
 * PAGE-BIN-CONNECTIONS
 ***********************************************/
//xPage xGetPageFromBin(xBin bin) {
//  if (bin->currentPage != NULL) {
//    if (bin->currentPage->free != NULL)
//      return bin->currentPage;
//    else {
//      xPage page  = bin->lastPage;
//      while ((page != NULL) && (page->free == NULL))
//        page  = page->prev;
//      if ((page != NULL) && (page->free != NULL)) {
//        bin->currentPage  = page;
//        return page;
//      }
//    }
//  }
//  /* now b->current==NULL or all pages are full */
//  //extern void *xGetNewPage();
//  xPage page  = (xPage)xGetNewPage();
//  xMakePage(page, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
//  page->prev  = bin->lastPage;
//  page->next  = NULL;
//  if (bin->lastPage !=  NULL)
//    bin->lastPage->next = page;
//  bin->lastPage         = page;
//  bin->currentPage      = page;
//  page->bin             = bin;
//  return page;
//  //return b->currentPage;
//}

/************************************************
 * ALLOCATING PAGES FOR BINS
 ***********************************************/
xPage xAllocNewPageForBin(xBin bin) {
  xPage newPage;
  void *tmp;
  int i = 1;

  // block size < page size
#if __XMALLOC_DEBUG > 1
  printf("binNumberBlocks %ld in %p\n",bin->numberBlocks,bin);
#endif
  if (bin->numberBlocks > 0) {
    newPage = xAllocSmallBlockPageForBin();
  }
  // block size > page size
  else
    newPage = xAllocBigBlockPagesForBin(-bin->numberBlocks);

  xSetTopBinAndStickyOfPage(newPage, bin);
  newPage->numberUsedBlocks = -1;
  newPage->current  = (void*) (((char*) newPage) +
                        __XMALLOC_SIZEOF_PAGE_HEADER);
  tmp               = newPage->current;
  while (i < bin->numberBlocks) {
    tmp = __XMALLOC_NEXT(tmp)  = ((void**) tmp) + bin->sizeInWords;
    i++;
  }
  __XMALLOC_NEXT(tmp) = NULL;

#if __XMALLOC_DEBUG > 1
  printf("PAGEUSEDBLOCKS %ld\n", newPage->numberUsedBlocks);
#endif
  return newPage;
}

xPage xAllocSmallBlockPageForBin() {
  xPage newPage;

  if (NULL == xBaseRegion)
    xBaseRegion  = xAllocNewRegion(1);

  while (1) {
    // current page in region can be used
    if (NULL != xBaseRegion->current) {
      newPage             = xBaseRegion->current;
      xBaseRegion->current = __XMALLOC_NEXT(newPage);
      goto Found;
    }
    // there exist pages in this region we can use
    if (xBaseRegion->numberInitPages > 0) {
      newPage = (xPage) xBaseRegion->initAddr;
      xBaseRegion->numberInitPages--;
      if (xBaseRegion->numberInitPages > 0)
        xBaseRegion->initAddr  +=  __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        xBaseRegion->initAddr  =   NULL;
      goto Found;
    }
    // there exists already a next region we can allocate from
    if (NULL != xBaseRegion->next) {
      xBaseRegion  = xBaseRegion->next;
    } else {
      xRegion region  = xAllocNewRegion(1);
      region->prev    = xBaseRegion;
      xBaseRegion     = xBaseRegion->next  = region;
    }
  }

  Found:
  newPage->region = xBaseRegion;
  xBaseRegion->numberUsedPages++;

#ifndef __XMALLOC_NDEBUG
  info.usedPages++;
  info.availablePages--;
  if (info.usedPages > info.maxPages)
    info.maxPages = info.usedPages;
#endif
  return newPage;
}

xPage xAllocBigBlockPagesForBin(int numberNeeded) {
  register xPage page;
  xRegion region;

  // take care that there is at least 1 region active, if
  // not then we allocate a big enough region for the memory chunk
  if (NULL == xBaseRegion)
    xBaseRegion  = xAllocNewRegion(numberNeeded);

  region  = xBaseRegion;
  while (1) {
    // memory chunk fits in this region
    if (region->numberInitPages >= numberNeeded) {
      page                    =   (xPage) region->initAddr;
      region->numberInitPages -=  numberNeeded;
      if (region->numberInitPages > 0)
        region->initAddr  +=  numberNeeded * __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        region->initAddr  =   NULL;
      goto Found;
    }
    // check if there is a consecutive chunk of numberNeeded pages in region we
    // can get
    page  = xGetConsecutivePagesFromRegion(region, numberNeeded);
    if (NULL != page)
      goto Found;
    // there already exists a next region we can allocate from
    if (NULL != region->next) {
      region  = region->next;
    } else {
      xRegion newRegion = xAllocNewRegion(numberNeeded);
      region->next      = newRegion;
      newRegion->prev   = region;
      region            = newRegion;
    }
  }

  Found:
  page->region            =   region;
  region->numberUsedPages +=  numberNeeded;

  if (xBaseRegion != region) {
    xTakeOutRegion(region);
    xInsertRegionBefore(region, xBaseRegion);
  }

#ifndef __XMALLOC_NDEBUG
  info.usedPages      +=  numberNeeded;
  info.availablePages -=  numberNeeded;
  if (info.usedPages > info.maxPages)
    info.maxPages = info.usedPages;
#endif
  return page;
}

/**********************************************
 * PAGE FREEING
 *********************************************/
void xFreeToPageFault(xPage page, void *addr) {
  __XMALLOC_ASSERT(page->numberUsedBlocks <= 0L);
  xBin bin  = xGetBinOfPage(page);
  if ((NULL != page->current) || (bin->numberBlocks <= 1)) {
    // collect all blocks of page
    xTakeOutPageFromBin(page, bin);
    // page can be freed
    if (bin->numberBlocks > 0)
      xFreePagesFromRegion(page,1);
    else
      xFreePagesFromRegion(page, - bin->numberBlocks);
  } else {
    // page was full
    page->current           = addr;
    page->numberUsedBlocks  = bin->numberBlocks - 2;
    *((void **) addr)       = NULL;
    xTakeOutPageFromBin(page, bin);
    xInsertPageToBin(page, bin);
  }
}
