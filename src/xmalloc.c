/**
 * \file   xmalloc.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  General source file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "src/xmalloc.h"

extern xBin __XMALLOC_LARGE_BIN;

xPage xGetPageFromBlock(void* ptr) {
  unsigned long page  =   (unsigned long) ptr;
  page                &=  ~4095;
  return (xPage)page;
}

/*
void* xGetNewPage() {
  xRegion reg = xBaseRegion;
  int i;
  while (1) {
    if (reg == NULL)
      reg = xAllocNewRegion(__XMALLOC_MIN_NUMBER_PAGES_PER_REGION);
    if (reg->numberUsedBlocks > 0) {
      for (i = 0; i < __XMALLOC_PAGES_PER_REGION; i++) {
        if (reg->bits[i] == '\0') {
	        reg->numberUsedBlocks--;
          reg->bits[i] = '\1';
          return (void*)(reg->start + i * 4096UL);
        }
      }
    }
    reg = reg->next;
  }
}
*/


/************************************************
 * SPEC-BIN STUFF
 ***********************************************/
xBin xGetSpecBin(size_t size) {
  xBin newSpecBin;
  long numberBlocks;
  long sizeInWords;

  size  = xAlignSize(size);
  if (size > __XMALLOC_SIZEOF_PAGE) {
    // large memory chunks
    // reserve memory for page header
    numberBlocks  = - (long)
      ((size + (__XMALLOC_SIZEOF_SYSTEM_PAGE - __XMALLOC_SIZEOF_PAGE)) +
       __XMALLOC_SIZEOF_SYSTEM_PAGE-1) / __XMALLOC_SIZEOF_SYSTEM_PAGE;

    sizeInWords   = ((-numberBlocks * __XMALLOC_SIZEOF_SYSTEM_PAGE) -
      (__XMALLOC_SIZEOF_SYSTEM_PAGE - __XMALLOC_SIZEOF_PAGE)) /
      __XMALLOC_SIZEOF_LONG;

    newSpecBin    = __XMALLOC_LARGE_BIN;
  } else {
    // small memory chunks
    // reserve memory for page header
    numberBlocks  = __XMALLOC_SIZEOF_PAGE / size;

    sizeInWords   = (__XMALLOC_SIZEOF_PAGE % size) / numberBlocks;
    sizeInWords   = ((size + sizeInWords) &
      ~(__XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE));

    __XMALLOC_ASSERT(sizeInWords >= size);
    __XMALLOC_ASSERT(numberBlocks * sizeInWords <= __XMALLOC_SIZEOF_PAGE);

    sizeInWords = sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG;

    if (size > __XMALLOC_MAX_SMALL_BLOCK_SIZE)
      newSpecBin  = __XMALLOC_LARGE_BIN;
    else
      newSpecBin  = xSmallSize2Bin(size);
  }
  if (__XMALLOC_LARGE_BIN == newSpecBin ||
      numberBlocks > newSpecBin->numberBlocks) {
    xSpecBin specBin  = xFindInSortedList(xBaseSpecBin, numberBlocks);
    // we get a specBin from the list search in above
    if (NULL != specBin) {
      (specBin->ref)++;
      __XMALLOC_ASSERT(NULL != specBin->bin &&
          specBin->bin->numberBlocks  ==  specBin->numberBlocks &&
          specBin->bin->sizeInWords   ==  sizeInWords);
      return specBin->bin;
    }
    // we do not get a specBin from the above list, thus we have to allocate and
    // register it by hand
    specBin               = (xSpecBin) xMalloc(sizeof(xSpecBinType));
    specBin->ref          = 1;
    specBin->next         = NULL;
    specBin->numberBlocks = numberBlocks;
    specBin->bin          = (xBin) xMalloc(sizeof(xBinType));
    specBin->bin->currentPage   = __XMALLOC_ZERO_PAGE;
    specBin->bin->lastPage      = NULL;
    specBin->bin->sizeInWords   = sizeInWords;
    specBin->bin->numberBlocks  = numberBlocks;
    specBin->bin->sticky        = 0;
    xBaseSpecBin  = xInsertIntoSortedList(xBaseSpecBin, specBin, numberBlocks);
    return specBin->bin;
  } else {
    return newSpecBin;
  }
}

void xUnGetSpecBin(xBin *oldBin, int remove) {
  xBin bin  = *oldBin;
  if (!xIsStaticBin(bin)) {
    xSpecBin sBin = xFindInSortedList(xBaseSpecBin, bin->numberBlocks);

    __XMALLOC_ASSERT(NULL != sBin && bin == sBin->bin);

    if (NULL != sBin) {
      sBin->ref--;
      if (0 == sBin->ref || remove) {
        //xFreeKeptAddrFromBin(sBin->bin);
        if (NULL == sBin->bin->lastPage || remove) {
          xBaseSpecBin  = xRemoveFromSortedList(xBaseSpecBin, sBin);
          xFreeSize(sBin->bin, sizeof(xBinType));
          xFreeSize(sBin, sizeof(xSpecBinType));
        }
      }
    }
  }
  *oldBin = NULL;
}

/*
xRegion xIsSmallBlock(void *ptr) {
  xRegion reg           = xBaseRegion;
  unsigned long longPtr = (unsigned long)ptr;
  while (reg != NULL) {
    if ((reg->start > longPtr) || (reg->end <= longPtr)) 
      reg = reg->next;
    else 
      return reg;
  }
  return NULL;
}

xRegion xIsBinBlock(unsigned long unsignedLongPtr) {
  xRegion reg = xBaseRegion;
  while (reg != NULL) {
    unsigned long regStart  = reg->start;
    if ((regStart <= unsignedLongPtr) && (unsignedLongPtr < reg->end)) {
      if (reg->bits[(unsignedLongPtr - regStart) / 4096UL]) 
        return reg;
      else 
        return NULL;
    }
    reg = reg->next;
  }
  return NULL;
}

void xFreeBinRegion(xRegion reg, void *ptr) {
  xPage page  = xGetPageFromBlock(ptr);
  if (page->numberUsedBlocks  > 1) {
    __XMALLOC_NEXT(ptr) = page->free;
    page->free          = ptr;
    page->numberUsedBlocks--;
  } else {
    xBin bin  = page->bin;
    unsigned long unsignedLongPtr = (unsigned long)ptr;
    if (page->next != NULL) 
      page->next->prev  = page->prev; 
    if (page->prev != NULL) 
      page->prev->next  = page->next; 
    if (bin->lastPage == page) 
      bin->lastPage = page->prev;
    if (bin->currentPage == page) 
      bin->currentPage  = page->prev;
    reg->numberUsedBlocks++;
    reg->bits[(unsignedLongPtr - reg->start) / 4096]  = '\0';
  }
}
*/
void* xReallocLarge(void *oldPtr, size_t newSize) {
  newSize       = xAlignSize(newSize);
  char *oldAddr = (char *)oldPtr - __XMALLOC_SIZEOF_STRICT_ALIGNMENT;
  char *newAddr = xReallocSizeFromSystem(oldAddr,
                    *((size_t *) oldAddr) + __XMALLOC_SIZEOF_STRICT_ALIGNMENT,
                    newSize + __XMALLOC_SIZEOF_STRICT_ALIGNMENT);
  
  *((size_t *) newAddr) = newSize;
  return (void *) (newAddr + __XMALLOC_SIZEOF_STRICT_ALIGNMENT);
}

void* xRealloc0Large(void *oldPtr, size_t newSize) {
  size_t oldSize  = xSizeOfLargeAddr(oldPtr);
  char *newPtr    = xReallocLarge(oldPtr, newSize);
  
  newSize = xSizeOfLargeAddr(newPtr);
  // check if we need to initialize stuff to zero
  if (newSize > oldSize)
    memset(newPtr + oldSize, 0, newSize - oldSize);
  
  return (void *) newPtr;
}

void* xDoRealloc(void *oldPtr, size_t oldSize, size_t newSize, int initZero) {
  if(!xIsBinAddr(oldPtr) && newSize > __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    // memory chunk is large, let system malloc handle it
    if (initZero)
      return xRealloc0Large(oldPtr, newSize);
    else
      return xReallocLarge(oldPtr, newSize);
  } else {
    // memory chunk is small enough, xmalloc handles it
    void *newPtr    = xMalloc(newSize);
    size_t minSize  = (oldSize < newSize ? oldSize : newSize);
    //memcpy(newPtr, oldPtr, minSize >> __XMALLOC_LOG_SIZEOF_LONG);
    memcpy(newPtr, oldPtr, minSize);

    // initialize with 0 if initZero is set
    if (initZero) {
      memset((char*) newPtr + minSize, 0, (newSize - oldSize) >>
            __XMALLOC_LOG_SIZEOF_LONG);
    }
    xFreeSize(oldPtr, oldSize);

    return newPtr;
  }
}

void* xReallocSize(void *oldPtr, size_t oldSize, size_t newSize) {
  void *newPtr  = NULL;
  if (__XMALLOC_MAX(newSize, oldSize) <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin oldBin = xGetBinOfAddr(oldPtr);
    xBin newBin = xSmallSize2Bin(newSize);

    if (oldBin != newBin) {
      newPtr  = xAllocFromBin(newBin);
      //memcpy(newPtr, oldPtr, (newBin->sizeInWords > oldWordSize ? oldWordSize :
      //        newBin->sizeInWords));
      memcpy(newPtr, oldPtr, (newSize> oldSize ? oldSize :
              newSize));
      xFreeBinAddr(oldPtr);
    } else {
      newPtr  = oldPtr;
    }
  } else {
    newPtr  = xDoRealloc(oldPtr, oldSize, newSize, 0);
  }
  return newPtr;
}

void* xRealloc0Size(void *oldPtr, size_t oldSize, size_t newSize) {
  void *newPtr  = NULL;
  if (__XMALLOC_MAX(newSize, oldSize) <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin oldBin = xGetBinOfAddr(oldPtr);
    xBin newBin = xSmallSize2Bin(newSize);

    if (oldBin != newBin) {
      size_t oldWordSize  = xIsBinAddr(oldPtr) ? oldBin->sizeInWords :
                            xWordSizeOfAddr(oldPtr);
      newPtr  = xAllocFromBin(newBin);
      //memcpy(newPtr, oldPtr, (newBin->sizeInWords > oldWordSize ? oldWordSize :
      //        newBin->sizeInWords));
      memcpy(newPtr, oldPtr, (newSize> oldSize ? oldSize :
              newSize));
      // initialize to zero if needed
      if (newBin->sizeInWords > oldWordSize)
        memset((void**) newPtr + oldWordSize, 0, newBin->sizeInWords - oldWordSize);
      
      xFreeBinAddr(oldPtr);
    } else {
      newPtr  = oldPtr;
    }
  } else {
    newPtr  = xDoRealloc(oldPtr, oldSize, newSize, 1);
  }
  return newPtr;
}

void xFreeSizeFunc(void *ptr, size_t size) { 
  xFree(ptr); 
}


/************************************************
 * STICKY BUSINESS OF BINS
 ***********************************************/
xBin xGetStickyBinOfBin(xBin bin) {
  xBin newBin = xMalloc(sizeof(xBinType));
  __XMALLOC_ASSERT(!xIsStickyBin(bin));
  newBin->sticky        = __XMALLOC_SIZEOF_VOIDP;
  newBin->numberBlocks  = bin->numberBlocks;
  newBin->sizeInWords   = bin->sizeInWords;
  newBin->next          = xStickyBins;
  xStickyBins           = newBin;
  newBin->lastPage      = NULL;
  newBin->currentPage   = __XMALLOC_ZERO_PAGE;

  return newBin;
}
