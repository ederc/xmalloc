/**
 * @file   xmalloc.c
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for xmalloc.
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

    assert(sizeInWords >= size);
    assert(numberBlocks * sizeInWords <= __XMALLOC_SIZEOF_PAGE);

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
      assert(NULL != specBin->bin &&
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
    return specBin->bin;
  } else {
    return newSpecBin;
  }
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
void xFreeSizeFunc(void *ptr, size_t size) { 
  xFree(ptr); 
}

/*
void xInfo() {
  int i       = 0;
  int kb      = 0;
  int kb2     = 0;
  xRegion reg = xBaseRegion;
  while (reg != NULL) {
    int j;
    printf("region %d (%lx - %lx), free pages %d\n", i, reg->start, reg->end, reg->numberUsedBlocks);
    kb2 +=  (__XMALLOC_PAGES_PER_REGION - reg->numberUsedBlocks) * 4;
    i++;
    reg =   reg->next;
    kb  +=  (4 * __XMALLOC_PAGES_PER_REGION) + 4;
  }
  printf("allocated kB: %d, used kb: %d\n", kb, kb2);
  for (i = 0; i < 23; i++) {
    xPage page  = x_StaticBin[i].currentPage;
    kb          = 0;
    while (page != NULL) { 
      kb++; 
      page  = page->prev; 
    }
    page  = x_StaticBin[i].currentPage;
    kb2   = (page != NULL) - 1;
    while (page!=NULL) { 
      kb2++; 
      page=page->next; 
    }
    printf("bin %d, sizeInWords=%ld, curr=%lx, pages: %d + %d\n", 
            i, x_StaticBin[i].sizeInWords, 
            (unsigned long)x_StaticBin[i].currentPage, kb, kb2);
  }
}
*/
