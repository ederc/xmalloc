/**
 * \file   xmalloc.h
 * \Author Christian Eder ( ederc\mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  General header file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_XMALLOC_H
#define XMALLOC_XMALLOC_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.

#define X_XMALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include "xassert.h"
#include "xmalloc-config.h"
#include "system.h"
#include "data.h"
#include "globals.h"
#include "page.h"
#include "bin.h"
#include "region.h"
#include "align.h"

// needed exactly here
extern xBin xSize2Bin[];
#define xSmallSize2Bin(size)                              \
  xSize2Bin[((size)-1) >> __XMALLOC_LOG_SIZEOF_ALIGNMENT]

/****************************************************
 * DEBUG STUFF:
 * predeclarations, for implementations see bottom
 * of this file
 ***************************************************/
  /*
#ifdef DEBUG
static inline xBin xGetHeadOfBinAddr(const void *addr);
static inline size_t xWordSizeOfBinAddr(const void *addr);
static inline size_t xSizeOfBinAddr(const void *addr);
static inline size_t xSizeOfAddr(const void *addr);
#endif
*/

/*********************************************************
 * DEBUGGING INFORMATION
 ********************************************************/
//#ifdef __XMALLOC_DEBUG
/**
 * \fn static inline xBin xGetHeadOfBinAddr(const void *addr)
 *
 * \brief Get head of bin the memory chunk at address \c addr is stored in.
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return head of \c xBin \c addr is in
 */
static inline xBin xGetHeadOfBinAddr(const void *addr) {
#if __XMALLOC_DEBUG > 1
  printf("gpoba %p\n", xGetPageOfBinAddr(addr));
#endif
  return xGetTopBinOfPage((xPage) xGetPageOfBinAddr(addr));
}

/**
 * \fn static inline size_t xWordSizeOfBinAddr(const void *addr)
 *
 * \brief Get the word size of the memory chunk stored at address \c addr .
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return size in words of address \c addr
 *
 */
static inline size_t xWordSizeOfBinAddr(const void *addr) {
  return xGetHeadOfBinAddr(addr)->sizeInWords;
}

/**
 * \fn static inline size_t xSizeOfBinAddr(const void *addr)
 *
 * \brief Get the size of the memory chunk stored at address \c addr .
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return size of address \c addr
 *
 */
static inline size_t xSizeOfBinAddr(const void *addr) {
  return(xWordSizeOfBinAddr(addr) << __XMALLOC_LOG_SIZEOF_LONG);
}

/**
 * \fn static inline size_t xSizeOfLargeAddr(const void *addr)
 *
 * \brief Get the size of the memory chunk stored at address \c addr .
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return size of address \c addr
 */
static inline size_t xSizeOfLargeAddr(const void *addr) {
  return *((size_t *) ((char *) addr - __XMALLOC_SIZEOF_STRICT_ALIGNMENT));
}

/**
 * \fn static inline size_t xSizeOfAddr(const void *addr)
 *
 * \brief Get the size of the memory chunk stored at address \c addr .
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return size of address \c addr
 */
static inline size_t xSizeOfAddr(const void *addr) {
  return(xIsBinAddr(addr) ? xSizeOfBinAddr(addr) : xSizeOfLargeAddr(addr));
}

/**
 * \fn static inline size_t xWordSizeOfAddr(const void *addr)
 *
 * \brief Get the word size of the memory chunk stored at address \c addr .
 *
 * \param addr Const pointer to the corresponding address.
 *
 * \return size of address \c addr
 */
static inline size_t xWordSizeOfAddr(const void *addr) {
  return(xIsBinAddr(addr) ? xWordSizeOfBinAddr(addr) :
          xSizeOfLargeAddr(addr) >> __XMALLOC_LOG_SIZEOF_LONG);
}
//#endif


/*********************************************************
 * GENERAL MALLOC AND FREE STUFF
 ********************************************************/
/**
 * \fn static inline void* xMalloc(const size_t size)
 *
 * \brief Allocates memory of size class \c size .
 *
 * \param size Const \c size_t giving size class. 
 *
 * \return address of memory allocated
 *
 * \note It is assumed that \c size > 0.
 *
 */
static inline void* xMalloc(const size_t size) {
  void *addr  = NULL;
  if (size <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin bin  = xSmallSize2Bin(size); 
    addr      = xAllocFromBin(bin);
    return addr;
  } else {
    long *ptr  = (long*) malloc(size + __XMALLOC_SIZEOF_LONG);
    *ptr       = size;
    ptr++;
    return ptr;
  }
}

/**
 * \fn static inline void* xMalloc0(const size_t size)
 *
 * \brief Allocates memory of size class \c size and initializes everything to
 * zero.
 *
 * \param size Const \c size_t giving size class.
 *
 * \return address of memory allocated
 *
 * \note It is assumed that \c size > 0.
 *
 */
static inline void* xMalloc0(size_t size) {
  void *addr  = NULL;
  if (size <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin bin  = xSmallSize2Bin(size);
    addr      = xAllocFromBin(bin);
    xMemsetInWords(addr, 0, bin->sizeInWords);
    return addr;
  } else {
    long *ptr  = (long*) malloc(size + __XMALLOC_SIZEOF_LONG);
    *ptr       = size;
    ptr++;
    memset(ptr, 0, size);
    return ptr;
  }
}

/**
 * \fn static inline void* xmalloc(const size_t size)
 *
 * \brief Allocates memory of size class \c size .
 *
 * \return address of memory allocated
 *
 * \param size Const \c size_t giving size class. \c size can be 0.
 *
 */
static inline void* xmalloc(const size_t size) {
  if (size > 0)
    return xMalloc(size);
  else
    return NULL;
}

/**
 * \fn static inline void xFreeBinAddr(void *addr)
 *
 * \brief Frees memory stored at address \c addr .
 *
 * \param addr address of memory to be deleted. 
 *
 * \note It is assumed that \c addr != NULL.
 *
 */
static inline void xFreeBinAddr(void *addr) {
  register void *__addr = addr;
  register xPage __page = (xPage) xGetPageOfAddr(__addr);
  xFreeToPage(__page, __addr);
}

/**
 * \fn static inline void xFreeBin(void *addr, xBin bin)
 *
 * \brief Frees memory stored at address \c addr .
 *
 * \param addr address of memory to be deleted. 
 *
 * \param bin \c xBin \c addr is stored in. 
 *
 * \note It is assumed that \c addr != NULL.
 *
 */
static inline void xFreeBin(void *addr, xBin bin) {
  register void *__addr = addr;
  register xPage __page = (xPage) xGetPageOfAddr(__addr);
  xFreeToPage(__page, __addr);
}

/**
 * \fn static inline void xFreeLargeAddr(void *addr)
 *
 * \brief Frees memory stored at address \c addr .
 *
 * \param addr address of memory to be deleted. 
 *
 * \note It is assumed that \c addr != NULL.
 *
 */
static inline void xFreeLargeAddr(void *addr) {
  char *_addr  = (char *)addr - __XMALLOC_SIZEOF_STRICT_ALIGNMENT;
  xFreeSizeToSystem(_addr,*((size_t*) _addr) + __XMALLOC_SIZEOF_STRICT_ALIGNMENT);
}

/**
 * \fn static inline void xFree(void *addr)
 *
 * \brief Frees memory stored at address \c addr .
 *
 * \param addr address of memory to be deleted. 
 *
 * \note It is assumed that \c addr != NULL.
 *
 */
static inline void xFree(void *addr) {
  if (xIsBinAddr(addr))
    xFreeBinAddr(addr);
  else
    xFreeLargeAddr(addr);
}

/**
 * \fn static inline void xFreeSize(void *addr, size_t size) {
 *
 * \brief Frees memory stored at address \c addr with a size check included.
 *
 * \param addr address of memory to be deleted. 
 *
 * \note It is assumed that \c addr != NULL.
 *
 */
static inline void xFreeSize(void *addr, size_t size) {
  __XMALLOC_ASSERT(NULL != addr);
  __XMALLOC_ASSERT(0 != size);
  if ((size <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) || xIsBinAddr(addr))
    xFreeBinAddr(addr);
  else
    xFreeLargeAddr(addr);
}

/**
 * \fn static inline void xfree(void *addr)
 *
 * \brief Frees memory stored at address \c addr .
 *
 * \param addr address of memory to be deleted. 
 *
 * \note If \c addr == NULL, then freeing does not take place.
 *
 */
static inline void xfree(void *addr) {
  if (NULL != addr)
    xFree(addr);
}

/**
 * \fn static inline void xfreeSize(void *addr, size_t size) {
 *
 * \brief Frees memory stored at address \c addr with a size check included.
 *
 * \param addr address of memory to be deleted.
 *
 */
static inline void xfreeSize(void *addr, size_t size) {
  if ((NULL != addr) && (0 != size))
    return xFreeSize(addr, size);
}

void xFreeSizeFunc(void *ptr, size_t size);

xRegion xIsBinBlock(unsigned long region);

/************************************************
 * ALLOCATION AND FREEING OF SPECIAL BINS
 * NOTE: This needs to be located here since
 *       it depends on xMalloc()
 ***********************************************/
/**
 * \fn xBin xGetSpecBin(size_t size);
 *
 * \brief Returns a special bin for monomial handling
 *
 * \param size \c size_t size class of the monomials
 *
 * \return \c xBin of the \c xSpecBin of size class \c size
 */
xBin xGetSpecBin(size_t size);

/**
 * \fn void xUnGetSpecBin(xBin *oldBin, int remove);
 */
void xUnGetSpecBin(xBin *oldBin, int remove);


/**
 * \fn void* xReallocLarge(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk from system. For this it
 * takes care of xmallocs alignment of those big memory chunks.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
void* xReallocLarge(void *oldPtr, size_t newSize);

/**
 * \fn void* xRealloc0Large(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk from system and initializes
 * everything to zero. For this it takes care of xmallocs alignment of those
 * big memory chunks.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
void* xRealloc0Large(void *oldPtr, size_t newSize);

/**
 * \fn void* xReallocSize(void *oldPtr, size_t oldSize, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param oldSize size of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
void* xReallocSize(void *oldPtr, size_t oldSize, size_t newSize);

/**
 * \fn void* xRealloc0Size(void *oldPtr, size_t oldSize, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk and initializes everything to
 * zero.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param oldSize size of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 *
 * \note Assumes that \c oldPtr != NULL.
 */
void* xRealloc0Size(void *oldPtr, size_t oldSize, size_t newSize);

/**
 * \fn void* xReallocSize(void *oldPtr, size_t oldSize, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk. xmalloc uses \c oldSize
 * to find possibly fitting \c xBins for an optimized allocation.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param oldSize size of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunka
 *
 * \note Assumes that \c oldPtr != NULL.
 */
static inline void* xreallocSize(void *oldPtr, size_t oldSize, size_t newSize) {
  if (!newSize)
    newSize = (size_t) 1;
  if (NULL != oldPtr)
    return xReallocSize(oldPtr, oldSize, newSize);
  else
    return xMalloc(newSize);
}

/**
 * \fn void* xRealloc0Size(void *oldPtr, size_t oldSize, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk and initializes everything to
 * zero. xmalloc uses \c oldSize to find possibly fitting
 * \c xBins for an optimized allocation.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param oldSize size of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
static inline void* xrealloc0Size(void *oldPtr, size_t oldSize, size_t newSize) {
  if (!newSize)
    newSize = (size_t) 1;
  if (NULL != oldPtr)
    return xRealloc0Size(oldPtr, oldSize, newSize);
  else
    return xMalloc0(newSize);
}

/**
 * \fn void* xDoRealloc(void *oldPtr, size_t newSize, int initZero)
 *
 * \brief Reallocates memory to \c newSize chunk. For this it checks if \c
 * newSize is smaller than \c __XMALLOC_MAX_SMALL_BLOCK_SIZE . If this is true
 * it allocates the new memory from xmallocs \c xBin structures. Otherwise a
 * system reallocation is done via \fn xReallocLarge resp. \fn xRealloc0Large .
 * If the corresponding flag \c initZero is set, then all new memory is
 * initialized to zero.
 *
 * \param oldPtr address of old memory chunk
 *
 * \param oldSize size of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \param initZero initializes memory to zero if flag is set to 1
 *
 * \return address of new memory chunk
 *
 * \note Assumes that \c newSize =/= 0 and \c oldPtr =/= NULL .
 *
 */
void* xDoRealloc(void *oldPtr, size_t oldSize, size_t newSize, int initZero);

/**
 * \fn static inline void* xRealloc0(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk and initializes everything to
 * zero. Computes the size of the old memory chunk first, then calls
 * \fn xRealloc0Size .
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 *
 * \note Assumes that \c newSize =/= 0 and \c oldPtr =/= NULL .
 *
 */
static inline void* xRealloc0(void *oldPtr, size_t newSize) {
  size_t oldSize = xSizeOfAddr(oldPtr);
  return xRealloc0Size(oldPtr, oldSize, newSize);
}

/**
 * \fn static inline void* xRealloc(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk. Computes the size of the old
 * memory chunk first, then calls \fn xReallocSize .
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 *
 * \note Assumes that \c newSize =/= 0 and \c oldPtr =/= NULL .
 *
 */
static inline void* xRealloc(void *oldPtr, size_t newSize) {
  size_t oldSize = xSizeOfAddr(oldPtr);
  return xReallocSize(oldPtr, oldSize, newSize);
}

/**
 * \fn static inline void* xrealloc0(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk and initializes everything to
 * zero. Checks input data first, then calls \fn xRealloc0 .
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
static inline void* xrealloc0(void *oldPtr, size_t newSize) {
  if (!newSize)
    newSize = (size_t) 1;
  if (NULL != oldPtr)
    return xRealloc0(oldPtr, newSize);
  else
    return xMalloc0(newSize);
}

/**
 * \fn static inline void* xrealloc(void *oldPtr, size_t newSize)
 *
 * \brief Reallocates memory to \c newSize chunk. Checks input data first,
 * then calls \fn xRealloc .
 *
 * \param oldPtr address of old memory chunk
 *
 * \param newSize size of new memory chunk
 *
 * \return address of new memory chunk
 */
static inline void* xrealloc(void *oldPtr, size_t newSize) {
  if (!newSize)
    newSize = (size_t) 1;
  if (NULL != oldPtr)
    return xRealloc(oldPtr, newSize);
  else
    return xMalloc(newSize);
}

static inline char* xStrDup(const char *str) { 
  size_t length = strlen(str);
  char *newStr  = (char *)xMalloc(length + 1);
  return strcpy(newStr, str);
}

static inline void* xMemDup(void *str) { 
  size_t oldSize = xSizeOfAddr(str);
  void *newPtr   = xMalloc(oldSize);
  memcpy(newPtr, str, oldSize);
  return newPtr;
}


/************************************************
 * STICKY BUSINESS OF BINS
 ***********************************************/
/**
 * \fn xBin xGetStickyBinOfBin(xBin bin);
 *
 * \brief Gets the sticky bin of \c bin .
 *
 * \param bin \c xBin
 *
 * \return sticky bin of \c bin .
 *
 */
xBin xGetStickyBinOfBin(xBin bin);



#define xAlloc0Aligned(S)       xMalloc0(S)
#define xAllocAligned(S)        xMalloc(S)
#define xInitInfo()             
#define xInitGetBackTrace()
#define xPrintStats(F)
#define xPrintBinStats(F)
#define xMarkMemoryAsStatic()
#define xMarkAsStaticAddr(A)
#define xMemCpyW(A, B, S)         memcpy(A,B,(S)*__XMALLOC_SIZEOF_LONG)
#define xMemcpyW(A, B, S)         memcpy(A,B,(S)*__XMALLOC_SIZEOF_LONG)
#define memcpyW(A, B ,C)          memcpy(A,B,(C)*__XMALLOC_SIZEOF_LONG)
#define xFreeFunc                 xFree

/* debug dummies: */
#define xTypeReallocAlignedSize     xTypeReallocSize
#define xTypeRealloc0AlignedSize    xTypeRealloc0Size
#define xMemDupAligned              xMemDup
#define xCheckIf(cond, test)                    ((void) 0)
#define xCheckBinAddr(addr)                     ((void) 0)
#define xCheckAddrBin(addr, bin)                ((void) 0)
#define xCheckBinAddrSize(addr, size)           ((void) 0)
#define xCheckAddrSize(addr, size)              ((void) 0)
#define xCheckAddr(addr)                        ((void) 0)
#define xcheckAddrSize(addr, size)              ((void) 0)
#define xcheckAddr(addr)                        ((void) 0)
#define xCheckBin(bin)                          ((void) 0)
#define xCheckMemory()                          ((void) 0)
#define xPrintCurrentBackTraceMax(A, B)         ((void) 0)
#define xdebugAddrSize(A, B)                    ((void) 0)
#define xPrintAddrInfo(A, B, C)                 ((void) 0)
#ifdef x_NDEBUG
#define xTestBinAddrSize(A, B, C)               ((void) 0)
#else
#define xTestBinAddrSize(A, B, C)               xError_NoError
#endif
#define xTestList(A, B)                          xError_NoError
#define xInitRet_2_Info(argv0)                  ((void) 0)
#define xMergeStickyBinIntoBin(A, B)            ((void) 0)
#define xPrintUsedTrackAddrs(A, B)              ((void) 0)
#define xPrintUsedAddrs(A, B)                   ((void) 0)
#define xPrintCurrentBackTrace(A)               ((void) 0)

#ifdef __cplusplus
}
#endif

#undef XMALLOC_USES_MALLOC
#define X_XMALLOC
#define xMallocFunc xMalloc
#define xReallocSizeFunc xReallocSize
/* #define X_NDEBUG */
#undef X_SING_KEEP
#endif
