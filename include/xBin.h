/**
 * @file   xBin.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Bin handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_BIN_H
#define X_BIN_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "include/xDataStructures.h"
#include "include/xGlobals.h"
#include "include/xPage.h"
#include "include/xRegion.h"

void* xAllocBin(xBin bin);

static inline void* xAlloc0Bin(xBin bin) {
  void *ptr = xAllocBin(bin);
  memset(ptr, 0, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
  return ptr;
}

xBin xGetSpecBin(size_t size);
void xUnGetSpecBin(xBin *bin);

/**
 * @fn xPage xGetPageFromBin(xBin bin)
 *
 * @brief Gets a currently free page from \var bin.
 *
 * @param bin \var xBin the bin the page should be part of
 *
 */
xPage xGetPageFromBin(xBin bin);
  
/**
 * @fn void xInsertPageToBin(xBin bin, xPage page)
 *
 * @brief Inserts the newly allocated \var xPage \var page to \var bin.
 *
 * @param bin \var xBin the new page becomes a part of 
 * @param page \var xPage the new page 
 *
 */
void xInsertPageToBin(xBin bin, xPage page);

/**
 * @fn xPage xAllocNewPageForBin(xBin bin) 
 *
 * @brief Allocates a new \var xPage to \var bin.
 *
 * @param bin \var xBin the new page becomes a part of 
 *
 */
xPage xAllocNewPageForBin(xBin bin);

/**
 * @fn xPage xAllocSmallBlockPageForBin()
 *
 * @brief Allocates a new \var xPage for small block free lists.
 *
 * @note This function does NEITHER subdivide NOR structure the allocated page.
 * This must be done afterwards.
 *
 */
xPage xAllocSmallBlockPageForBin();

/**
 * @fn xPage xAllocBigBlockPagesForBin(int numberNeeded)
 *
 * @brief Allocates new \var xPages for big block memory.
 *
 * @param numberNeeded is the number of pages to be allocated.
 *
 * @note This function does NEITHER subdivide NOR structure the allocated pages.
 * This must be done afterwards.
 *
 */
xPage xAllocBigBlockPagesForBin(int numberNeeded);

/**
 * @fn void xAllocFromFullPage(void *addr, xBin bin)
 *
 * @brief Sets \var addr to memory address from a newly allocated page.
 *
 * @param addr pointer to the corresponding address.
 * @param bin \var xBin the new page becomes a part of 
 *
 */
void xAllocFromFullPage(void *addr, xBin bin);


/************************************************
 * FREEING BINS
 ***********************************************/
inline void xFreeBin(void *addr) {
    register void *__addr = (void*) addr;
    register xPage __page = xGetPageOfAddr(__addr);
    xFreeToPage(__addr, __page);
}

#endif
