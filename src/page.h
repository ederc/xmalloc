/**
 * @file   page.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Page handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 * @note   There are some page based functions implemented in the bin.* 
 *         files since they depend internally on the strong page <-> bin
 *         connection. Those files are mentioned ( and commented out! ) 
 *         at the end of this file
 */

#ifndef XMALLOC_PAGE_H
#define XMALLOC_PAGE_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "xmalloc-config.h"
#include "data.h"
#include "globals.h"
#include "align.h"
#include "system.h"


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
 * @brief Computes the page shift for address @var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 * @return page shift of @var addr
 *
 */
static inline unsigned long xGetPageShiftOfAddr(const void *addr) {
  return((((unsigned long) addr) & (__XMALLOC_SIZEOF_INDEX_PAGE_MINUS_ONE))
      >> __XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE);
}

/**
 * @fn static inline unsigned long xGetPageIndexOfAddr(const void *addr)
 *
 * @brief Computes the page index for address @var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 * @return page index of @var addr
 *
 */
static inline unsigned long xGetPageIndexOfAddr(const void *addr) {
  return(((unsigned long) addr) >> __XMALLOC_INDEX_PAGE_SHIFT);
}

/**
 * @fn static inline xBin xGetHeadOfBinAddr(const void *addr) {
 *
 * @brief Get head of bin the memory chunk at address @var addr is stored in.
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return @var xPage @var addr is in
 *
 */
static inline xPage xGetPageOfBinAddr(const void *addr) {
  return((xPage) ((long) addr & ~(__XMALLOC_SIZEOF_SYSTEM_PAGE - 1)));
}

/**
 * @fn static inline BOOLEAN xIsBinAddr(const void *addr)
 *
 * @brief Checks if @var addr is an address in the xPages or not.
 *
 * @param addr Const pointer to the corresponding address
 *
 * @return true if @var addr is handled by xmalloc, false else
 *
 */
static inline BOOLEAN xIsBinAddr(const void *addr) {
  register unsigned long testAddr = xGetPageIndexOfAddr(addr);
#if __XMALLOC_DEBUG 
  printf("------!---------\n");
  printf("%ld\n",testAddr);
  printf("%ld\n",xMinPageIndex);
  printf("%ld\n",xMaxPageIndex);
  printf("------!---------\n");
  printf("%ld\n",xGetPageShiftOfAddr(addr));
#endif
  return((testAddr >= xMinPageIndex) &&
         (testAddr <= xMaxPageIndex) && 
         ((xPageShifts[testAddr - xMinPageIndex] & 
          (((unsigned long) 1) << xGetPageShiftOfAddr(addr))) != 0));
}

/**
 * @fn static inline void xAllocFromNonEmptyPage(xPage page)
 *
 * @brief Sets memory address from the non empty @var xPage @var
 * page.
 *
 * @param page @var xPage the memory should be allocated in.
 *
 * @return address of allocated memory
 *
 */
static inline void* xAllocFromNonEmptyPage(xPage page) {
  page->numberUsedBlocks++;
  //printf("page %p -- page->current %p\n", page, page->current);
  void *addr  = (void*) page->current;
  assert(NULL != addr);
  page->current = __XMALLOC_NEXT(page->current);
  return addr;
}

/************************************************
 * PAGE REGISTRATION
 ***********************************************/
/**
 * @fn void xPageIndexFault(unsigned long startIndex, unsigned long endIndex)
 *
 * @brief Fixes page indices problems occured during page registrations.
 *
 * @param startIndex lower index of region
 *
 * @param endIndex higher index of region
 *
 */
void xPageIndexFault(unsigned long startIndex, unsigned long endIndex);

/**
 * @fn void xRegisterPagesInRegion(void *startAddr, int numberPages)
 *
 * @brief Uses memory chunk of @var numberPages system pages and registers them
 * as @var xPages.
 *
 * @param startAddr address if the beginning of the memory chunk of continuous
 * system pages.
 *
 * @param numberPages number of pages in the memory chunk to be registered
 *
 */
void xRegisterPagesInRegion(void *startAddr, int numberPages);

/**
 * @fn void xUnregisterPagesInRegion(void *startAddr, int numberPages)
 *
 * @brief Uses memory chunk of @var numberPages system pages and unregisters
 * them.
 *
 * @param startAddr address if the beginning of the memory chunk of continuous
 * system pages.
 *
 * @param numberPages number of pages in the memory chunk to be unregistered
 *
 */
void xUnregisterPagesFromRegion(void *startAddr, int numberPages);

/************************************************
 * INLINED PAGE TESTS / ADDRESS HANDLINGS
 ***********************************************/
/**
 * @fn static inline BOOLEAN xIsAddrPageAligned(void *addr)
 *
 * @brief Tests if @var addr is page aligned or not.
 *
 * @param addr memory address to be checked
 *
 * @return true if @var addr is aligned, false else
 *
 */
static inline BOOLEAN xIsAddrPageAligned(void *addr) {
  return (((long) addr & (__XMALLOC_SIZEOF_SYSTEM_PAGE - 1)) == 0);
}

/**
 * @fn static inline xPage xGetPageOfAddr(void *addr)
 *
 * @brief Returns @var xPage @var addr is included in.
 *
 * @param addr memory address to be checked
 *
 * @return address of @var xPage @var addr is in
 */
static inline void* xGetPageOfAddr(void *addr) {
  return (void *) ((long) addr & ~(__XMALLOC_SIZEOF_SYSTEM_PAGE - 1));
}

/**
 * @fn static inline BOOLEAN xIsAddrOnPage(void *addr, xPage page)
 *
 * @brief Checks if @var addr is on @var page .
 *
 * @param addr memory address to be checked
 *
 * @param page @var xPage to be checked
 *
 * @return true if @var addr is on @var page , false else
 */
static inline BOOLEAN xIsAddrOnPage(void *addr, xPage page) {
  return(xGetPageOfAddr(addr) == page);
}

/**
 * @fn static inline BOOLEAN xAreAddressesOnSamePage(void *addr1, void *addr2)
 *
 * @brief Checks if @var addr1 and @var addr2 lie on the same page.
 *
 * @param addr1 memory address to be checked
 *
 * @param addr2 memory address to be checked
 *
 * @return true if @var addr1 and @var addr2 are on the same page, false else
 */
static inline BOOLEAN xAreAddressesOnSamePage(void *addr1, void *addr2) {
  return(xGetPageOfAddr(addr1) == xGetPageOfAddr(addr2));
}

/************************************************
 * FREEING OPERATIONS CONCERNING PAGES: THOSE 
 * DEPEND ON BINS => THEY ARE IMPLEMENTED IN
 * BIN.*
 ***********************************************/
// void xFreeToPageFault(xPage page, void *addr);
// static inline void xFreeToPage(xPage page, void *addr);
#endif
