/**
 * @file   t2.c
 * @Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include <xmalloc-config.h>
#include "../src/xmalloc.h"

int main()
{
  int i;
  for (i=1;i<__XMALLOC_MAX_SMALL_BLOCK_SIZE;i++)
  {
    xBin b=xGetSpecBin(i);
    void *p=xMalloc(i);
    printf(" %d (%d vs %d)\n",i,b->sizeInWords*4,xSizeOfAddr(p));
    xFree(p);
  }
  return 0;
}
