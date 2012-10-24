/**
 * \file   test-xPrintInfo.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test of info printing in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

#define __XMALLOC_TEST_BLOCKS 20000
char *B[__XMALLOC_TEST_BLOCKS];

int main() {
  
  void *p = xMalloc0(64);
  
  xUpdateInfo();
  __XMALLOC_ASSERT(info.currentBytesFromMalloc/1024 == 2048); 
  __XMALLOC_ASSERT(info.maxBytesFromMalloc/1024 == 2048);
  __XMALLOC_ASSERT(info.currentBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.maxBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.currentRegionsAlloc == 1); 
  __XMALLOC_ASSERT(info.maxRegionsAlloc == 1); 
  __XMALLOC_ASSERT(info.maxPages ==1); 
  __XMALLOC_ASSERT(info.usedPages == 1); 
  __XMALLOC_ASSERT(info.availablePages == 511); 

  int i, j;
  for (i = 0; i < __XMALLOC_TEST_BLOCKS; i++)
    B[i]  = (char *)xMalloc0((i * 4) + 1);

  xUpdateInfo();
  __XMALLOC_ASSERT(info.currentBytesFromMalloc/1024 == 2048); 
  __XMALLOC_ASSERT(info.maxBytesFromMalloc/1024 == 2048);
  __XMALLOC_ASSERT(info.currentBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.maxBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.maxRegionsAlloc == 1); 
  __XMALLOC_ASSERT(info.maxPages == 53); 
  __XMALLOC_ASSERT(info.usedPages == 53); 
  __XMALLOC_ASSERT(info.availablePages == 459); 
  
  for (i = __XMALLOC_TEST_BLOCKS - 1; i > -1; i--) {
    xFree(B[i]);
  }
  
  xUpdateInfo();
  __XMALLOC_ASSERT(info.currentBytesFromMalloc/1024 == 0); 
  __XMALLOC_ASSERT(info.maxBytesFromMalloc/1024 == 2048);
  __XMALLOC_ASSERT(info.currentBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.maxBytesSystem/1024 == 0); 
  __XMALLOC_ASSERT(info.maxRegionsAlloc == 1); 
  __XMALLOC_ASSERT(info.maxPages == 53); 
  __XMALLOC_ASSERT(info.usedPages == 53); 
  __XMALLOC_ASSERT(info.availablePages == 459); 

  return 0;
}
