/* Copyright 2012 Christian Eder
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#ifndef X_PAGE_H
#define X_PAGE_H

static inline unsigned long xGetPageShitOfAddr(const void *addr) {
  return((((unsigned long) addr) & (__XMALLOC_SIZEOF_INDEX_PAGE_MINUS_ONE))
      >> __XMALLOC_LOG_BIT_SIZEOF_SYSTEM_PAGE);
}

static inline unsigned long xGetPageIndexOfAddr(const void *addr) {
  return(((unsigned long) addr) >> __XMALLOC_INDEX_PAGE_SHIFT);
}

static inline bool xIsPageAddr(const void *addr) {
  register unsigned long testAddr = xGetPageIndexOfAddr(addr);
  return((testAddr >= xMinPageIndex) &&
         (testAddr <= xMaxPageIndex) && 
         ((xPageIndices[testAddr - xMinPageIndex] & 
          ((unsigned long) 1) << xGetPageShiftOfAddr(addr)) != 0));
}

static inline size_t xSizeOfAddr(void *addr) {
  return(xIsPageAddr(addr) ? xSizeOfBinAddr(addr) : xSizeOfLargeAddr(addr));
}

#endif
