/**
 * @file   t2.c
 * @Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include <xmalloc.h>

#define X_MAX_SMALL_BLOCK 1012

int main()
{
  int i;
  for (i=1;i<X_MAX_SMALL_BLOCK;i++)
  {
    xBin b=xGetSpecBin(i);
    void *p=xMalloc(i);
    if ((i>b->sizeInWords*4)
    || (b->sizeInWords*4!=xSizeOfAddr(p)))
      printf(" %d (%d vs %d)\n",i,b->sizeInWords*4,xSizeOfAddr(p));
    xFree(p);
  }
  return 0;
}
