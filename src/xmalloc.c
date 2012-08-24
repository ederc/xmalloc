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

xPage xGetPageFromBlock(void* ptr) {
  unsigned long page  =   (unsigned long) ptr;
  page                &=  ~4095;
  return (xPage)page;
}

/*
void* xGetNewPage() {
  xRegion reg = baseRegion;
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

void* xMalloc(const size_t size) {
  void *addr;
  if (size <= __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    xBin bin  = xSmallSize2Bin(size); 
    xAllocFromBin(addr, bin);
    return addr;
  } else {
     long *ptr  = (long*) malloc(size + __XMALLOC_SIZEOF_LONG);
     *ptr       = size;
     ptr++;
     return ptr;
  }
}

void* xmalloc(size_t size) {
  if (size > 0)
    return xMalloc(size);
  else
    return NULL;
}

/*
xRegion xIsSmallBlock(void *ptr) {
  xRegion reg           = baseRegion;
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
  xRegion reg = baseRegion;
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
void xFree(void *ptr) {
  if (ptr == NULL) {
    printf("xFree(NULL)\n");
  } else {
    /*assume (ptr!=NULL);*/
    xRegion reg = xIsBinBlock((unsigned long)ptr);
    if (reg != NULL) {
      xFreeBinRegion(reg, ptr);
    } else {  
      long *longPtr = (long*)ptr; 
      longPtr--; 
      free(longPtr);
    }
  }
}

void xfree(void *ptr) {
  if (ptr != NULL) 
    xFree(ptr);
}

void xFreeSizeFunc(void *ptr, size_t size) { 
  xFree(ptr); 
}

/*
void xInfo() {
  int i       = 0;
  int kb      = 0;
  int kb2     = 0;
  xRegion reg = baseRegion;
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
