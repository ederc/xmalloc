#include <stdio.h>
#include "xalloc.h"

#define X_MAX_SMALL_BLOCK 1012

int main()
{
  int i;
  for (i=1;i<X_MAX_SMALL_BLOCK;i++)
  {
    xBin b=xGetSpecBin(i);
    void *p=xAlloc(i);
    if ((i>b->sizeW*4)
    || (b->sizeW*4!=xSizeOfAddr(p)))
      printf(" %d (%d vs %d)\n",i,b->sizeW*4,xSizeOfAddr(p));
    xFree(p);
  }
  return 0;
}
