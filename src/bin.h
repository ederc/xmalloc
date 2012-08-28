/**
 * @file   xBin.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Bin handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
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
 * GET BIN INFORMATION FOR PAGES/ADDRESSES
 ***********************************************/
/**
 * @fn void xInsertPageToBin(xBin bin, xPage page)
 *
 * @brief Inserts the newly allocated @var xPage @var page to @var bin.
 *
 * @param bin @var xBin the new page becomes a part of
 *
 * @param page @var xPage the new page
 *
 */
void xInsertPageToBin(xBin bin, xPage page);

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

/**
 * @fn void xAllocFromFullPage(void *addr, xBin bin)
 *
 * @brief Sets @var addr to memory address from a newly allocated page.
 *
 * @param addr pointer to the corresponding address.
 * @param bin @var xBin the new page becomes a part of
 *
 */
void xAllocFromFullPage(void *addr, xBin bin);


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
 * @fn static inline void xAllocFromBin(void *addr, xBin bin)
 *
 * @brief Generic memory allocation from @var bin.
 *
 * @param addr memory address the allocated memory is stored in
 *
 * @param bin @var xBin the bin memory should be allocated from
 *
 */
static inline void xAllocFromBin(void *addr, xBin bin) {
  register xPage page = bin->currentPage;
  if (page->current != NULL)
    xAllocFromNonEmptyPage(addr, page);
  else
    xAllocFromFullPage(addr, bin);
}

static inline void xAlloc0FromBin(void *addr, xBin bin) {
  xAllocFromBin(addr, bin);
  memset(addr, 0, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
}

/************************************************
 * DEBUGGING INFORMATION
 ***********************************************/
//#ifdef __XMALLOC_DEBUG
/**
 * @fn static inline xBin xGetTopBinOfPage(const xPage page) {
 *
 * @brief Get top bin the page @var page .
 *
 * @param page Const @var xPage .
 *
 * @return top @var xBin of @var xPage @var page
 *
 */
static inline xBin xGetTopBinOfPage(const xPage page) {
  return((xBin) ((unsigned long) page->bin)); // TOODOO
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

/**
 * @fn void xInsertPageToBin(xBin bin, xPage page)
 *
 * @brief Inserts the newly allocated @var xPage @var page to @var bin.
 *
 * @param bin @var xBin the new page becomes a part of
 *
 * @param page @var xPage the new page
 *
 */
void xInsertPageToBin(xBin bin, xPage page);
//#endif
#endif
