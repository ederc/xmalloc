/**
 * @file   xBin.c 
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline bin handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <xBin.h>
#include <xRegion.h>


/************************************************
 * SPEC-BIN STUFF
 ***********************************************/
//xBin xGetSpecBin(size_t size) {
//  xBin bin  = xGetBin(size);
//  if (bin == NULL) {
//    bin = (xBin)malloc(sizeof(*bin));
//    memset(bin, 0, sizeof(*bin));
//    bin->sizeInWords  = (size + __XMALLOC_SIZEOF_LONG - 1) / __XMALLOC_SIZEOF_LONG;
//    bin->currentPage  = xPageForMalloc;
//  }
//  return bin;
//}

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

void xInsertPageToBin(xBin bin, xPage page) {
  if(bin->currentPage == xZeroPage) {
    page->prev        = NULL;
    page->next        = NULL;
    bin->currentPage  = page;
    bin->lastPage     = page;
  } else {
    if(bin->currentPage == bin->lastPage) {
      bin->lastPage = page;
    } else {
      bin->currentPage->next->prev  = page;
    }
    page->next              = bin->currentPage->next;
    bin->currentPage->next  = page;
    page->prev              = bin->currentPage;
  }
}

/************************************************
 * ALLOCATING PAGES IN BINS
 ***********************************************/
void xAllocFromFullPage(void *addr, xBin bin) {
  if(bin->currentPage != xZeroPage) {
    bin->currentPage->numberUsedBlocks  = 0;
  }
  xPage newPage     = xAllocNewPageForBin(bin);
  xInsertPageToBin(bin, newPage);
  bin->currentPage  = newPage; 
  xAllocFromNonEmptyPage(addr, newPage);
}

/************************************************
 * ALLOCATING PAGES FOR BINS
 ***********************************************/
xPage xAllocNewPageForBin(xBin bin) {
  xPage newPage;
  void *tmp;
  int i = 1;

  // block size < page size
  if(bin->numberBlocks > 0)
    newPage = xAllocSmallBlockPageForBin(); // TOODOO
  // block size > page size
  else
    newPage = xAllocBigBlockPagesForBin(-bin->numberBlocks); // TOODOO

  newPage->numberUsedBlocks = -1;
  newPage->current  = (void*) (((char*) newPage) + 
                        __XMALLOC_SIZEOF_PAGE_HEADER);
  tmp               = newPage->current;
  while(i < bin->numberBlocks) {
    tmp = __XMALLOC_NEXT(tmp)  = ((void**) tmp) + bin->sizeInWords;
    i++;
  }
  __XMALLOC_NEXT(tmp) = NULL;
  return newPage;
}

xPage xAllocSmallBlockPageForBin() {
  xPage newPage;

  if(NULL == baseRegion)
    baseRegion  = xAllocNewRegion(1); // TOODOO
  
  while(1) {
    // current page in region can be used
    if(NULL != baseRegion->current) {
      newPage             = baseRegion->current;
      baseRegion->current = __XMALLOC_NEXT(newPage);
      goto Found;
    }
    // there exist pages in this region we can use
    if(baseRegion->numberInitPages > 0) {
      newPage = (xPage) baseRegion->initAddr;
      baseRegion->numberInitPages--;
      if(baseRegion->numberInitPages > 0)
        baseRegion->initAddr  +=  __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        baseRegion->initAddr  =   NULL;
      goto Found;
    }
    // there exists already a next region we can allocate from
    if(NULL != baseRegion->next) {
      baseRegion  = baseRegion->next;
    } else {
      xRegion region  = xAllocNewRegion(1);
      region->prev    = baseRegion;
      baseRegion      = baseRegion->next  = region;
    }
  }

  Found:
  newPage->region = baseRegion;
  baseRegion->numberUsedPages++;
  return newPage;
}

xPage xAllocBigBlockPagesForBin(int numberNeeded) {
  register xPage page;
  xRegion region;
  
  // take care that there is at least 1 region active, if
  // not then we allocate a big enough region for the memory chunk
  if(NULL == baseRegion)
    baseRegion  = xAllocNewRegion(numberNeeded);
  
  region  = baseRegion;
  while(1) {
    // memory chunk fits in this region
    if(region->numberInitPages >= numberNeeded) {
      page                    =   (xPage) region->initAddr;
      region->numberInitPages -=  numberNeeded;
      if(region->numberInitPages > 0)
        region->initAddr  +=  numberNeeded * __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        region->initAddr  =   NULL;
      goto Found;
    }
    // check if there is a consecutive chunk of numberNeeded pages in region we
    // can get
    page  = xGetConsecutivePagesFromRegion(region, numberNeeded);
    if(NULL != page)
      goto Found;
    // there already exists a next region we can allocate from
    if(NULL != region->next) {
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
  
  if(baseRegion != region) {
    xTakeOutRegion(region);
    xInsertRegionBefore(region, baseRegion);
  }
  return page;
}
