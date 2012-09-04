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
    printf(" - - - start allocation - - - \n");
    void *p=xMalloc(i);
    printf(" - - - end allocation: %p- - - \n",p);
    if ((i>b->sizeInWords*4)
    || (b->sizeInWords*4 != (long) xSizeOfAddr(p)))
      printf(" %d (%d vs %d)\n",i,((int) b->sizeInWords)*4,(int) xSizeOfAddr(p));
    printf("%p in %p ? nrBL %ld\n",p,xGetPageOfAddr(p),((xPage)xGetPageOfAddr(p))->numberUsedBlocks);
    printf(" - - - start freeing - - - \n");
    xFree(p);
    printf(" - - - end freeing - - - \n");
  }
  return 0;
}
