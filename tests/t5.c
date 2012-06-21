/* Copyright 2012 Hans Schoenemann
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include <xmalloc.h>

int main()
{
  printf("check __XMALLOC_SIZEOF_LONG: %d == %d sizeof(long)\n",__XMALLOC_SIZEOF_LONG,(int)sizeof(long));
  {
    printf("check X_MAX_SMALL_BLOCK:\n");
    xBin b=&x_StaticBin[sizeof(x_StaticBin)/sizeof(struct xBin_s)-1];
    printf("  x_StaticBin: %ld==X_MAX_SMALL_BLOCK: %d\n",b->sizeW*sizeof(long), X_MAX_SMALL_BLOCK);
  }
  {
    int i;
    for(i=1;i<=X_MAX_SMALL_BLOCK;i++)
    {
      xBin b=xGetBin(i);
      if (i>(b->sizeW*sizeof(long))) printf("problem with xGetBin(%d)\n",i);
    }
  }
  {
    printf("check X_PAGES_PER_REGION: %d==4096\n",(int)sizeof(struct xRegion_s));
  }
  {
     xBlock B;
     long s;
     xPage n=(xPage)xGetNewPage();
     xBlock t=(xBlock)&(n->data);
     unsigned long header=(unsigned long)(t)-(unsigned long)n;
     xMakePage(n,x_StaticBin[0].sizeW*sizeof(long));
     B=n->free;
     s=0;
     while(B!=NULL)
     {
        s+=x_StaticBin[0].sizeW*sizeof(long);
        B=B->next;
     }
     printf("check xMakePage: %ld bytes (one more: %ld, header: %ld)\n",
      s,s+x_StaticBin[0].sizeW*sizeof(long),header);
  }
  return 0;
}
