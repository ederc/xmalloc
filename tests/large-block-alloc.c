/**
 * \file   t1.c
 * \Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main()
{
  int i = __XMALLOC_MAX_SMALL_BLOCK_SIZE;
  for (i; i < (10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE); i=i+5)
  {
    xBin bin  = xGetSpecBin(i);
    __XMALLOC_ASSERT(NULL != bin);
    void *p=xMalloc(i);
    if ((i > (bin->sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG))
    || ((bin->sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG) != (long) xSizeOfAddr(p)))
      printf(" %d (%d vs %d)\n",i,((long) bin->sizeInWords) >> __XMALLOC_LOG_SIZEOF_LONG,(int) xSizeOfAddr(p));
      printf(" %d",bin->sizeInWords);
    xFree(p);
  }
  return 0;
}
