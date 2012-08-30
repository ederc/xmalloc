/**
 * @file   xmalloc.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General header file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_XMALLOC_H
#define XMALLOC_XMALLOC_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "src/data.h"
#include "src/globals.h"
#include "src/page.h"
#include "src/bin.h"
#include "src/region.h"
#include "src/align.h"

#define X_XMALLOC

#ifdef __cplusplus
extern "C" {
#endif

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
 * @fn static inline xBin xGetHeadOfBinAddr(const void *addr)
 *
 * @brief Get head of bin the memory chunk at address @var addr is stored in.
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return head of @var xBin @var addr is in
 */
static inline xBin xGetHeadOfBinAddr(const void *addr) {
  return xGetTopBinOfPage((xPage) xGetPageOfBinAddr(addr));
}

/**
 * @fn static inline size_t xWordSizeOfBinAddr(const void *addr)
 *
 * @brief Get the word size of the memory chunk stored at address @var addr .
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return size in words of address @var addr
 *
 */
static inline size_t xWordSizeOfBinAddr(const void *addr) {
  return xGetHeadOfBinAddr(addr)->sizeInWords;
}

/**
 * @fn static inline size_t xSizeOfBinAddr(const void *addr)
 *
 * @brief Get the size of the memory chunk stored at address @var addr .
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return size of address @var addr
 *
 */
static inline size_t xSizeOfBinAddr(const void *addr) {
  return(xWordSizeOfBinAddr(addr) << __XMALLOC_LOG_SIZEOF_LONG);
}

/**
 * @fn static inline size_t xSizeOfLargeAddr(const void *addr)
 *
 * @brief Get the size of the memory chunk stored at address @var addr .
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return size of address @var addr
 */
static inline size_t xSizeOfLargeAddr(const void *addr) {
  return *((size_t *) ((char *) addr - __XMALLOC_SIZEOF_STRICT_ALIGNMENT));
}

/**
 * @fn static inline size_t xSizeOfAddr(const void *addr)
 *
 * @brief Get the size of the memory chunk stored at address @var addr .
 *
 * @param addr Const pointer to the corresponding address.
 *
 * @return size of address @var addr
 */
static inline size_t xSizeOfAddr(const void *addr) {
  return(xIsBinAddr(addr) ? xSizeOfBinAddr(addr) : xSizeOfLargeAddr(addr));
}
//#endif


/*********************************************************
 * GENERAL MALLOC AND FREE STUFF
 ********************************************************/
/**
 * @fn static inline void* xMalloc(const size_t size)
 *
 * @brief Allocates memory of size class @var size .
 *
 * @param size Const @var size_t giving size class. 
 *
 * @return address of memory allocated
 *
 * @note It is assumed that @var size > 0.
 *
 */
static inline void* xMalloc(const size_t size) {
  void *addr  = NULL;
  if (size <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin bin  = xSmallSize2Bin(size); 
    assert(NULL != bin);
    addr  = xAllocFromBin(bin);
    assert(NULL != addr);
    return addr;
  } else {
     long *ptr  = (long*) malloc(size + __XMALLOC_SIZEOF_LONG);
     *ptr       = size;
     ptr++;
     return ptr;
  }
}

/**
 * @fn static inline void* xmalloc(const size_t size)
 *
 * @brief Allocates memory of size class @var size .
 *
 * @return address of memory allocated
 *
 * @param size Const @var size_t giving size class. @var size can be 0.
 *
 */
static inline void* xmalloc(const size_t size) {
  if (size > 0)
    return xMalloc(size);
  else
    return NULL;
}

/**
 * @fn static inline void xFreeBinAddr(void *addr)
 *
 * @brief Frees memory stored at address @var addr .
 *
 * @param addr address of memory to be deleted. 
 *
 * @note It is assumed that @var addr != NULL.
 *
 */
static inline void xFreeBinAddr(void *addr) {
  register void *__addr = addr;
  register xPage __page = xGetPageOfAddr(__addr);
  xFreeToPage(__addr, __page); // TOODOO
}

/**
 * @fn static inline void xFreeLargeAddr(void *addr)
 *
 * @brief Frees memory stored at address @var addr .
 *
 * @param addr address of memory to be deleted. 
 *
 * @note It is assumed that @var addr != NULL.
 *
 */
static inline void xFreeLargeAddr(void *addr) {
  free(addr);
}

/**
 * @fn static inline void xFree(void *addr)
 *
 * @brief Frees memory stored at address @var addr .
 *
 * @param addr address of memory to be deleted. 
 *
 * @note It is assumed that @var addr != NULL.
 *
 */
static inline void xFree(void *addr) {
  if (xIsBinAddr(addr))
    xFreeBinAddr(addr);
  else
    xFreeLargeAddr(addr); // TOODOO
}

/**
 * @fn static inline void xfree(void *addr)
 *
 * @brief Frees memory stored at address @var addr .
 *
 * @param addr address of memory to be deleted. 
 *
 * @note If @var addr == NULL, then freeing does not take place.
 *
 */
static inline void xfree(void *addr) {
  if(NULL != addr)
    xFree(addr);
}

void xFreeSizeFunc(void *ptr, size_t size);

xRegion xIsBinBlock(unsigned long region);

static inline void* xMalloc0(size_t size) {
  void *ptr = xMalloc(size);
  memset(ptr, 0, size); 
  return ptr; 
}

/************************************************
 * ALLOCATION AND FREEING OF SPECIAL BINS
 * NOTE: This needs to be located here since
 *       it depends on xMalloc()
 ***********************************************/
/**
 * @fn xBin xGetSpecBin(size_t size);
 *
 * @brief Returns a special bin for monomial handling
 *
 * @param size @var size_t size class of the monomials
 *
 * @return @var xBin of the @var xSpecBin of size class @var size
 */
xBin xGetSpecBin(size_t size);

void xUnGetSpecBin(xBin *bin);


static inline void* xRealloc0(void *oldPtr, size_t newSize) {
  void *newPtr = xMalloc0(newSize);
  if (oldPtr != NULL) {
    size_t oldSize = xSizeOfAddr(oldPtr);
    memcpy(newPtr, oldPtr, ((oldSize < newSize) ? oldSize : newSize));
    xFree(oldPtr);
  }
  return newPtr;
}

static inline void* xRealloc(void *oldPtr, size_t newSize) {
  void* newPtr = xMalloc(newSize);
  if (oldPtr != NULL) {
    size_t oldSize = xSizeOfAddr(oldPtr);
    memcpy(newPtr, oldPtr, ((oldSize < newSize) ? oldSize : newSize));
    xFree(oldPtr);
  }
  return newPtr;
}

static inline void* xReallocSize(void *oldPtr, size_t oldSize, size_t newSize) {
  void *newPtr = xMalloc(newSize);
  if (oldPtr != NULL) {
    memcpy(newPtr, oldPtr, ((oldSize < newSize) ? oldSize : newSize));
    xFree(oldPtr);
  }
  return newPtr;
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

//void xInfo();

#define xTypeAllocBin(T, P, B)  P=(T)xAllocBin(B)
#define xTypeAlloc(T, P, S)     P=(T)xMalloc(S)
#define xTypeAlloc0(T, P, S)    P=(T)xMalloc0(S)
#define xTypeAlloc0Bin(T, P, B) P=(T)xAlloc0Bin(B)
#define xAlloc0Aligned(S)       xMalloc0(S)
#define xAllocAligned(S)        xMalloc(S)
//#define xAllocBin(B)            xMalloc(B)
//#define xAlloc0Bin(B)           xMalloc0(B)
#define xInitInfo()             
#define xInitGetBackTrace()
#define xUpdateInfo()             
#define xPrintStats(F)
#define xPrintInfo(F)
#define xPrintBinStats(F)
#define xMarkMemoryAsStatic()
#define xFreeSize(P, S)           xFree(P)
#define xfreeSize(P, S)           xFreeSize(P,S)
#define xFreeBinAddr(P)           xFree(P)
#define xrealloc(A, NS)           xRealloc(A,NS)
#define xreallocSize(A, OS, NS)   xRealloc(A,NS)
#define xRealloc0Size(A, OS, NS)  xRealloc0(A,NS)
#define xrealloc0Size(A, OS, NS)  xRealloc(A,NS)
#define xMarkAsStaticAddr(A)
#define xMemCpyW(A, B, S)         memcpy(A,B,(S)*__XMALLOC_SIZEOF_LONG)
#define xMemcpyW(A, B, S)         memcpy(A,B,(S)*__XMALLOC_SIZEOF_LONG)
#define memcpyW(A, B ,C)          memcpy(A,B,(C)*__XMALLOC_SIZEOF_LONG)
#define xGetStickyBinOfBin(B)     (B)
#define xFreeFunc                 xFree

/* debug dummies: */
#define xTypeReallocAlignedSize     xTypeReallocSize
#define xTypeRealloc0AlignedSize    xTypeRealloc0Size
#define xReallocAlignedSize         xReallocSize
#define xRealloc0AlignedSize        xRealloc0Size
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
