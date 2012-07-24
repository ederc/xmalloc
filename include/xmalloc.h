/* Copyright 2012 Christian Eder
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#ifndef XMEMORY_H
#define XMEMORY_H

#include <stdlib.h>
#include <string.h>
#include "xmalloc-config.h"

#define X_XMALLOC

#ifdef __cplusplus
extern "C" {
#endif

enum xError_e {
  xError_NoError = 0,
  xError_Unknown,
  xError_InternalBug,
  xError_MemoryCorrupted,
  xError_NullAddr,
  xError_InvalidRangeAddr,
  xError_FalseAddr,
  xError_FalseAddrOrMemoryCorrupted,
  xError_WrongSize,
  xError_FreedAddr,
  xError_FreedAddrOrMemoryCorrupted,
  xError_WrongBin,
  xError_UnknownBin,
  xError_NotBinAddr,
  xError_UnalignedAddr,
  xError_NullSizeAlloc,
  xError_ListCycleError,
  xError_SortedListError,
  xError_KeptAddrListCorrupted,
  xError_FreePattern,
  xError_BackPattern,
  xError_FrontPattern,
  xError_NotString,
  xError_StickyBin,
  xError_MaxError
};

struct xPage_s;
typedef struct xPage_s *xPage;

struct xBin_s {
  xPage currentPage;
  xPage lastPage;
  long sizeInWords; /* size in words */
};

typedef struct xBin_s *xBin;

struct xInfo_s;
typedef struct xInfo_s xInfo_t;
struct xInfo_s {
  long MaxBytesSystem;      /* set in xUpdateInfo(), is more accurate with malloc support   */
  long CurrentBytesSystem;  /* set in xUpdateInfo(), is more accurate with malloc support */
  long MaxBytesSbrk;        /* always up-to-date, not very accurate, needs xInintInfo() */
  long CurrentBytesSbrk;    /* set in xUpdateInfo(), needs xInintInfo() */
  long MaxBytesMmap;        /* set in xUpdateInfo(), not very accurate */
  long CurrentBytesMmap;    /* set in xUpdateInfo(), not very accurate */
  long UsedBytes;           /* set in xUpdateInfo() */
  long AvailBytes;          /* set in xUpdateInfo() */
  long UsedBytesMalloc;     /* set in xUpdateInfo(), needs malloc support */
  long AvailBytesMalloc;    /* set in xUpdateInfo(), needs malloc support */
  long MaxBytesFromMalloc;      /* always kept up-to-date */
  long CurrentBytesFromMalloc;  /* always kept up-to-date */
  long MaxBytesFromValloc;      /* always kept up-to-date */
  long CurrentBytesFromValloc;  /* always kept up-to-date */
  long UsedBytesFromValloc;     /* set in xUpdateInfo()  */
  long AvailBytesFromValloc;    /* set in xUpdateInfo()  */
  long MaxPages;                /* always kept up-to-date */
  long UsedPages;               /* always kept up-to-date */
  long AvailPages;              /* always kept up-to-date */
  long MaxRegionsAlloc;         /* always kept up-to-date */
  long CurrentRegionsAlloc;     /* always kept up-to-date */
};

extern struct xInfo_s x_Info;

struct xOpts_s;
extern struct xOpts_s {
  int MinTrack;
  int MinCheck;
  int MaxTrack;
  int MaxCheck;
  int Keep;
  int HowToReportErrors;
  int MarkAsStatic;
  unsigned int PagesPerRegion;
  void (*OutOfMemoryFunc)();
  void (*MemoryLowFunc)();
  void (*ErrorHook)();
} x_Opts;

typedef struct xOpts_s xOpts_t;

struct xBlock_s;
typedef struct xBlock_s *xBlock;
struct xBlock_s {
  xBlock next;
};

struct xRegion_s;
typedef struct xRegion_s *xRegion;

extern int x_sing_opt_show_mem;

void* xMalloc(size_t size);
void* xmalloc(size_t size);
void xFree(void *ptr);
void xfree(void *ptr);

void xFreeSizeFunc(void *ptr, size_t size);

long xSizeOfAddr(void *ptr);
xRegion xIsBinBlock(unsigned long region);

static inline void* xMalloc0(size_t size) {
  void *ptr = xMalloc(size);
  memset(ptr, 0, size); 
  return ptr; 
}


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

void* xAllocBin(xBin bin);
void xFreeBin(void *ptr, xBin bin);

static inline void* xAlloc0Bin(xBin bin) {
  void *ptr = xAllocBin(bin);
  memset(ptr, 0, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
  return ptr;
}

xBin xGetSpecBin(size_t size);
void xUnGetSpecBin(xBin *bin);

void xInfo();

#define xSizeInWordsOfAddr(P)   (xSizeOfAddr(P)/__XMALLOC_SIZEOF_LONG)
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
#define xIsBinPageAddr(A)                       ((void) 0)
#define xTestBinAddrSize(A, B, C)               ((void) 0)
#else
#define xIsBinPageAddr(A)                       xIsBinBlock((unsigned long)A)
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
