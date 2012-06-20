#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "xalloc.h"

#define SIZEOF_LONG 4

struct xPage_s
{
   xBin bin;
   xPage prev;
   xPage next;
   long cnt; /* number of used blocks in ths page */
   xBlock free; /* free blocks in this page */
   void *data; /* start of data, must be last*/
};

#if SIZEOF_LONG == 8
#define X_PAGES_PER_REGION 4068
#define X_MAX_SMALL_BLOCK  1008    
   /* 64bit */
#else
#define X_PAGES_PER_REGION 4080
#define X_MAX_SMALL_BLOCK  1016    
   /* 32bit */
#endif
struct xRegion_s
{
  unsigned long start;
  unsigned long end;
  void *next;
  int cnt; /* number of free pages in this region */
  char bits[X_PAGES_PER_REGION];
};
xRegion baseRegion=NULL;

#if SIZEOF_LONG == 8
struct xBin_s x_StaticBin[] = {
{NULL, NULL, 1}, /*0 */
{NULL, NULL, 2}, /*1 */
{NULL, NULL, 3}, /*2 */
{NULL, NULL, 4}, /*3 */
{NULL, NULL, 5}, /*4 */
{NULL, NULL, 6}, /*5 */
{NULL, NULL, 7}, /*6 */
{NULL, NULL, 8}, /*7 */
{NULL, NULL, 9}, /*8 */
{NULL, NULL, 10}, /*9 */
{NULL, NULL, 12}, /*10*/
{NULL, NULL, 14}, /*11*/
{NULL, NULL, 16}, /*12*/
{NULL, NULL, 18}, /*13*/
{NULL, NULL, 20}, /*14*/
{NULL, NULL, 24}, /*15*/
{NULL, NULL, 28}, /*16*/
{NULL, NULL, 38}, /*17*/
{NULL, NULL, 50}, /*18*/
{NULL, NULL, 63}, /*19*/
{NULL, NULL, 84}, /*20*/
{NULL, NULL, 101}, /*21*/
{NULL, NULL, 126}  /*22*/
};

xBin x_Size2Bin[/*126*/] = {
&x_StaticBin[0], /* 8 */
&x_StaticBin[1], /* 16 */
&x_StaticBin[2], /* 24 */
&x_StaticBin[3], /* 32 */
&x_StaticBin[4], /* 40 */
&x_StaticBin[5], /* 48 */
&x_StaticBin[6], /* 56 */
&x_StaticBin[7], /* 64 */
&x_StaticBin[8], /* 72 */
&x_StaticBin[9], /* 80 */
&x_StaticBin[10], /* 88 */
&x_StaticBin[10], /* 96 */
&x_StaticBin[11], /* 104 */
&x_StaticBin[11], /* 112 */
&x_StaticBin[12], /* 120 */
&x_StaticBin[12], /* 128 */
&x_StaticBin[13], /* 136 */
&x_StaticBin[13], /* 144 */
&x_StaticBin[14], /* 152 */
&x_StaticBin[14], /* 160 */
&x_StaticBin[15], /* 168 */
&x_StaticBin[15], /* 176 */
&x_StaticBin[15], /* 184 */
&x_StaticBin[15], /* 192 */
&x_StaticBin[16], /* 200 */
&x_StaticBin[16], /* 208 */
&x_StaticBin[16], /* 216 */
&x_StaticBin[16], /* 224 */
&x_StaticBin[17], /* 232 */
&x_StaticBin[17], /* 240 */
&x_StaticBin[17], /* 248 */
&x_StaticBin[17], /* 256 */
&x_StaticBin[17], /* 264 */
&x_StaticBin[17], /* 272 */
&x_StaticBin[17], /* 280 */
&x_StaticBin[17], /* 288 */
&x_StaticBin[17], /* 296 */
&x_StaticBin[17], /* 304 */
&x_StaticBin[18], /* 312 */
&x_StaticBin[18], /* 320 */
&x_StaticBin[18], /* 328 */
&x_StaticBin[18], /* 336 */
&x_StaticBin[18], /* 344 */
&x_StaticBin[18], /* 352 */
&x_StaticBin[18], /* 360 */
&x_StaticBin[18], /* 368 */
&x_StaticBin[18], /* 376 */
&x_StaticBin[18], /* 384 */
&x_StaticBin[18], /* 392 */
&x_StaticBin[18], /* 400 */
&x_StaticBin[19], /* 408 */
&x_StaticBin[19], /* 416 */
&x_StaticBin[19], /* 424 */
&x_StaticBin[19], /* 432 */
&x_StaticBin[19], /* 440 */
&x_StaticBin[19], /* 448 */
&x_StaticBin[19], /* 456 */
&x_StaticBin[19], /* 464 */
&x_StaticBin[19], /* 472 */
&x_StaticBin[19], /* 480 */
&x_StaticBin[19], /* 488 */
&x_StaticBin[19], /* 496 */
&x_StaticBin[19], /* 504 */
&x_StaticBin[20], /* 512 */
&x_StaticBin[20], /* 520 */
&x_StaticBin[20], /* 528 */
&x_StaticBin[20], /* 536 */
&x_StaticBin[20], /* 544 */
&x_StaticBin[20], /* 552 */
&x_StaticBin[20], /* 560 */
&x_StaticBin[20], /* 568 */
&x_StaticBin[20], /* 576 */
&x_StaticBin[20], /* 584 */
&x_StaticBin[20], /* 592 */
&x_StaticBin[20], /* 600 */
&x_StaticBin[20], /* 608 */
&x_StaticBin[20], /* 616 */
&x_StaticBin[20], /* 624 */
&x_StaticBin[20], /* 632 */
&x_StaticBin[20], /* 640 */
&x_StaticBin[20], /* 648 */
&x_StaticBin[20], /* 656 */
&x_StaticBin[20], /* 664 */
&x_StaticBin[20], /* 672 */
&x_StaticBin[21], /* 680 */
&x_StaticBin[21], /* 688 */
&x_StaticBin[21], /* 696 */
&x_StaticBin[21], /* 704 */
&x_StaticBin[21], /* 712 */
&x_StaticBin[21], /* 720 */
&x_StaticBin[21], /* 728 */
&x_StaticBin[21], /* 736 */
&x_StaticBin[21], /* 744 */
&x_StaticBin[21], /* 752 */
&x_StaticBin[21], /* 760 */
&x_StaticBin[21], /* 768 */
&x_StaticBin[21], /* 776 */
&x_StaticBin[21], /* 784 */
&x_StaticBin[21], /* 792 */
&x_StaticBin[21], /* 800 */
&x_StaticBin[21], /* 808 */
&x_StaticBin[22], /* 816 */
&x_StaticBin[22], /* 824 */
&x_StaticBin[22], /* 832 */
&x_StaticBin[22], /* 840 */
&x_StaticBin[22], /* 848 */
&x_StaticBin[22], /* 856 */
&x_StaticBin[22], /* 864 */
&x_StaticBin[22], /* 872 */
&x_StaticBin[22], /* 880 */
&x_StaticBin[22], /* 888 */
&x_StaticBin[22], /* 896 */
&x_StaticBin[22], /* 904 */
&x_StaticBin[22], /* 912 */
&x_StaticBin[22], /* 920 */
&x_StaticBin[22], /* 928 */
&x_StaticBin[22], /* 936 */
&x_StaticBin[22], /* 944 */
&x_StaticBin[22], /* 952 */
&x_StaticBin[22], /* 960 */
&x_StaticBin[22], /* 968 */
&x_StaticBin[22], /* 976 */
&x_StaticBin[22], /* 984 */
&x_StaticBin[22], /* 992 */
&x_StaticBin[22], /* 1000 */
&x_StaticBin[22] /* 1008 */};
#else
struct xBin_s x_StaticBin[/*24*/] = {
{NULL, NULL, 2}, /* 0 */
{NULL, NULL, 3}, /* 1 */
{NULL, NULL, 4}, /* 2 */
{NULL, NULL, 5}, /* 3 */
{NULL, NULL, 6}, /* 4 */
{NULL, NULL, 7}, /* 5 */
{NULL, NULL, 8}, /* 6 */
{NULL, NULL, 10}, /* 7 */
{NULL, NULL, 12}, /* 8 */
{NULL, NULL, 14}, /* 9 */
{NULL, NULL, 16}, /* 10 */
{NULL, NULL, 20}, /* 11 */
{NULL, NULL, 24}, /* 12 */
{NULL, NULL, 28}, /* 13 */
{NULL, NULL, 32}, /* 14 */
{NULL, NULL, 40}, /* 15 */
{NULL, NULL, 48}, /* 16 */
{NULL, NULL, 56}, /* 17 */
{NULL, NULL, 78}, /* 18 */
{NULL, NULL, 101}, /* 19 */
{NULL, NULL, 127}, /* 20 */
{NULL, NULL, 169}, /* 21 */
{NULL, NULL, 203}, /* 22 */
{NULL, NULL, 254} /* 23 */
};
xBin x_Size2Bin[/*254*/] = {
&x_StaticBin[0], /* 4 */
&x_StaticBin[0], /* 8 */
&x_StaticBin[1], /* 12 */
&x_StaticBin[2], /* 16 */
&x_StaticBin[3], /* 20 */
&x_StaticBin[4], /* 24 */
&x_StaticBin[5], /* 28 */
&x_StaticBin[6], /* 32 */
&x_StaticBin[7], /* 36 */
&x_StaticBin[7], /* 40 */
&x_StaticBin[8], /* 44 */
&x_StaticBin[8], /* 48 */
&x_StaticBin[9], /* 52 */
&x_StaticBin[9], /* 56 */
&x_StaticBin[10], /* 60 */
&x_StaticBin[10], /* 64 */
&x_StaticBin[11], /* 68 */
&x_StaticBin[11], /* 72 */
&x_StaticBin[11], /* 76 */
&x_StaticBin[11], /* 80 */
&x_StaticBin[12], /* 84 */
&x_StaticBin[12], /* 88 */
&x_StaticBin[12], /* 92 */
&x_StaticBin[12], /* 96 */
&x_StaticBin[13], /* 100 */
&x_StaticBin[13], /* 104 */
&x_StaticBin[13], /* 108 */
&x_StaticBin[13], /* 112 */
&x_StaticBin[14], /* 116 */
&x_StaticBin[14], /* 120 */
&x_StaticBin[14], /* 124 */
&x_StaticBin[14], /* 128 */
&x_StaticBin[15], /* 132 */
&x_StaticBin[15], /* 136 */
&x_StaticBin[15], /* 140 */
&x_StaticBin[15], /* 144 */
&x_StaticBin[15], /* 148 */
&x_StaticBin[15], /* 152 */
&x_StaticBin[15], /* 156 */
&x_StaticBin[15], /* 160 */
&x_StaticBin[16], /* 164 */
&x_StaticBin[16], /* 168 */
&x_StaticBin[16], /* 172 */
&x_StaticBin[16], /* 176 */
&x_StaticBin[16], /* 180 */
&x_StaticBin[16], /* 184 */
&x_StaticBin[16], /* 188 */
&x_StaticBin[16], /* 192 */
&x_StaticBin[17], /* 196 */
&x_StaticBin[17], /* 200 */
&x_StaticBin[17], /* 204 */
&x_StaticBin[17], /* 208 */
&x_StaticBin[17], /* 212 */
&x_StaticBin[17], /* 216 */
&x_StaticBin[17], /* 220 */
&x_StaticBin[17], /* 224 */
&x_StaticBin[18], /* 228 */
&x_StaticBin[18], /* 232 */
&x_StaticBin[18], /* 236 */
&x_StaticBin[18], /* 240 */
&x_StaticBin[18], /* 244 */
&x_StaticBin[18], /* 248 */
&x_StaticBin[18], /* 252 */
&x_StaticBin[18], /* 256 */
&x_StaticBin[18], /* 260 */
&x_StaticBin[18], /* 264 */
&x_StaticBin[18], /* 268 */
&x_StaticBin[18], /* 272 */
&x_StaticBin[18], /* 276 */
&x_StaticBin[18], /* 280 */
&x_StaticBin[18], /* 284 */
&x_StaticBin[18], /* 288 */
&x_StaticBin[18], /* 292 */
&x_StaticBin[18], /* 296 */
&x_StaticBin[18], /* 300 */
&x_StaticBin[18], /* 304 */
&x_StaticBin[18], /* 308 */
&x_StaticBin[18], /* 312 */
&x_StaticBin[19], /* 316 */
&x_StaticBin[19], /* 320 */
&x_StaticBin[19], /* 324 */
&x_StaticBin[19], /* 328 */
&x_StaticBin[19], /* 332 */
&x_StaticBin[19], /* 336 */
&x_StaticBin[19], /* 340 */
&x_StaticBin[19], /* 344 */
&x_StaticBin[19], /* 348 */
&x_StaticBin[19], /* 352 */
&x_StaticBin[19], /* 356 */
&x_StaticBin[19], /* 360 */
&x_StaticBin[19], /* 364 */
&x_StaticBin[19], /* 368 */
&x_StaticBin[19], /* 372 */
&x_StaticBin[19], /* 376 */
&x_StaticBin[19], /* 380 */
&x_StaticBin[19], /* 384 */
&x_StaticBin[19], /* 388 */
&x_StaticBin[19], /* 392 */
&x_StaticBin[19], /* 396 */
&x_StaticBin[19], /* 400 */
&x_StaticBin[19], /* 404 */
&x_StaticBin[20], /* 408 */
&x_StaticBin[20], /* 412 */
&x_StaticBin[20], /* 416 */
&x_StaticBin[20], /* 420 */
&x_StaticBin[20], /* 424 */
&x_StaticBin[20], /* 428 */
&x_StaticBin[20], /* 432 */
&x_StaticBin[20], /* 436 */
&x_StaticBin[20], /* 440 */
&x_StaticBin[20], /* 444 */
&x_StaticBin[20], /* 448 */
&x_StaticBin[20], /* 452 */
&x_StaticBin[20], /* 456 */
&x_StaticBin[20], /* 460 */
&x_StaticBin[20], /* 464 */
&x_StaticBin[20], /* 468 */
&x_StaticBin[20], /* 472 */
&x_StaticBin[20], /* 476 */
&x_StaticBin[20], /* 480 */
&x_StaticBin[20], /* 484 */
&x_StaticBin[20], /* 488 */
&x_StaticBin[20], /* 492 */
&x_StaticBin[20], /* 496 */
&x_StaticBin[20], /* 500 */
&x_StaticBin[20], /* 504 */
&x_StaticBin[20], /* 508 */
&x_StaticBin[21], /* 512 */
&x_StaticBin[21], /* 516 */
&x_StaticBin[21], /* 520 */
&x_StaticBin[21], /* 524 */
&x_StaticBin[21], /* 528 */
&x_StaticBin[21], /* 532 */
&x_StaticBin[21], /* 536 */
&x_StaticBin[21], /* 540 */
&x_StaticBin[21], /* 544 */
&x_StaticBin[21], /* 548 */
&x_StaticBin[21], /* 552 */
&x_StaticBin[21], /* 556 */
&x_StaticBin[21], /* 560 */
&x_StaticBin[21], /* 564 */
&x_StaticBin[21], /* 568 */
&x_StaticBin[21], /* 572 */
&x_StaticBin[21], /* 576 */
&x_StaticBin[21], /* 580 */
&x_StaticBin[21], /* 584 */
&x_StaticBin[21], /* 588 */
&x_StaticBin[21], /* 592 */
&x_StaticBin[21], /* 596 */
&x_StaticBin[21], /* 600 */
&x_StaticBin[21], /* 604 */
&x_StaticBin[21], /* 608 */
&x_StaticBin[21], /* 612 */
&x_StaticBin[21], /* 616 */
&x_StaticBin[21], /* 620 */
&x_StaticBin[21], /* 624 */
&x_StaticBin[21], /* 628 */
&x_StaticBin[21], /* 632 */
&x_StaticBin[21], /* 636 */
&x_StaticBin[21], /* 640 */
&x_StaticBin[21], /* 644 */
&x_StaticBin[21], /* 648 */
&x_StaticBin[21], /* 652 */
&x_StaticBin[21], /* 656 */
&x_StaticBin[21], /* 660 */
&x_StaticBin[21], /* 664 */
&x_StaticBin[21], /* 668 */
&x_StaticBin[21], /* 672 */
&x_StaticBin[21], /* 676 */
&x_StaticBin[22], /* 680 */
&x_StaticBin[22], /* 684 */
&x_StaticBin[22], /* 688 */
&x_StaticBin[22], /* 692 */
&x_StaticBin[22], /* 696 */
&x_StaticBin[22], /* 700 */
&x_StaticBin[22], /* 704 */
&x_StaticBin[22], /* 708 */
&x_StaticBin[22], /* 712 */
&x_StaticBin[22], /* 716 */
&x_StaticBin[22], /* 720 */
&x_StaticBin[22], /* 724 */
&x_StaticBin[22], /* 728 */
&x_StaticBin[22], /* 732 */
&x_StaticBin[22], /* 736 */
&x_StaticBin[22], /* 740 */
&x_StaticBin[22], /* 744 */
&x_StaticBin[22], /* 748 */
&x_StaticBin[22], /* 752 */
&x_StaticBin[22], /* 756 */
&x_StaticBin[22], /* 760 */
&x_StaticBin[22], /* 764 */
&x_StaticBin[22], /* 768 */
&x_StaticBin[22], /* 772 */
&x_StaticBin[22], /* 776 */
&x_StaticBin[22], /* 780 */
&x_StaticBin[22], /* 784 */
&x_StaticBin[22], /* 788 */
&x_StaticBin[22], /* 792 */
&x_StaticBin[22], /* 796 */
&x_StaticBin[22], /* 800 */
&x_StaticBin[22], /* 804 */
&x_StaticBin[22], /* 808 */
&x_StaticBin[22], /* 812 */
&x_StaticBin[23], /* 816 */
&x_StaticBin[23], /* 820 */
&x_StaticBin[23], /* 824 */
&x_StaticBin[23], /* 828 */
&x_StaticBin[23], /* 832 */
&x_StaticBin[23], /* 836 */
&x_StaticBin[23], /* 840 */
&x_StaticBin[23], /* 844 */
&x_StaticBin[23], /* 848 */
&x_StaticBin[23], /* 852 */
&x_StaticBin[23], /* 856 */
&x_StaticBin[23], /* 860 */
&x_StaticBin[23], /* 864 */
&x_StaticBin[23], /* 868 */
&x_StaticBin[23], /* 872 */
&x_StaticBin[23], /* 876 */
&x_StaticBin[23], /* 880 */
&x_StaticBin[23], /* 884 */
&x_StaticBin[23], /* 888 */
&x_StaticBin[23], /* 892 */
&x_StaticBin[23], /* 896 */
&x_StaticBin[23], /* 900 */
&x_StaticBin[23], /* 904 */
&x_StaticBin[23], /* 908 */
&x_StaticBin[23], /* 912 */
&x_StaticBin[23], /* 916 */
&x_StaticBin[23], /* 920 */
&x_StaticBin[23], /* 924 */
&x_StaticBin[23], /* 928 */
&x_StaticBin[23], /* 932 */
&x_StaticBin[23], /* 936 */
&x_StaticBin[23], /* 940 */
&x_StaticBin[23], /* 944 */
&x_StaticBin[23], /* 948 */
&x_StaticBin[23], /* 952 */
&x_StaticBin[23], /* 956 */
&x_StaticBin[23], /* 960 */
&x_StaticBin[23], /* 964 */
&x_StaticBin[23], /* 968 */
&x_StaticBin[23], /* 972 */
&x_StaticBin[23], /* 976 */
&x_StaticBin[23], /* 980 */
&x_StaticBin[23], /* 984 */
&x_StaticBin[23], /* 988 */
&x_StaticBin[23], /* 992 */
&x_StaticBin[23], /* 996 */
&x_StaticBin[23], /* 1000 */
&x_StaticBin[23], /* 1004 */
&x_StaticBin[23], /* 1008 */
&x_StaticBin[23], /* 1012 */
&x_StaticBin[23] /* 1016 */};
#endif

xPage xGetPageFromBlock(void *r)
{
  unsigned long rr=(unsigned long)r;
  rr &= ~4095;
  return (xPage)rr;
}

long xSizeOfAddr(void *d)
{
  xRegion R=xIsBinBlock((unsigned long)d);
  if (R!=NULL)
  {
    xPage p=xGetPageFromBlock(d);
    return p->bin->sizeW*sizeof(long);
  }
  else
  {
    long *dd=(long*)d; dd--; return *dd;
  }
}

void xMakePage(void * page, size_t s)
{
  xPage p=(xPage)page;
  xBlock t=(xBlock)&(p->data);
  /*unsigned long header=(unsigned long)t-(unsigned long)p;*/
  #if 1
  memset((void *)p,0,4096);
  #else
  p->free=0;
  p->cnt=0;
  #endif
  while (((unsigned long)t)+s<=(((unsigned long)p)+4096))
  {
    t->next=p->free;
    p->free=t;
    t=(xBlock)(((unsigned long)t)+s);
  }
  if (p->free==NULL)
  {
    printf("xMakePage(%ld)\n",(long)s);
  }
}

xRegion xAllocRegion()
{
  xRegion R=(xRegion)malloc(sizeof(*R));
  void *p;
  memset(R,0,sizeof(*R));
  posix_memalign(&p,4096,4096*X_PAGES_PER_REGION);
  R->start=(unsigned long)p;
  R->end=R->start+4096*X_PAGES_PER_REGION;
  R->cnt=X_PAGES_PER_REGION;
  R->next=baseRegion;
  baseRegion=R;
  return R;
}

void *xGetNewPage()
{
  xRegion R=baseRegion;
  int i;
  while(1)
  {
    if (R==NULL)
    {
      R=xAllocRegion();
    }
    if (R->cnt>0)
    {
      for(i=0;i<X_PAGES_PER_REGION;i++)
      {
        if (R->bits[i]=='\0')
        {
	  R->cnt--;
          R->bits[i]='\1';
          return (void*)(R->start+i*4096UL);
        }
      }
    }
    R=R->next;
  }
}

xBin xGetBin(size_t s)
{
  if (s<=X_MAX_SMALL_BLOCK)
  return x_Size2Bin[(s-1)/(sizeof(long))];
  #if 0
  #if SIZEOF_LONG == 4
  else if (s<=2036) return &x_StaticBin[24];
  #else
  else if (s<=2028) return &x_StaticBin[23];
  #endif
  #endif
  return NULL;
}

xPage xPageForMalloc=(xPage)1;

xBin xGetSpecBin(size_t s)
{
  xBin b=xGetBin(s);
  if (b==NULL)
  {
    b=(xBin)malloc(sizeof(*b));
    memset(b,0,sizeof(*b));
    b->sizeW=(s+sizeof(long)-1)/sizeof(long);
    b->current=xPageForMalloc;
  }
  return b;
}

void xUnGetSpecBin(xBin* b)
{
  if (*b==NULL) printf("xUnGetSpecBin(NULL\n");
  else
  if ((*b)->current==xPageForMalloc)
  {
    /* TODO */
    free(*b);
  }
  *b=NULL;
}


xPage xGetPageFromBin(xBin b)
{
  if (b->current!=NULL)
  {
    if (b->current->free!=NULL)
      return b->current;
    else
    {
      xPage n=b->last;
      while ((n!=NULL)&&(n->free==NULL)) n=n->prev;
      if ((n!=NULL)&&(n->free!=NULL)) { b->current=n; return n; }
    }
  }
  /* now b->current==NULL or all pages are full */
  {
    //extern void *xGetNewPage();
     xPage n=(xPage)xGetNewPage();
     xMakePage(n,b->sizeW*sizeof(long));
     n->prev=b->last;
     n->next=NULL;
     if (b->last!=NULL) b->last->next=n;
     b->last=n;
     b->current=n;
     n->bin=b;
     return n;
  }
  return b->current;
}

xPage xGetPageFromSize(size_t s)
{
  xBin b=xGetBin(s);
  return xGetPageFromBin(b);
}

void * xAllocFromPage(xPage p)
{
  xBlock r=p->free;
  p->free=r->next;
  p->cnt++;
  memset(r,0,p->bin->sizeW*sizeof(long)); /*debug!*/
  return (void *)r;
}

void * xAlloc(size_t s)
{
  /*assume (s>0);*/
  if (s<=X_MAX_SMALL_BLOCK)
  {
    xPage page=xGetPageFromSize(s);
    return xAllocFromPage(page);
  }
  else
  {
     long *d=(long*)malloc(s+sizeof(long)); *d=s;d++;return d;
  }
}

void * xalloc(size_t s)
{
  if (s>0)
  {
    return xAlloc(s);
  }
  else
    return NULL;
}

void xFreeToPage(xPage p, void *r)
{
  xBlock rr=(xBlock)r;
  rr->next=p->free;
  p->free=rr;
  p->cnt--;
}

xRegion xIsSmallBlock(void *r)
{
  xRegion R=baseRegion;
  unsigned long rr=(unsigned long)r;
  while(R!=NULL)
  {
    if ((R->start>rr)||(R->end<=rr)) R=R->next;
    else return R;
  }
  return NULL;
}

void *xAllocBin(xBin b)
{
  xPage p=b->current;
  if (p==xPageForMalloc) return xAlloc(b->sizeW*sizeof(long));
  p=xGetPageFromBin(b);
  return xAllocFromPage(p);
}

xRegion xIsBinBlock(unsigned long r)
{
  xRegion R=baseRegion;
  while (R!=NULL)
  {
    unsigned long rs=R->start;
    if ((rs <=r) && (r < R->end))
    {
      if (R->bits[(r-rs)/4096UL]) return R;
      else return NULL;
    }
    R=R->next;
  }
  return NULL;
}

void xFreeBinRegion(xRegion R,void *r)
{
  xPage p=xGetPageFromBlock(r);
  if (p->cnt >1)
  {
    *((void**) (r)) = p->free;
    p->free=r;
    p->cnt--;
  }
  else
  {
    xBin b=p->bin;
    unsigned long ur=(unsigned long)r;
    if (p->next!=NULL) p->next->prev=p->prev; 
    if (p->prev!=NULL) p->prev->next=p->next; 
    if (b->last==p) b->last=p->prev;
    if (b->current==p) b->current=p->prev;
    R->cnt++;
    R->bits[(ur-R->start)/4096]='\0';
  }
}

void xFreeBin(void *r, xBin b)
{
  
  if (b->current==xPageForMalloc) { xFree(r);return;}
  xPage p=xGetPageFromBlock(r);
  if (p->cnt >1)
  {
    *((void**) (r)) = p->free;
    p->free=r;
    p->cnt--;
  }
  else
  {
    xRegion R=xIsBinBlock((unsigned long)r);
    /*xBin b=p->bin;*/
    if (p->next!=NULL) p->next->prev=p->prev; 
    if (p->prev!=NULL) p->prev->next=p->next; 
    if (b->last==p) b->last=p->prev;
    if (b->current==p) b->current=p->prev;
    R->cnt++;
    R->bits[(((unsigned long)r)-R->start)/4096]='\0';
  }
}

void xFree(void *r)
{
  if (r==NULL) 
    printf("xFree(NULL)\n");
  else
  {
  /*assume (r!=NULL);*/
  xRegion R=xIsBinBlock((unsigned long)r);
  if (R!=NULL) xFreeBinRegion(R,r);
  else
  {  
    long *dd=(long*)r; 
    dd--; 
    free(dd);
  }
  }
}

void xfree(void *r)
{
  if (r!=NULL) xFree(r);
}

void xFreeSizeFunc(void *r, size_t s) { xFree(r); }

void xInfo()
{
  int i=0;
  int kb=0;
  int kb2=0;
  xRegion R=baseRegion;
  while (R!=NULL)
  {
    int j;
    printf("region %d (%lx - %lx), free pages %d\n",i,R->start,R->end,R->cnt);
    kb2+=(X_PAGES_PER_REGION-R->cnt)*4;
    i++;
    R=R->next;
    kb+=(4*X_PAGES_PER_REGION)+4;
  }
  printf("allocated kB: %d, used kb: %d\n",kb,kb2);
  for(i=0;i<23;i++)
  {
    xPage p=x_StaticBin[i].current;
    kb=0;
    while (p!=NULL) { kb++; p=p->prev; }
    p=x_StaticBin[i].current;
    kb2=(p!=NULL) -1;
    while (p!=NULL) { kb2++; p=p->next; }
    printf("bin %d, sizeW=%ld, curr=%lx, pages: %d + %d\n",i,x_StaticBin[i].sizeW,(unsigned long)x_StaticBin[i].current, kb, kb2);
  }
}
