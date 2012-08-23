/**
 * @file   xPage.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Page handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_PAGE_H
#define X_PAGE_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "src/xDataStructures.h"
#include "src/xGlobals.h"
#include "src/xRegion.h"


void xFreeToPageFault(xPage page, void *addr);
void xPageIndexFault(unsigned long startIndex, unsigned long endIndex);

/***********************************************************************
 *
 * Identifying whether an address is an xPageAddr or not:
 *
 *******************************************************************/

/* For this explanation assume that
    __XMALLOC_SIZEOF_LONG == 2^2,
    __XMALLOC_SIZEOF_LOG_LONG == 2,
    __XMALLOC_SIZEOF_BIT_LOG_LONG == 5,
    __XMALLOC_SIZEOF_SYSTEM_PAGE = 2^12:

   Let
   addr: |    15      |  5       |    12        |
          PAGE_INDEX   PAGE_SHIFT PAGE_OFFSET    PAGE_BASE

  xPageShifts is an array of bit-fields which is indexed by
  xGetPageIndexOfAddr(addr) - xMinPageIndex.
  Its maximal length is 2^15.

  xGetPageShiftOfAdd(addr) is used as index into the bit-field.

  If it's value is 1, then addr is from xPage, else not.

  xMinPageIndex is the minimal page index of all registered xPageAddr

  In other words:
    xIsBinPageAddr(addr) <=> (xGetPageIndexOfAddr(addr) >= xMinPageIndex &&
                              xGetPageIndexOfAddr(addr) <= xMaxPageIndex &&
                              xPageIndicies[xGetPageIndexOfAddr(addr) -
                              xMinPageIndex] & (1 << xGetPageShiftOfAddr(addr)))
*/

/**
 * @fn static inline unsigned long xGetPageShiftOfAddr(const void *addr)
 *
 * @brief Computes the page shift for address \var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline unsigned long xGetPageShiftOfAddr(const void *addr) {
  return((((unsigned long) addr) & (__XMALLOC_SIZEOF_INDEX_PAGE_MINUS_ONE))
      >> __XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE);
}

/**
 * @fn static inline unsigned long xGetPageIndexOfAddr(const void *addr)
 *
 * @brief Computes the page index for address \var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline unsigned long xGetPageIndexOfAddr(const void *addr) {
  return(((unsigned long) addr) >> __XMALLOC_INDEX_PAGE_SHIFT);
}

/**
 * @fn static inline xBin xGetHeadOfBinAddr(const void *addr) {
 *
 * @brief Get head of bin the memory chunk at address \var addr is stored in.
 *
 * @param addr Const pointer to the corresponding address.
 *
 */
static inline xPage xGetPageOfBinAddr(const void *addr) {
  return((xPage) ((long) addr & ~(__XMALLOC_SIZEOF_SYSTEM_PAGE - 1)));
}

/**
 * @fn static inline bool xIsPageAddr(const void *addr)
 *
 * @brief Checks if \var addr is an address in the xPages or not.
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline bool xIsPageAddr(const void *addr) {
  register unsigned long testAddr = xGetPageIndexOfAddr(addr);
  return((testAddr >= xMinPageIndex) &&
         (testAddr <= xMaxPageIndex) && 
         ((xPageShifts[testAddr - xMinPageIndex] & 
          ((unsigned long) 1) << xGetPageShiftOfAddr(addr)) != 0));
}

/**
 * @fn static inline void xAllocFromNonEmptyPage(void *addr, xPage page)
 *
 * @brief Sets \var addr to memory address from the non empty \var xPage \var
 * page.
 *
 * @param addr pointer to the corresponding address.
 * @param page \var xPage the memory should be allocated in.
 *
 */
static inline void xAllocFromNonEmptyPage(void *addr, xPage page) {
  page->numberUsedBlocks++;
  addr          = (void*) page->current;
  page->current = __XMALLOC_NEXT(page->current);
}

/**
 * @fn void xRegisterPages(void *startAddr, int numberPages)
 *
 * @brief Uses memory chunk of \var numberPages system pages and registers them
 * as \var xPages.
 *
 * @param startAddr address if the beginning of the memory chunk of continuous
 * system pages.
 * @param numberPages number of pages in the memory chunk to be registered
 *
 */
void xRegisterPages(void *startAddr, int numberPages);

/************************************************
 * INLINED PAGE TESTS / ADDRESS HANDLINGS
 ***********************************************/
/**
 * @fn static inline long xIsAddrPageAligned(void *addr)
 *
 * @brief Tests if \var addr is page aligned or not.
 *
 * @param addr memory address to be checked
 *
 */
static inline long xIsAddrPageAligned(void *addr) {
  return (((long) addr & (__XMALLOC_SIZEOF_SYSTEM_PAGE - 1)) == 0);
}

/**
 * @fn static inline xPage xGetPageOfAddr(void *addr)
 *
 * @brief Returns \var xPage \var addr is included in.
 *
 * @param addr memory address to be checked
 *
 */
static inline void* xGetPageOfAddr(void *addr) {
  return (void *) ((long) addr & ~(__XMALLOC_SIZEOF_SYSTEM_PAGE - 1));
}

/**
 * @fn static inline bool xIsAddrOnPage(void *addr, xPage page)
 *
 * @brief Checks if \var addr is on \var page .
 *
 * @param addr memory address to be checked
 * @param page \var xPage to be checked
 *
 */
static inline bool xIsAddrOnPage(void *addr, xPage page) {
  return(xGetPageOfAddr(addr) == page);
}

/**
 * @fn static inline bool xAreAddressesOnSamePage(void *addr1, void *addr2)
 *
 * @brief Checks if \var addr1 and \var addr2 lie on the same page.
 *
 * @param addr1 memory address to be checked
 * @param addr2 memory address to be checked
 *
 */
static inline bool xAreAddressesOnSamePage(void *addr1, void *addr2) {
  return(xGetPageOfAddr(addr1) == xGetPageOfAddr(addr2));
}

/************************************************
 * FREEING OPERATIONS CONCERNING PAGES
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
#endif
