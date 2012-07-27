/* Copyright 2012 Christian Eder
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <xmalloc.h>

#if __XMALLOC_SIZEOF_LONG == 8 /* 64bit */
#define __XMALLOC_PAGES_PER_REGION 4068
#define __XMALLOC_MAX_SMALL_BLOCK  1008    
  #else /* 32bit */
#define __XMALLOC_PAGES_PER_REGION 4080
#define __XMALLOC_MAX_SMALL_BLOCK  1016    
  
#endif
xRegion baseRegion  = NULL;

/* zero page for initializing static bins */
struct xPageStruct xZeroPage[] = {{0, NULL, NULL, NULL, NULL}};

#if __XMALLOC_SIZEOF_LONG == 8
struct xBinStruct xStaticBin[] = {
{xZeroPage, NULL, NULL, 1}, /*0 */
{xZeroPage, NULL, NULL, 2}, /*1 */
{xZeroPage, NULL, NULL, 3}, /*2 */
{xZeroPage, NULL, NULL, 4}, /*3 */
{xZeroPage, NULL, NULL, 5}, /*4 */
{xZeroPage, NULL, NULL, 6}, /*5 */
{xZeroPage, NULL, NULL, 7}, /*6 */
{xZeroPage, NULL, NULL, 8}, /*7 */
{xZeroPage, NULL, NULL, 9}, /*8 */
{xZeroPage, NULL, NULL, 10}, /*9 */
{xZeroPage, NULL, NULL, 12}, /*10*/
{xZeroPage, NULL, NULL, 14}, /*11*/
{xZeroPage, NULL, NULL, 16}, /*12*/
{xZeroPage, NULL, NULL, 18}, /*13*/
{xZeroPage, NULL, NULL, 20}, /*14*/
{xZeroPage, NULL, NULL, 24}, /*15*/
{xZeroPage, NULL, NULL, 28}, /*16*/
{xZeroPage, NULL, NULL, 38}, /*17*/
{xZeroPage, NULL, NULL, 50}, /*18*/
{xZeroPage, NULL, NULL, 63}, /*19*/
{xZeroPage, NULL, NULL, 84}, /*20*/
{xZeroPage, NULL, NULL, 101}, /*21*/
{xZeroPage, NULL, NULL, 126}  /*22*/
};

xBin xSize2Bin[/*126*/] = {
&xStaticBin[0], /* 8 */
&xStaticBin[1], /* 16 */
&xStaticBin[2], /* 24 */
&xStaticBin[3], /* 32 */
&xStaticBin[4], /* 40 */
&xStaticBin[5], /* 48 */
&xStaticBin[6], /* 56 */
&xStaticBin[7], /* 64 */
&xStaticBin[8], /* 72 */
&xStaticBin[9], /* 80 */
&xStaticBin[10], /* 88 */
&xStaticBin[10], /* 96 */
&xStaticBin[11], /* 104 */
&xStaticBin[11], /* 112 */
&xStaticBin[12], /* 120 */
&xStaticBin[12], /* 128 */
&xStaticBin[13], /* 136 */
&xStaticBin[13], /* 144 */
&xStaticBin[14], /* 152 */
&xStaticBin[14], /* 160 */
&xStaticBin[15], /* 168 */
&xStaticBin[15], /* 176 */
&xStaticBin[15], /* 184 */
&xStaticBin[15], /* 192 */
&xStaticBin[16], /* 200 */
&xStaticBin[16], /* 208 */
&xStaticBin[16], /* 216 */
&xStaticBin[16], /* 224 */
&xStaticBin[17], /* 232 */
&xStaticBin[17], /* 240 */
&xStaticBin[17], /* 248 */
&xStaticBin[17], /* 256 */
&xStaticBin[17], /* 264 */
&xStaticBin[17], /* 272 */
&xStaticBin[17], /* 280 */
&xStaticBin[17], /* 288 */
&xStaticBin[17], /* 296 */
&xStaticBin[17], /* 304 */
&xStaticBin[18], /* 312 */
&xStaticBin[18], /* 320 */
&xStaticBin[18], /* 328 */
&xStaticBin[18], /* 336 */
&xStaticBin[18], /* 344 */
&xStaticBin[18], /* 352 */
&xStaticBin[18], /* 360 */
&xStaticBin[18], /* 368 */
&xStaticBin[18], /* 376 */
&xStaticBin[18], /* 384 */
&xStaticBin[18], /* 392 */
&xStaticBin[18], /* 400 */
&xStaticBin[19], /* 408 */
&xStaticBin[19], /* 416 */
&xStaticBin[19], /* 424 */
&xStaticBin[19], /* 432 */
&xStaticBin[19], /* 440 */
&xStaticBin[19], /* 448 */
&xStaticBin[19], /* 456 */
&xStaticBin[19], /* 464 */
&xStaticBin[19], /* 472 */
&xStaticBin[19], /* 480 */
&xStaticBin[19], /* 488 */
&xStaticBin[19], /* 496 */
&xStaticBin[19], /* 504 */
&xStaticBin[20], /* 512 */
&xStaticBin[20], /* 520 */
&xStaticBin[20], /* 528 */
&xStaticBin[20], /* 536 */
&xStaticBin[20], /* 544 */
&xStaticBin[20], /* 552 */
&xStaticBin[20], /* 560 */
&xStaticBin[20], /* 568 */
&xStaticBin[20], /* 576 */
&xStaticBin[20], /* 584 */
&xStaticBin[20], /* 592 */
&xStaticBin[20], /* 600 */
&xStaticBin[20], /* 608 */
&xStaticBin[20], /* 616 */
&xStaticBin[20], /* 624 */
&xStaticBin[20], /* 632 */
&xStaticBin[20], /* 640 */
&xStaticBin[20], /* 648 */
&xStaticBin[20], /* 656 */
&xStaticBin[20], /* 664 */
&xStaticBin[20], /* 672 */
&xStaticBin[21], /* 680 */
&xStaticBin[21], /* 688 */
&xStaticBin[21], /* 696 */
&xStaticBin[21], /* 704 */
&xStaticBin[21], /* 712 */
&xStaticBin[21], /* 720 */
&xStaticBin[21], /* 728 */
&xStaticBin[21], /* 736 */
&xStaticBin[21], /* 744 */
&xStaticBin[21], /* 752 */
&xStaticBin[21], /* 760 */
&xStaticBin[21], /* 768 */
&xStaticBin[21], /* 776 */
&xStaticBin[21], /* 784 */
&xStaticBin[21], /* 792 */
&xStaticBin[21], /* 800 */
&xStaticBin[21], /* 808 */
&xStaticBin[22], /* 816 */
&xStaticBin[22], /* 824 */
&xStaticBin[22], /* 832 */
&xStaticBin[22], /* 840 */
&xStaticBin[22], /* 848 */
&xStaticBin[22], /* 856 */
&xStaticBin[22], /* 864 */
&xStaticBin[22], /* 872 */
&xStaticBin[22], /* 880 */
&xStaticBin[22], /* 888 */
&xStaticBin[22], /* 896 */
&xStaticBin[22], /* 904 */
&xStaticBin[22], /* 912 */
&xStaticBin[22], /* 920 */
&xStaticBin[22], /* 928 */
&xStaticBin[22], /* 936 */
&xStaticBin[22], /* 944 */
&xStaticBin[22], /* 952 */
&xStaticBin[22], /* 960 */
&xStaticBin[22], /* 968 */
&xStaticBin[22], /* 976 */
&xStaticBin[22], /* 984 */
&xStaticBin[22], /* 992 */
&xStaticBin[22], /* 1000 */
&xStaticBin[22] /* 1008 */};
#else
struct xBinStruct xStaticBin[/*24*/] = {
{xZeroPage, NULL, NULL, 2}, /* 0 */
{xZeroPage, NULL, NULL, 3}, /* 1 */
{xZeroPage, NULL, NULL, 4}, /* 2 */
{xZeroPage, NULL, NULL, 5}, /* 3 */
{xZeroPage, NULL, NULL, 6}, /* 4 */
{xZeroPage, NULL, NULL, 7}, /* 5 */
{xZeroPage, NULL, NULL, 8}, /* 6 */
{xZeroPage, NULL, NULL, 10}, /* 7 */
{xZeroPage, NULL, NULL, 12}, /* 8 */
{xZeroPage, NULL, NULL, 14}, /* 9 */
{xZeroPage, NULL, NULL, 16}, /* 10 */
{xZeroPage, NULL, NULL, 20}, /* 11 */
{xZeroPage, NULL, NULL, 24}, /* 12 */
{xZeroPage, NULL, NULL, 28}, /* 13 */
{xZeroPage, NULL, NULL, 32}, /* 14 */
{xZeroPage, NULL, NULL, 40}, /* 15 */
{xZeroPage, NULL, NULL, 48}, /* 16 */
{xZeroPage, NULL, NULL, 56}, /* 17 */
{xZeroPage, NULL, NULL, 78}, /* 18 */
{xZeroPage, NULL, NULL, 101}, /* 19 */
{xZeroPage, NULL, NULL, 127}, /* 20 */
{xZeroPage, NULL, NULL, 169}, /* 21 */
{xZeroPage, NULL, NULL, 203}, /* 22 */
{xZeroPage, NULL, NULL, 254} /* 23 */
};

xBin xSize2Bin[/*254*/] = {
&xStaticBin[0], /* 4 */
&xStaticBin[0], /* 8 */
&xStaticBin[1], /* 12 */
&xStaticBin[2], /* 16 */
&xStaticBin[3], /* 20 */
&xStaticBin[4], /* 24 */
&xStaticBin[5], /* 28 */
&xStaticBin[6], /* 32 */
&xStaticBin[7], /* 36 */
&xStaticBin[7], /* 40 */
&xStaticBin[8], /* 44 */
&xStaticBin[8], /* 48 */
&xStaticBin[9], /* 52 */
&xStaticBin[9], /* 56 */
&xStaticBin[10], /* 60 */
&xStaticBin[10], /* 64 */
&xStaticBin[11], /* 68 */
&xStaticBin[11], /* 72 */
&xStaticBin[11], /* 76 */
&xStaticBin[11], /* 80 */
&xStaticBin[12], /* 84 */
&xStaticBin[12], /* 88 */
&xStaticBin[12], /* 92 */
&xStaticBin[12], /* 96 */
&xStaticBin[13], /* 100 */
&xStaticBin[13], /* 104 */
&xStaticBin[13], /* 108 */
&xStaticBin[13], /* 112 */
&xStaticBin[14], /* 116 */
&xStaticBin[14], /* 120 */
&xStaticBin[14], /* 124 */
&xStaticBin[14], /* 128 */
&xStaticBin[15], /* 132 */
&xStaticBin[15], /* 136 */
&xStaticBin[15], /* 140 */
&xStaticBin[15], /* 144 */
&xStaticBin[15], /* 148 */
&xStaticBin[15], /* 152 */
&xStaticBin[15], /* 156 */
&xStaticBin[15], /* 160 */
&xStaticBin[16], /* 164 */
&xStaticBin[16], /* 168 */
&xStaticBin[16], /* 172 */
&xStaticBin[16], /* 176 */
&xStaticBin[16], /* 180 */
&xStaticBin[16], /* 184 */
&xStaticBin[16], /* 188 */
&xStaticBin[16], /* 192 */
&xStaticBin[17], /* 196 */
&xStaticBin[17], /* 200 */
&xStaticBin[17], /* 204 */
&xStaticBin[17], /* 208 */
&xStaticBin[17], /* 212 */
&xStaticBin[17], /* 216 */
&xStaticBin[17], /* 220 */
&xStaticBin[17], /* 224 */
&xStaticBin[18], /* 228 */
&xStaticBin[18], /* 232 */
&xStaticBin[18], /* 236 */
&xStaticBin[18], /* 240 */
&xStaticBin[18], /* 244 */
&xStaticBin[18], /* 248 */
&xStaticBin[18], /* 252 */
&xStaticBin[18], /* 256 */
&xStaticBin[18], /* 260 */
&xStaticBin[18], /* 264 */
&xStaticBin[18], /* 268 */
&xStaticBin[18], /* 272 */
&xStaticBin[18], /* 276 */
&xStaticBin[18], /* 280 */
&xStaticBin[18], /* 284 */
&xStaticBin[18], /* 288 */
&xStaticBin[18], /* 292 */
&xStaticBin[18], /* 296 */
&xStaticBin[18], /* 300 */
&xStaticBin[18], /* 304 */
&xStaticBin[18], /* 308 */
&xStaticBin[18], /* 312 */
&xStaticBin[19], /* 316 */
&xStaticBin[19], /* 320 */
&xStaticBin[19], /* 324 */
&xStaticBin[19], /* 328 */
&xStaticBin[19], /* 332 */
&xStaticBin[19], /* 336 */
&xStaticBin[19], /* 340 */
&xStaticBin[19], /* 344 */
&xStaticBin[19], /* 348 */
&xStaticBin[19], /* 352 */
&xStaticBin[19], /* 356 */
&xStaticBin[19], /* 360 */
&xStaticBin[19], /* 364 */
&xStaticBin[19], /* 368 */
&xStaticBin[19], /* 372 */
&xStaticBin[19], /* 376 */
&xStaticBin[19], /* 380 */
&xStaticBin[19], /* 384 */
&xStaticBin[19], /* 388 */
&xStaticBin[19], /* 392 */
&xStaticBin[19], /* 396 */
&xStaticBin[19], /* 400 */
&xStaticBin[19], /* 404 */
&xStaticBin[20], /* 408 */
&xStaticBin[20], /* 412 */
&xStaticBin[20], /* 416 */
&xStaticBin[20], /* 420 */
&xStaticBin[20], /* 424 */
&xStaticBin[20], /* 428 */
&xStaticBin[20], /* 432 */
&xStaticBin[20], /* 436 */
&xStaticBin[20], /* 440 */
&xStaticBin[20], /* 444 */
&xStaticBin[20], /* 448 */
&xStaticBin[20], /* 452 */
&xStaticBin[20], /* 456 */
&xStaticBin[20], /* 460 */
&xStaticBin[20], /* 464 */
&xStaticBin[20], /* 468 */
&xStaticBin[20], /* 472 */
&xStaticBin[20], /* 476 */
&xStaticBin[20], /* 480 */
&xStaticBin[20], /* 484 */
&xStaticBin[20], /* 488 */
&xStaticBin[20], /* 492 */
&xStaticBin[20], /* 496 */
&xStaticBin[20], /* 500 */
&xStaticBin[20], /* 504 */
&xStaticBin[20], /* 508 */
&xStaticBin[21], /* 512 */
&xStaticBin[21], /* 516 */
&xStaticBin[21], /* 520 */
&xStaticBin[21], /* 524 */
&xStaticBin[21], /* 528 */
&xStaticBin[21], /* 532 */
&xStaticBin[21], /* 536 */
&xStaticBin[21], /* 540 */
&xStaticBin[21], /* 544 */
&xStaticBin[21], /* 548 */
&xStaticBin[21], /* 552 */
&xStaticBin[21], /* 556 */
&xStaticBin[21], /* 560 */
&xStaticBin[21], /* 564 */
&xStaticBin[21], /* 568 */
&xStaticBin[21], /* 572 */
&xStaticBin[21], /* 576 */
&xStaticBin[21], /* 580 */
&xStaticBin[21], /* 584 */
&xStaticBin[21], /* 588 */
&xStaticBin[21], /* 592 */
&xStaticBin[21], /* 596 */
&xStaticBin[21], /* 600 */
&xStaticBin[21], /* 604 */
&xStaticBin[21], /* 608 */
&xStaticBin[21], /* 612 */
&xStaticBin[21], /* 616 */
&xStaticBin[21], /* 620 */
&xStaticBin[21], /* 624 */
&xStaticBin[21], /* 628 */
&xStaticBin[21], /* 632 */
&xStaticBin[21], /* 636 */
&xStaticBin[21], /* 640 */
&xStaticBin[21], /* 644 */
&xStaticBin[21], /* 648 */
&xStaticBin[21], /* 652 */
&xStaticBin[21], /* 656 */
&xStaticBin[21], /* 660 */
&xStaticBin[21], /* 664 */
&xStaticBin[21], /* 668 */
&xStaticBin[21], /* 672 */
&xStaticBin[21], /* 676 */
&xStaticBin[22], /* 680 */
&xStaticBin[22], /* 684 */
&xStaticBin[22], /* 688 */
&xStaticBin[22], /* 692 */
&xStaticBin[22], /* 696 */
&xStaticBin[22], /* 700 */
&xStaticBin[22], /* 704 */
&xStaticBin[22], /* 708 */
&xStaticBin[22], /* 712 */
&xStaticBin[22], /* 716 */
&xStaticBin[22], /* 720 */
&xStaticBin[22], /* 724 */
&xStaticBin[22], /* 728 */
&xStaticBin[22], /* 732 */
&xStaticBin[22], /* 736 */
&xStaticBin[22], /* 740 */
&xStaticBin[22], /* 744 */
&xStaticBin[22], /* 748 */
&xStaticBin[22], /* 752 */
&xStaticBin[22], /* 756 */
&xStaticBin[22], /* 760 */
&xStaticBin[22], /* 764 */
&xStaticBin[22], /* 768 */
&xStaticBin[22], /* 772 */
&xStaticBin[22], /* 776 */
&xStaticBin[22], /* 780 */
&xStaticBin[22], /* 784 */
&xStaticBin[22], /* 788 */
&xStaticBin[22], /* 792 */
&xStaticBin[22], /* 796 */
&xStaticBin[22], /* 800 */
&xStaticBin[22], /* 804 */
&xStaticBin[22], /* 808 */
&xStaticBin[22], /* 812 */
&xStaticBin[23], /* 816 */
&xStaticBin[23], /* 820 */
&xStaticBin[23], /* 824 */
&xStaticBin[23], /* 828 */
&xStaticBin[23], /* 832 */
&xStaticBin[23], /* 836 */
&xStaticBin[23], /* 840 */
&xStaticBin[23], /* 844 */
&xStaticBin[23], /* 848 */
&xStaticBin[23], /* 852 */
&xStaticBin[23], /* 856 */
&xStaticBin[23], /* 860 */
&xStaticBin[23], /* 864 */
&xStaticBin[23], /* 868 */
&xStaticBin[23], /* 872 */
&xStaticBin[23], /* 876 */
&xStaticBin[23], /* 880 */
&xStaticBin[23], /* 884 */
&xStaticBin[23], /* 888 */
&xStaticBin[23], /* 892 */
&xStaticBin[23], /* 896 */
&xStaticBin[23], /* 900 */
&xStaticBin[23], /* 904 */
&xStaticBin[23], /* 908 */
&xStaticBin[23], /* 912 */
&xStaticBin[23], /* 916 */
&xStaticBin[23], /* 920 */
&xStaticBin[23], /* 924 */
&xStaticBin[23], /* 928 */
&xStaticBin[23], /* 932 */
&xStaticBin[23], /* 936 */
&xStaticBin[23], /* 940 */
&xStaticBin[23], /* 944 */
&xStaticBin[23], /* 948 */
&xStaticBin[23], /* 952 */
&xStaticBin[23], /* 956 */
&xStaticBin[23], /* 960 */
&xStaticBin[23], /* 964 */
&xStaticBin[23], /* 968 */
&xStaticBin[23], /* 972 */
&xStaticBin[23], /* 976 */
&xStaticBin[23], /* 980 */
&xStaticBin[23], /* 984 */
&xStaticBin[23], /* 988 */
&xStaticBin[23], /* 992 */
&xStaticBin[23], /* 996 */
&xStaticBin[23], /* 1000 */
&xStaticBin[23], /* 1004 */
&xStaticBin[23], /* 1008 */
&xStaticBin[23], /* 1012 */
&xStaticBin[23] /* 1016 */};
#endif

xPage xGetPageFromBlock(void* ptr) {
  unsigned long page  =   (unsigned long) ptr;
  page                &=  ~4095;
  return (xPage)page;
}

long xSizeOfAddr(void* ptr) {
  xRegion reg = xIsBinBlock((unsigned long)ptr);
  if (reg != NULL)  {
    xPage page =  xGetPageFromBlock(ptr);
    return page->bin->sizeInWords * __XMALLOC_SIZEOF_LONG;
  } else {
    long* newPtr  = (long*) ptr; 
    newPtr--; 
    return *newPtr;
  }
}

void xMakePage(void* ptr, size_t size) {
  xPage page      = (xPage)ptr;
  xBlock pageData = (xBlock)&(page->data);
  /*unsigned long header=(unsigned long)t-(unsigned long)p;*/
  #if 1
  memset((void*)page, 0, 4096);
  #else
  page->free=0;
  page->numberUsedBlocks=0;
  #endif
  while (((unsigned long)pageData) + size <= (((unsigned long)page) + 4096)) {
    pageData->next  = page->free;
    page->free      = pageData;
    pageData        = (xBlock)(((unsigned long)pageData)+size);
  }
  if (page->free == NULL)
    printf("xMakePage(%ld)\n", (long)size);
}

xRegion xAllocRegion() {
  xRegion reg  = (xRegion)malloc(sizeof(*reg));
  void *ptr;
  memset(reg, 0, sizeof(*reg));
  posix_memalign(&ptr, 4096, 4096 * __XMALLOC_PAGES_PER_REGION);
  reg->start            = (unsigned long)ptr;
  reg->end              = reg->start + 4096 * __XMALLOC_PAGES_PER_REGION;
  reg->numberUsedBlocks = __XMALLOC_PAGES_PER_REGION;
  reg->next             = baseRegion;
  baseRegion            = reg;
  return reg;
}

void* xGetNewPage() {
  xRegion reg = baseRegion;
  int i;
  while (1) {
    if (reg == NULL)
      reg = xAllocRegion();
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

xBin xGetBin(size_t size) {
  if (size <= __XMALLOC_MAX_SMALL_BLOCK)
    return x_Size2Bin[(size - 1) / (__XMALLOC_SIZEOF_LONG)];
  return NULL;
}

xPage xPageForMalloc  = (xPage)1;

xBin xGetSpecBin(size_t size) {
  xBin bin  = xGetBin(size);
  if (bin == NULL) {
    bin = (xBin)malloc(sizeof(*bin));
    memset(bin, 0, sizeof(*bin));
    bin->sizeInWords  = (size + __XMALLOC_SIZEOF_LONG - 1) / __XMALLOC_SIZEOF_LONG;
    bin->currentPage  = xPageForMalloc;
  }
  return bin;
}

void xUnGetSpecBin(xBin* bin) {
  if (*bin  ==  NULL) {
    printf("xUnGetSpecBin(NULL\n");
  } else {
    if ((*bin)->currentPage == xPageForMalloc) {
      /* TODO */
      free(*bin);
    }
  }
  *bin  = NULL;
}


xPage xGetPageFromBin(xBin bin) {
  if (bin->currentPage != NULL) {
    if (bin->currentPage->free != NULL)
      return bin->currentPage;
    else {
      xPage page  = bin->lastPage;
      while ((page != NULL) && (page->free == NULL)) 
        page  = page->prev;
      if ((page != NULL) && (page->free != NULL)) { 
        bin->currentPage  = page; 
        return page; 
      }
    }
  }
  /* now b->current==NULL or all pages are full */
  //extern void *xGetNewPage();
  xPage page  = (xPage)xGetNewPage();
  xMakePage(page, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
  page->prev  = bin->lastPage;
  page->next  = NULL;
  if (bin->lastPage !=  NULL) 
    bin->lastPage->next = page;
  bin->lastPage         = page;
  bin->currentPage      = page;
  page->bin             = bin;
  return page;
  //return b->currentPage;
}

xPage xGetPageFromSize(size_t size) {
  xBin bin  = xGetBin(size);
  return xGetPageFromBin(bin);
}

void* xAllocFromPage(xPage page) {
  xBlock ptr  = page->free;
  page->free  = ptr->next;
  page->numberUsedBlocks++;
  memset(ptr, 0, page->bin->sizeInWords * __XMALLOC_SIZEOF_LONG); /*debug!*/
  return (void *)ptr;
}

void* xMalloc(size_t size) {
  /*assume (s>0);*/
  if (size <= __XMALLOC_MAX_SMALL_BLOCK) {
    xPage page  = xGetPageFromSize(size);
    return xAllocFromPage(page);
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

void xFreeToPage(xPage page, void *ptr) {
  xBlock xBlockPtr  = (xBlock)ptr;
  xBlockPtr->next   = page->free;
  page->free        = xBlockPtr;
  page->numberUsedBlocks--;
}

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

void* xAllocBin(xBin bin) {
  xPage page  = bin->currentPage;
  if (page == xPageForMalloc) 
    return xMalloc(bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
  page  = xGetPageFromBin(bin);
  return xAllocFromPage(page);
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
    *((void**) (ptr)) = page->free;
    page->free        = ptr;
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

void xFreeBin(void *ptr, xBin bin) {
  if (bin->currentPage == xPageForMalloc) { 
    xFree(ptr);
    return;
  }
  xPage page  = xGetPageFromBlock(ptr);
  if (page->numberUsedBlocks > 1) {
    *((void**) (ptr)) = page->free;
    page->free        = ptr;
    page->numberUsedBlocks--;
  } else {
    xRegion reg = xIsBinBlock((unsigned long)ptr);
    /*xBin bin=page->bin;*/
    if (page->next != NULL) 
      page->next->prev  = page->prev; 
    if (page->prev != NULL) 
      page->prev->next  = page->next; 
    if (bin->lastPage == page) 
      bin->lastPage = page->prev;
    if (bin->currentPage == page) 
      bin->currentPage  = page->prev;
    reg->numberUsedBlocks++;
    reg->bits[(((unsigned long)ptr) - reg->start) / 4096] = '\0';
  }
}

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
