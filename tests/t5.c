/**
 * \file   t5.c
 * \Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include <xmalloc-config.h>
#include "../src/xmalloc.h"

int main()
{
  {
    xBin b=&x_StaticBin[sizeof(x_StaticBin)/sizeof(struct xBin_s)-1];
  }
  {
    int i;
    for(i=1;i<=X_MAX_SMALL_BLOCK;i++)
    {
      xBin b=xGetBin(i);
      if (i>(b->sizeInWords*sizeof(long))) printf("problem with xGetBin(%d)\n",i);
    }
  }
  {
  }
  {
     xBlock B;
     long s;
     xPage n=(xPage)xGetNewPage();
     xBlock t=(xBlock)&(n->data);
     unsigned long header=(unsigned long)(t)-(unsigned long)n;
     xMakePage(n,x_StaticBin[0].sizeInWords*sizeof(long));
     B=n->free;
     s=0;
     while(B!=NULL)
     {
        s+=x_StaticBin[0].sizeInWords*sizeof(long);
        B=B->next;
     }
  }
  return 0;
}
