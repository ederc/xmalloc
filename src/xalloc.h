#ifndef XMEMORY_H
#define XMEMORY_H
/****************************************
*  Cxputer Algebra System SINGULAR     *
****************************************/
/* $Id: mmemory.h,v 1.9 1998/06/02 15:29:58 Singular Exp $ */
/*
* ABSTRACT
*/
#include <stdlib.h>
#include <string.h>

#define X_XALLOC

#ifdef __cplusplus
extern "C" {
#endif

enum xError_e
{
  xError_NoError = 0,
  xError_Unknown,
  xError_InternalBug,
  xError_MemoryCorrupted,
  xError_NullAddr,
  xError_InvalidRangeAddr,
  xError_FalseAddr,
  xError_FalseAddrOrMemoryCorrupted,
  xError_WrongSize,
  xError_FreedAddr,
  xError_FreedAddrOrMemoryCorrupted,
  xError_WrongBin,
  xError_UnknownBin,
  xError_NotBinAddr,
  xError_UnalignedAddr,
  xError_NullSizeAlloc,
  xError_ListCycleError,
  xError_SortedListError,
  xError_KeptAddrListCorrupted,
  xError_FreePattern,
  xError_BackPattern,
  xError_FrontPattern,
  xError_NotString,
  xError_StickyBin,
  xError_MaxError
};

struct xPage_s;
typedef struct xPage_s * xPage;

struct xBin_s
{
  xPage current;
  xPage last;
  long sizeW; /* size in words */
};
typedef struct xBin_s * xBin;


struct xInfo_s;
typedef struct xInfo_s xInfo_t;
struct xInfo_s
{
  long MaxBytesSystem;      /* set in xUpdateInfo(), is more accurate with malloc support   */
  long CurrentBytesSystem;  /* set in xUpdateInfo(), is more accurate with malloc support */
  long MaxBytesSbrk;        /* always up-to-date, not very accurate, needs xInintInfo() */
  long CurrentBytesSbrk;    /* set in xUpdateInfo(), needs xInintInfo() */
  long MaxBytesMmap;        /* set in xUpdateInfo(), not very accurate */
  long CurrentBytesMmap;    /* set in xUpdateInfo(), not very accurate */
  long UsedBytes;           /* set in xUpdateInfo() */
  long AvailBytes;          /* set in xUpdateInfo() */
  long UsedBytesMalloc;     /* set in xUpdateInfo(), needs malloc support */
  long AvailBytesMalloc;    /* set in xUpdateInfo(), needs malloc support */
  long MaxBytesFromMalloc;      /* always kept up-to-date */
  long CurrentBytesFromMalloc;  /* always kept up-to-date */
  long MaxBytesFromValloc;      /* always kept up-to-date */
  long CurrentBytesFromValloc;  /* always kept up-to-date */
  long UsedBytesFromValloc; /* set in xUpdateInfo()  */
  long AvailBytesFromValloc;/* set in xUpdateInfo()  */
  long MaxPages;            /* always kept up-to-date */
  long UsedPages;           /* always kept up-to-date */
  long AvailPages;          /* always kept up-to-date */
  long MaxRegionsAlloc;     /* always kept up-to-date */
  long CurrentRegionsAlloc; /* always kept up-to-date */
};

extern struct xInfo_s x_Info;

struct xOpts_s;
extern struct xOpts_s
{
  int MinTrack;
  int MinCheck;
  int MaxTrack;
  int MaxCheck;
  int Keep;
  int HowToReportErrors;
  int MarkAsStatic;
  unsigned int PagesPerRegion;
  void (*OutOfMemoryFunc)();
  void (*MemoryLowFunc)();
  void (*ErrorHook)();
} x_Opts;

typedef struct xOpts_s xOpts_t;

struct xBlock_s;
typedef struct xBlock_s * xBlock;
struct xBlock_s
{
  xBlock next;
};

struct xRegion_s;
typedef struct xRegion_s * xRegion;

extern int x_sing_opt_show_mem;

void * xAlloc(size_t s);
void * xalloc(size_t s);
void xFree(void *r);
void xfree(void *r);

void xFreeSizeFunc(void *p, size_t s);

long xSizeOfAddr(void *d);
xRegion xIsBinBlock(unsigned long r);

static inline void * xAlloc0(size_t s)
{ void *d=xAlloc(s);memset(d,0,s); return d; }


static inline void *xRealloc0(void *d, size_t ns)
{
  void *n=xAlloc0(ns);
  if (d!=NULL)
  {
    size_t c;
    size_t os=xSizeOfAddr(d);
    if (ns>os) c=os; else c=ns;
    memcpy(n,d,c);
    xFree(d);
  }
  return n;
}

static inline void *xRealloc(void *d, size_t ns)
{
  void *n=xAlloc(ns);
  if (d!=NULL)
  {
    size_t c;
    size_t os=xSizeOfAddr(d);
    if (ns>os) c=os; else c=ns;
    memcpy(n,d,c);
    xFree(d);
  }
  return n;
}

static inline void *xReallocSize(void *d, size_t os, size_t ns)
{
  void *n=xAlloc(ns);
  if (d!=NULL)
  {
    size_t c;
    if (ns>os) c=os; else c=ns;
    memcpy(n,d,c);
    xFree(d);
  }
  return n;
}


static inline char * xStrDup(const char *s)
{ 
  size_t l=strlen(s);
  char *ns=(char *)xAlloc(l+1);
  return strcpy(ns,s);
}
static inline void * xMemDup(void * s)
{ 
  size_t os=xSizeOfAddr(s);
  void *n=xAlloc(os);
  memcpy(n,s,os);
  return n;
}

void *xAllocBin(xBin b);
void xFreeBin(void *r, xBin b);
static inline void *xAlloc0Bin(xBin b)
{
  void *r=xAllocBin(b);
  memset(r,0,b->sizeW*sizeof(long));
  return r;
}

xBin xGetSpecBin(size_t s);
void xUnGetSpecBin(xBin *b);

void xInfo();

#define xSizeWOfAddr(P)         (xSizeOfAddr(P)/sizeof(long))
#define xTypeAllocBin(T,P,B)    P=(T)xAllocBin(B)
#define xTypeAlloc(T,P,S)       P=(T)xAlloc(S)
#define xTypeAlloc0(T,P,S)      P=(T)xAlloc0(S)
#define xTypeAlloc0Bin(T,P,B)   P=(T)xAlloc0Bin(B)
#define xAlloc0Aligned(S)       xAlloc0(S)
#define xAllocAligned(S)        xAlloc(S)
//#define xAllocBin(B)            xAlloc(B)
//#define xAlloc0Bin(B)           xAlloc0(B)
#define xInitInfo()             
#define xInitGetBackTrace()
#define xUpdateInfo()             
#define xPrintStats(F)
#define xPrintInfo(F)
#define xPrintBinStats(F)
#define xMarkMemoryAsStatic()
#define xFreeSize(P,S) xFree(P)
#define xfreeSize(P,S)          xFreeSize(P,S)
#define xFreeBinAddr(P)         xFree(P)
#define xrealloc(A,NS)          xRealloc(A,NS)
#define xreallocSize(A,OS,NS)   xRealloc(A,NS)
#define xRealloc0Size(A,OS,NS)  xRealloc0(A,NS)
#define xrealloc0Size(A,OS,NS)  xRealloc(A,NS)
#define xMarkAsStaticAddr(A)
#define xMemCpyW(A,B,S)         memcpy(A,B,(S)*sizeof(long))
#define xMemcpyW(A,B,S)         memcpy(A,B,(S)*sizeof(long))
#define memcpyW(A,B,C)           memcpy(A,B,(C)*sizeof(long))
#define xGetStickyBinOfBin(B) (B)

#define xFreeFunc               xFree

/* debug dummies: */
#define xTypeReallocAlignedSize     xTypeReallocSize
#define xTypeRealloc0AlignedSize    xTypeRealloc0Size
#define xReallocAlignedSize         xReallocSize
#define xRealloc0AlignedSize        xRealloc0Size
#define xMemDupAligned     xMemDup
#define xCheckIf(cond, test)                    ((void) 0)
#define xCheckBinAddr(addr)                     ((void) 0)
#define xCheckAddrBin(addr,bin)                 ((void) 0)
#define xCheckBinAddrSize(addr,size)            ((void) 0)
#define xCheckAddrSize(addr,size)               ((void) 0)
#define xCheckAddr(addr)                        ((void) 0)
#define xcheckAddrSize(addr,size)               ((void) 0)
#define xcheckAddr(addr)                        ((void) 0)
#define xCheckBin(bin)                          ((void) 0)
#define xCheckMemory()                          ((void) 0)
#define xPrintCurrentBackTraceMax(A,B)          ((void) 0)
#define xdebugAddrSize(A,B)                     ((void) 0)
#define xPrintAddrInfo(A,B,C)                   ((void) 0)
#ifdef x_NDEBUG
#define xIsBinPageAddr(A)                       ((void) 0)
#define xTestBinAddrSize(A,B,C)                 ((void) 0)
#else
#define xIsBinPageAddr(A)                       xIsBinBlock((unsigned long)A)
#define xTestBinAddrSize(A,B,C)                 xError_NoError
#endif
#define xTestList(A,B)                          xError_NoError
#define xInitRet_2_Info(argv0)                  ((void) 0)
#define xMergeStickyBinIntoBin(A,B)             ((void) 0)
#define xPrintUsedTrackAddrs(A,B)               ((void) 0)
#define xPrintUsedAddrs(A,B)                    ((void) 0)
#define xPrintCurrentBackTrace(A)               ((void) 0)



char * xFindExec (const char *name, char* executable);

#ifdef __cplusplus
}
#endif

#undef XALLOC_USES_MALLOC
#define X_XALLOC
#define xMallocFunc xAlloc
#define xReallocSizeFunc xReallocSize
/* #define X_NDEBUG */
#undef X_SING_KEEP
#endif
