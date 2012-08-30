/**
 * @file   bin.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Bin handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 * @note   There are some page based functions implemented in the bin.* 
 *         files since they depend internally on the strong page <-> bin
 *         connection.
 */

#ifndef XMALLOC_BIN_H
#define XMALLOC_BIN_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "src/data.h"
#include "src/globals.h"
#include "src/page.h"
#include "src/region.h"
#include "src/align.h"

/************************************************
 * NOTE: The functionality of getting and freeing
 *       xSpecBins must be located in xmalloc.*
 *       since it depends on xMalloc(), etc.
 ***********************************************/
// xBin xGetSpecBin(size_t size); => see xmalloc.h
// void xUnGetSpecBin(xBin *bin); => see xmalloc.h

/************************************************
 * FREEING OPERATIONS CONCERNING PAGES: THOSE 
 * DEPEND ON BINS => THEY ARE IMPLEMENTED HERE
 ***********************************************/
/**
 * @fn void xFreeToPageFault(xPage page, void *addr)
 *
 * @brief If there was a problem in @var xFreeToPage() this function has to
 * take care of the freeing: At the point this function is called we already
 * know that @var page->numberUsedBlocks <= 0.
 * There are 3 different strategies on what to do with pages which were full and
 * have a free block now:
 * 1. Insert at the end ( default ).
 * 2. Insert after @var current_page
 *    => #define __XMALLOC_PAGE_AFTER_CURRENT
 * 3. Insert before @var current_page , i.e. let it be the new current page
 *    => #define __XMALLOC_PAGE_BEFORE_CURRENT
 *
 * @param page \c xPage the freed memory should be given to
 *
 * @param addr memory address to be checked
 *
 */
void xFreeToPageFault(xPage page, void *addr); // TOODOO

/**
 * @fn static inline void xFreeToPage(xPage page, void *addr)
 *
 * @brief Frees memory at @var addr to @c xPage @var page .
 *
 * @param page @c xPage the freed memory should be given to
 *
 * @param addr memory address to be checked
 *
 */
static inline void xFreeToPage(xPage page, void *addr) {
  if (page->numberUsedBlocks > 0L) {
    *((void **) addr) = page->current;
    page->current     = addr;
  } else {
    xFreeToPageFault(page, addr);
  }
}

/************************************************
 * STICKY BUSINESS OF BINS
 ***********************************************/
/**
 * @fn static inline bool xIsStickyBin(xBin bin)
 *
 * @brief Tests if @var bin is sticky or not.
 *
 * @param bin @var xBin to be tested
 *
 * @return true if @var bin is sticky, false else
 *
 */
static inline bool xIsStickyBin(xBin bin) {
  return (bin->sticky >= __XMALLOC_SIZEOF_VOIDP);
}


/************************************************
 * LIST HANDLING FOR SPECIAL BINS
 ***********************************************/
/**
 * @fn static inline xOffsetToNextSpecBin(xSpecBin specBin)
 *
 * @brief Returns the offset in the list of special bins w.r.t. to next
 *
 * @param specBin @var xSpecBin the offset is computed of.
 *
 */

/*
static inline xOffsetToNextSpecBin(xSpecBin specBin) {
  return (NULL != specBin ? ((char *)&(specBin->next)) - ((char *)specBin) : 0);
}
*/

/**
 * @fn static inline xOffsetToNumberBlocksSpecBin(xSpecBin specBin)
 *
 * @brief Returns the offset in the list of special bins w.r.t. to numberBlocks
 *
 * @param specBin @var xSpecBin the offset is computed of.
 *
 */

/*
static inline xOffsetToNumberBlocksSpecBin(xSpecBin specBin) {
  return (NULL != specBin ?
      ((char *)&(specBin->numberBlocks)) - ((char *)specBin) : 0);
}
*/

/**
 * @fn static inline void* xFindInSortedList(xSpecBin xBaseSpecBin, long numberBlocks)
 *
 * @brief Tries to find a special bin for the size class given by
 * @var numberBlocks . If there does not exist such a special bin, then
 * it returns NULL. Here the list searched through is already sorted by
 * increasing size classes.
 *
 * @param bin @var xSpecBin usually base of special bins, but can be any
 * @var xSpecBin .
 *
 * @param numberBlocks @var long number of blocks in bin, i.e. size class
 * needed for special bin.
 *
 * @return address of found xSpecBin, NULL if none is found
 */
static inline void* xFindInSortedList(xSpecBin bin, long numberBlocks) {
  while (NULL != bin) {
    if (bin->numberBlocks >= numberBlocks) {
      if (bin->numberBlocks == numberBlocks)
        return bin;
      // list is sorted, thus we know that there does not exist
      // such a special bin we need in this list
      return NULL;
    }
    bin = bin->next;
  }
  return NULL;
}

/**
 * @fn static inline void* xFindInList(xSpecBin xBaseSpecBin, long numberBlocks)
 *
 * @brief Tries to find a special bin for the size class given by
 * @var numberBlocks . If there does not exist such a special bin, then
 * it returns NULL. Here the list searched through is possibly not sorted.
 *
 * @param bin @var xSpecBin usually base of special bins, but can be any
 * @var xSpecBin .
 *
 * @param numberBlocks @var long number of blocks in bin, i.e. size class
 * needed for special bin.
 *
 * @return address of found xSpecBin, NULL if none is found
 */
static inline void* xFindInList(xSpecBin bin, long numberBlocks) {
  while (NULL != bin) {
    if (bin->numberBlocks == numberBlocks)
      return bin;
    bin = bin->next;
  }
  return NULL;
}

/************************************************
 * HANDLING LISTS OF PAGES / PAGE INFORAMTION
 * IN BINS
 ***********************************************/
/**
 * @fn void xTakeOutPageFromBin(xPage page, xBin bin)
 *
 * @brief Takes @var page out of @var bin.
 *
 * @param bin @var xBin the new page is a part of
 *
 * @param page @var xPage taken out of @var bin
 *
 */
static inline void xTakeOutPageFromBin(xPage page, xBin bin) {
  if (bin->currentPage == page) {
    if (NULL == page->next) {
      if (NULL == page->prev) {
        bin->lastPage = NULL;
        bin->currentPage  = __XMALLOC_ZERO_PAGE;
        return;
      }
      bin->currentPage  = page->prev;
    } else {
      bin->currentPage  = page->next;
    }
  }
  if (bin->lastPage == page) {
    assert((NULL != page->prev) && (NULL == page->next));
    bin->lastPage = page->prev;
  } else {
    assert(NULL != page->next);
    page->next->prev  = page->prev;
  }
  if (NULL != page->prev)
    page->prev->next  = page->next;
}

/**
 * @fn void xInsertPageToBin(xPage page, xBin* bin)
 *
 * @brief Inserts the newly allocated @var xPage @var page to @var bin.
 *
 * @param page @var xPage the new page
 *
 * @param bin @var xBin* the new page becomes a part of
 *
 */
static inline void xInsertPageToBin(xPage page, xBin bin) {
  if (__XMALLOC_ZERO_PAGE == bin->currentPage) {
    page->prev          = NULL;
    page->next          = NULL;
    bin->currentPage = page;
    bin->lastPage    = page;
  } else {
    if (bin->currentPage == bin->lastPage) {
      bin->lastPage = page;
    } else {
      bin->currentPage->next->prev  = page;
    }
    page->next                = bin->currentPage->next;
    bin->currentPage->next = page;
    page->prev                = bin->currentPage;
  }
}

/**
 * @fn xPage xAllocNewPageForBin(xBin bin)
 *
 * @brief Allocates a new @var xPage to @var bin.
 *
 * @param bin @var xBin the new page becomes a part of
 *
 * @return @var xPage allocated
 */
xPage xAllocNewPageForBin(xBin bin);

/**
 * @fn xPage xAllocSmallBlockPageForBin()
 *
 * @brief Allocates a new @var xPage for small block free lists.
 *
 * @note This function does NEITHER subdivide NOR structure the allocated page.
 * This must be done afterwards
 *
 * @return @var xPage allocated.
 *
 */
xPage xAllocSmallBlockPageForBin();

/**
 * @fn xPage xAllocBigBlockPagesForBin(int numberNeeded)
 *
 * @brief Allocates new @var xPages for big block memory.
 *
 * @param numberNeeded is the number of pages to be allocated.
 *
 * @note This function does NEITHER subdivide NOR structure the allocated pages.
 * This must be done afterwards.
 *
 * @return @var xPage representing the first one of @var numberNeeded @var
 * xPages needed for this allocation
 *
 */
xPage xAllocBigBlockPagesForBin(int numberNeeded);

/************************************************
 * ALLOCATING PAGES IN BINS
 ***********************************************/
/**
 * @fn void xAllocFromFullPage(xBin* bin)
 *
 * @brief Returns memory address from a newly allocated page.
 *
 * @param bin @var xBin* the new page becomes a part of
 *
 * @return address of allocated memory
 *
 */
static inline void* xAllocFromFullPage(xBin bin) {
  xPage newPage;
  if (__XMALLOC_ZERO_PAGE != bin->currentPage) {
    bin->currentPage->numberUsedBlocks  = 0;
  }

  if(!bin->sticky && (NULL != bin->currentPage->next)) {
    assert(NULL != bin->currentPage->next->current);
    newPage = bin->currentPage->next;
  } else {
    newPage = xAllocNewPageForBin(bin);
    assert((NULL != newPage) && (newPage != __XMALLOC_ZERO_PAGE) &&
           (NULL != newPage->current));
    assert(NULL != newPage);
    xInsertPageToBin(newPage, bin);
  }

  bin->currentPage  = newPage;
  return xAllocFromNonEmptyPage(newPage);
}

/************************************************
 * FREEING BINS
 ***********************************************/
/**
 * @fn static inline void xFreeBin(void *addr)
 *
 * @brief Frees the memory of @var addr .
 *
 * @param addr memory address that should be freed.
 *
 */
static inline void xFreeBin(void *addr) {
    register void *__addr = (void*) addr;
    register xPage __page = (xPage) xGetPageOfAddr(__addr);
    xFreeToPage(__addr, __page);
}

/************************************************
 * ALLOCATING MEMORY FROM BINS
 ***********************************************/
/**
 * @fn static inline void xAllocFromBin(xBin bin)
 *
 * @brief Generic memory allocation from @var bin.
 *
 * @param bin @var xBin the bin memory should be allocated from
 *
 * @return address of allocated memory
 *
 */
static inline void* xAllocFromBin(xBin bin) {
  register xPage page = bin->currentPage;
  if (page->current != NULL)
    return xAllocFromNonEmptyPage(page);
  else
    return xAllocFromFullPage(bin);
}

/**
 * @fn static inline void xAlloc0FromBin(xBin bin)
 *
 * @brief Generic memory allocation from @var bin , sets to zero.
 *
 * @param bin @var xBin the bin memory should be allocated from
 *
 * @return address of allocated memory
 *
 */
static inline void* xAlloc0FromBin(xBin bin) {
  void *addr  = xAllocFromBin(bin);
  memset(addr, 0, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
  return addr;
}

/************************************************
 * DEBUGGING INFORMATION
 ***********************************************/
//#ifdef __XMALLOC_DEBUG
/**
 * @fn static inline xBin xGetTopBinOfPage(const xPage page)
 *
 * @brief Get top bin the page @var page .
 *
 * @param page Const @var xPage .
 *
 * @return top @var xBin of @var xPage @var page
 *
 */
static inline xBin xGetTopBinOfPage(const xPage page) {
  return((xBin) ((unsigned long) page->bin));
}

/**
 * @fn static inline xBin xGetBinOfPage(const xPage page)
 *
 * @brief Get top bin the page @var page .
 *
 * @param page Const @var xPage .
 *
 * @return top @var xBin of @var xPage @var page
 *
 */
static inline xBin xGetBinOfPage(const xPage page) {
  unsigned long sticky  = xGetStickyOfPage(page);
  xBin bin              = xGetTopBinOfPage(page);

  if (!xIsStickyBin(bin)) // TOODOO
    while ((bin->sticky != sticky) && (NULL != bin->next))
      bin = bin->next;

  return bin;
}

/**
 * @fn xPage xGetPageFromBin(xBin bin)
 *
 * @brief Gets a currently free page from @var bin.
 *
 * @param bin @var xBin the bin the page should be part of
 *
 * @return „current free @var xPage from @var bin
 *
 */
xPage xGetPageFromBin(xBin bin);
//#endif
#endif
