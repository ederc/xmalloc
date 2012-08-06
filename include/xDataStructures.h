/**
 * @file   xDataStructures.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Basic data structures needed for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_DATA_STRUCTURES_H
#define X_DATA_STRUCTURES_H

#include <stdlib.h>
#include <string.h>

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

typedef enum{false = 0, true  = 1} bool;

struct xPageStruct;
typedef struct xPageStruct*   xPage;

struct xBinStruct;
typedef struct xBinStruct*    xBin;

struct xRegionStruct;
typedef struct xRegionStruct* xRegion;

struct xInfoStruct;
typedef struct xInfoStruct*   xInfo;

struct xBlockStruct;
typedef struct xBlockStruct*  xBlock;


/**
 * \struct xPageStruct
 * \brief Structure of the internal xmalloc page including a header for better
 * handling in the allocator.
 */
struct xPageStruct {
   long     numberUsedBlocks; /**< number of used blocks in ths page */
   void*    bin;              /**< pointer to free list this page is in */  
   xPage    prev;             /**< previous page in the free list */
   xPage    next;             /**< next page in the free list */
   xRegion  region;           /**< region this page comes from */
};

/**
 * \struct xBinStruct
 * \brief Structure of the free list holding pages divided into the same number
 * of blocks, i.e. for the same size class
 */
struct xBinStruct {
  xPage   currentPage;  /**< Current page in the free list of this size class */
  xPage   lastPage;     /**< Last page of the free list of this size class */
  xBin    next;         /**< Next page in the free list of this size class */
  size_t  sizeInWords;  /**< Size class in word size */
  long    numberBlocks; /**< Maximum number of blocks per page w.r.t. the size 
                             class: If > 0 => #blocks per page
                                    If < 0 => #pages per block */
};

/**
 * \struct xRegionStruct
 * \brief Structure of the regions new free pages are allocated in the first
 * place. They present a block in memory representing an array of pages.
 */
struct xRegionStruct {
  void* current;        /**< current entry in the free list of pages */
  xRegion prev;         /**< previous region */
  xRegion next;         /**< next region */
  char* initAddr;       /**< pointer portion of initial chunk which is still 
                             free */
  char* addr;           /**< address returned by alloc when allocating the 
                             region */
  int numberInitPages;  /**< number of free pages still available in the
                             initial chunk */
  int numberUsedPages;  /**< number of used pages in this region */
  int totalNumberPages; /**< total number of pages allocated in this region */
};


struct xInfoStruct {
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

extern struct xInfoStruct x_Info;

struct xOptsStruct;
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

typedef struct xOptsStruct xOpts_t;

struct xBlockStruct {
  xBlock next;
};
extern int x_sing_opt_show_mem;

#endif
