/**
 * @file   t1.c
 * @Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Test file for xmalloc.
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
    xBin b=xGetSpecBin(i);
    void *p=xMalloc(i);
    if ((i>b->sizeInWords*4)
    || (b->sizeInWords*4 != (long) xSizeOfAddr(p)))
      printf(" %d (%d vs %d)\n",i,((int) b->sizeInWords)*4,(int) xSizeOfAddr(p));
    xFree(p);
  }
  return 0;
}
