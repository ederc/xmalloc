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

/***********************************************************************
 *
 * Identifying whether an address is an xPageAddr or not:
 *
 *******************************************************************/

/* For this explanation assume that
    __XMALLOC_SIZEOF_LONG == 4 and
    __XMALLOC_SIZEOF_SYSTEM_PAGE = 2^12:

   Let
   addr: |    15      |  5       |    12        |
          PAGE_INDEX   PAGE_SHIFT PAGE_OFFSET    PAGE_BASE

  xPageIndices is an array of bit-fields which is indexed by
  xGetPageIndexOfAddr(addr) - om_MinBinPageIndex.
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
 * \brief Computes the page shift for address \var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline unsigned long xGetPageShitOfAddr(const void *addr) {
  return((((unsigned long) addr) & (__XMALLOC_SIZEOF_INDEX_PAGE_MINUS_ONE))
      >> __XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE);
}

/**
 * \brief Computes the page index for address \var addr .
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline unsigned long xGetPageIndexOfAddr(const void *addr) {
  return(((unsigned long) addr) >> __XMALLOC_INDEX_PAGE_SHIFT);
}

/**
 * \brief Checks if \var addr is an address in the xPages or not.
 *
 * @param addr Const pointer to the corresponding address
 *
 */
static inline bool xIsPageAddr(const void *addr) {
  register unsigned long testAddr = xGetPageIndexOfAddr(addr);
  return((testAddr >= xMinPageIndex) &&
         (testAddr <= xMaxPageIndex) && 
         ((xPageIndices[testAddr - xMinPageIndex] & 
          ((unsigned long) 1) << xGetPageShiftOfAddr(addr)) != 0));
}

/**
 * \brief Get the size of the memory chunk stored at address \var addr .
 *
 * @param addr Const pointer to the corresponding address.
 *
 */
static inline size_t xSizeOfAddr(const void *addr) {
  return(xIsPageAddr(addr) ? xSizeOfBinAddr(addr) : xSizeOfLargeAddr(addr));
}

#endif
