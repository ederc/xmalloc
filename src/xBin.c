/**
 * @file   xBin.c 
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline bin handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <xBin.h>

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

void xInsertPageToBin(xBin bin, xPage page) {
  if(bin->currentPage == xZeroPage) {
    page->prev        = NULL;
    page->next        = NULL;
    bin->currentPage  = page;
    bin->lastPage     = page;
  } else {
    if(bin->currentPage == bin->lastPage) {
      bin->lastPage = page;
    } else {
      bin->currentPage->next->prev  = page;
    }
    page->next              = bin->currentPage->next;
    bin->currentPage->next  = page;
    page->prev              = bin->currentPage;
  }
}

xPage xAllocNewPageForBin(xBin bin) {
  xPage newPage;
  void *tmp;
  int i = 1;

  // block size < page size
  if(bin->numberBlocks > 0)
    newPage = xAllocPageForBin(); // TOODOO
  // block size > page size
  else
    newPage = xAllocPagesForBin(); // TOODOO

  newPage->numberUsedBlocks = -1;
  newPage->current  = (void*) (((char*) newPage) + 
                        __XMALLOC_SIZEOF_PAGE_HEADER);
  tmp               = newPage->current;
  while(i < bin->numberBlocks) {
    tmp = __XMALLOC_NEXT(tmp)  = ((void**) tmp) + bin->sizeInWords;
    i++;
  }
  __XMALLOC_NEXT(tmp) = NULL;
  return newPage;
}

void xFreeBin(void *ptr, xBin bin) {
  if (bin->currentPage == xPageForMalloc) { 
    xFree(ptr);
    return;
  }
  xPage page  = xGetPageFromBlock(ptr);
  if (page->numberUsedBlocks > 1) {
    __XMALLOC_NEXT(ptr) = page->free;
    page->free          = ptr;
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
