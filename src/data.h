/**
 * @file   data.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Basic data structures needed for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_DATA_H
#define XMALLOC_DATA_H

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

// for Singular :(
typedef int BOOLEAN;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


//typedef enum{False = 0, True  = 1} boolean;

struct xPageStruct;
typedef struct xPageStruct    xPageType;
typedef xPageType*            xPage;

struct xBinStruct;
typedef struct xBinStruct     xBinType;
typedef xBinType*             xBin;

struct xSpecBinStruct;
typedef struct xSpecBinStruct xSpecBinType;
typedef xSpecBinType*         xSpecBin;

struct xBlockStruct;
typedef struct xBlockStruct   xBlockType;
typedef xBlockType*           xBlock;

struct xRegionStruct;
typedef struct xRegionStruct  xRegionType;
typedef xRegionType*          xRegion;

/**
 * @struct xPageStruct
 *
 * @brief Structure of the internal xmalloc page including a header for better
 * handling in the allocator.
 */
struct xPageStruct {
   long     numberUsedBlocks; /**< number of used blocks in this page */
   void*    current;          /**< pointer to free list this page is in */  
   xPage    prev;             /**< previous page in the free list */
   xPage    next;             /**< next page in the free list */
   void*    bin;              /**< bin of this page */
   xRegion  region;           /**< region this page comes from */
};

/**
 * @struct xBinStruct
 *
 * @brief Structure of the free list holding pages divided into the same number
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
  unsigned long sticky; /**< sticky tag of bin */
};

/**
 * @struct xSpecBinStruct
 *
 * @brief Bin structure eSPECially for monomials.
 */
struct xSpecBinStruct {
  xSpecBin  next;           /**< pointer to next bin */
  xBin      bin;            /**< pointer to bin itself */
  long      numberBlocks;   /**< Maximum number of blocks per page w.r.t.
                              the size class: If > 0 => #blocks per page
                                              If < 0 => #pages per block */
  long      ref;            /** reference counter */
};

/**
 * @struct xRegionStruct
 *
 * @brief Structure of the regions new free pages are allocated in the first
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


/**
 * @struct xInfoStruct
 *
 * @brief Structure storing all information about ongoing allocation resp.
 * freeing processes in xmalloc.
 */
struct xInfoStruct {
  long maxBytesSystem;          /**< maximal number of bytes allocated by the system allocator */
  long currentBytesSystem;      /**< current number of bytes allocated by the system allocator */
  long maxBytesSbrk;            /**< maximal number of bytes allocated via sbrk() */
  long currentBytesSbrk;        /**< current number of bytes allocated via sbrk()*/
  long maxBytesMmap;            /**< maximal number of bytes allocated via mmap() */
  long currentBytesMmap;        /**< current number of bytes allocated via mmap() */
  long usedBytes;               /**< number of bytes used by the application */
  long availableBytes;          /**< number of bytes available for the application */
  long usedBytesMalloc;         /**< number of bytes used by malloc */
  long availableBytesMalloc;    /**< number of bytes available for malloc */
  long maxBytesFromMalloc;      /**< maximal number of bytes from malloc */
  long currentBytesFromMalloc;  /**< current number of bytes from malloc */
  long maxBytesFromValloc;      /**< maximal number of bytes from valloc */
  long currentBytesFromValloc;  /**< current number of bytes from valloc */
  long usedBytesFromValloc;     /**< number of used bytes from valloc */
  long availableBytesFromValloc;/**< number of available bytes from valloc */
  long maxPages;                /**< maximal number of pages */
  long usedPages;               /**< number of used pages */
  long availablePages;          /**< number of available pages */
  long maxRegionsAlloc;         /**< maximal number of regions allocated */
  long currentRegionsAlloc;     /**< current number of regions allocated */
};

typedef struct xInfoStruct xInfo;

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

#ifdef __cplusplus
}
#endif

#endif
