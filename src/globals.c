/**
 * \file   globals.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  General source file for global stuff.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "src/data.h"
#include "src/globals.h"

// extern declaration in globals.h --- start
xSpecBin xBaseSpecBin     = NULL;
xBin __XMALLOC_LARGE_BIN  = (xBin) 1;

struct xBinStruct xStaticBin[/*23*/] = {
{__XMALLOC_ZERO_PAGE, NULL, NULL, 1,    506,  0}, /* 0*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 2,    253,  0}, /* 1*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 3,    168,  0}, /* 2*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 4,    126,  0}, /* 3*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 5,    101,  0}, /* 4*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 6,    84,   0}, /* 5*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 7,    72,   0}, /* 6*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 8,    63,   0}, /* 7*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 9,    56,   0}, /* 8*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 10,   50,   0}, /* 9*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 12,   42,   0}, /*10*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 14,   36,   0}, /*11*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 16,   31,   0}, /*12*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 18,   28,   0}, /*13*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 20,   25,   0}, /*14*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 24,   21,   0}, /*15*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 28,   18,   0}, /*16*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 38,   13,   0}, /*17*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 50,   10,   0}, /*18*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 63,   8,    0}, /*19*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 84,   6,    0}, /*20*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 101,  5,    0}, /*21*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 126,  4,    0}  /*22*/
};

xBin xSize2Bin[/*126*/] = {
&xStaticBin[0],   /*    8 */
&xStaticBin[1],   /*   16 */
&xStaticBin[2],   /*   24 */
&xStaticBin[3],   /*   32 */
&xStaticBin[4],   /*   40 */
&xStaticBin[5],   /*   48 */
&xStaticBin[6],   /*   56 */
&xStaticBin[7],   /*   64 */
&xStaticBin[8],   /*   72 */
&xStaticBin[9],   /*   80 */
&xStaticBin[10],  /*   88 */
&xStaticBin[10],  /*   96 */
&xStaticBin[11],  /*  104 */
&xStaticBin[11],  /*  112 */
&xStaticBin[12],  /*  120 */
&xStaticBin[12],  /*  128 */
&xStaticBin[13],  /*  136 */
&xStaticBin[13],  /*  144 */
&xStaticBin[14],  /*  152 */
&xStaticBin[14],  /*  160 */
&xStaticBin[15],  /*  168 */
&xStaticBin[15],  /*  176 */
&xStaticBin[15],  /*  184 */
&xStaticBin[15],  /*  192 */
&xStaticBin[16],  /*  200 */
&xStaticBin[16],  /*  208 */
&xStaticBin[16],  /*  216 */
&xStaticBin[16],  /*  224 */
&xStaticBin[17],  /*  232 */
&xStaticBin[17],  /*  240 */
&xStaticBin[17],  /*  248 */
&xStaticBin[17],  /*  256 */
&xStaticBin[17],  /*  264 */
&xStaticBin[17],  /*  272 */
&xStaticBin[17],  /*  280 */
&xStaticBin[17],  /*  288 */
&xStaticBin[17],  /*  296 */
&xStaticBin[17],  /*  304 */
&xStaticBin[18],  /*  312 */
&xStaticBin[18],  /*  320 */
&xStaticBin[18],  /*  328 */
&xStaticBin[18],  /*  336 */
&xStaticBin[18],  /*  344 */
&xStaticBin[18],  /*  352 */
&xStaticBin[18],  /*  360 */
&xStaticBin[18],  /*  368 */
&xStaticBin[18],  /*  376 */
&xStaticBin[18],  /*  384 */
&xStaticBin[18],  /*  392 */
&xStaticBin[18],  /*  400 */
&xStaticBin[19],  /*  408 */
&xStaticBin[19],  /*  416 */
&xStaticBin[19],  /*  424 */
&xStaticBin[19],  /*  432 */
&xStaticBin[19],  /*  440 */
&xStaticBin[19],  /*  448 */
&xStaticBin[19],  /*  456 */
&xStaticBin[19],  /*  464 */
&xStaticBin[19],  /*  472 */
&xStaticBin[19],  /*  480 */
&xStaticBin[19],  /*  488 */
&xStaticBin[19],  /*  496 */
&xStaticBin[19],  /*  504 */
&xStaticBin[20],  /*  512 */
&xStaticBin[20],  /*  520 */
&xStaticBin[20],  /*  528 */
&xStaticBin[20],  /*  536 */
&xStaticBin[20],  /*  544 */
&xStaticBin[20],  /*  552 */
&xStaticBin[20],  /*  560 */
&xStaticBin[20],  /*  568 */
&xStaticBin[20],  /*  576 */
&xStaticBin[20],  /*  584 */
&xStaticBin[20],  /*  592 */
&xStaticBin[20],  /*  600 */
&xStaticBin[20],  /*  608 */
&xStaticBin[20],  /*  616 */
&xStaticBin[20],  /*  624 */
&xStaticBin[20],  /*  632 */
&xStaticBin[20],  /*  640 */
&xStaticBin[20],  /*  648 */
&xStaticBin[20],  /*  656 */
&xStaticBin[20],  /*  664 */
&xStaticBin[20],  /*  672 */
&xStaticBin[21],  /*  680 */
&xStaticBin[21],  /*  688 */
&xStaticBin[21],  /*  696 */
&xStaticBin[21],  /*  704 */
&xStaticBin[21],  /*  712 */
&xStaticBin[21],  /*  720 */
&xStaticBin[21],  /*  728 */
&xStaticBin[21],  /*  736 */
&xStaticBin[21],  /*  744 */
&xStaticBin[21],  /*  752 */
&xStaticBin[21],  /*  760 */
&xStaticBin[21],  /*  768 */
&xStaticBin[21],  /*  776 */
&xStaticBin[21],  /*  784 */
&xStaticBin[21],  /*  792 */
&xStaticBin[21],  /*  800 */
&xStaticBin[21],  /*  808 */
&xStaticBin[22],  /*  816 */
&xStaticBin[22],  /*  824 */
&xStaticBin[22],  /*  832 */
&xStaticBin[22],  /*  840 */
&xStaticBin[22],  /*  848 */
&xStaticBin[22],  /*  856 */
&xStaticBin[22],  /*  864 */
&xStaticBin[22],  /*  872 */
&xStaticBin[22],  /*  880 */
&xStaticBin[22],  /*  888 */
&xStaticBin[22],  /*  896 */
&xStaticBin[22],  /*  904 */
&xStaticBin[22],  /*  912 */
&xStaticBin[22],  /*  920 */
&xStaticBin[22],  /*  928 */
&xStaticBin[22],  /*  936 */
&xStaticBin[22],  /*  944 */
&xStaticBin[22],  /*  952 */
&xStaticBin[22],  /*  960 */
&xStaticBin[22],  /*  968 */
&xStaticBin[22],  /*  976 */
&xStaticBin[22],  /*  984 */
&xStaticBin[22],  /*  992 */
&xStaticBin[22],  /* 1000 */
&xStaticBin[22]   /* 1008 */};

xBin xStickyBins  = NULL;

/************************************
 * STATISTICS / XINFO STUFF
 ***********************************/
xInfo info  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long xSbrkInit = 0;

void xUpdateInfo() {
  if (info.currentBytesFromMalloc < 0)
    info.currentBytesFromMalloc = 0;

  info.usedBytesFromValloc  = 1;
}

void xPrintInfo() {
  xUpdateInfo();
  /*
  printf("                  Current:       Max:\n");
  printf("BytesSystem:     %8ldk  %8ldk\n", info.currentBytesSystem/1024, info.maxBytesSystem/1024);
  printf("BytesSbrk:       %8ldk  %8ldk\n", info.currentBytesSbrk/1024, info.maxBytesSbrk/1024);
  printf("BytesMmap:       %8ldk  %8ldk\n", info.currentBytesMmap/1024, info.maxBytesMmap/1024);
  printf("BytesFromMalloc: %8ldk  %8ldk\n", info.currentBytesFromMalloc/1024, info.maxBytesFromMalloc/1024);
  printf("BytesFromValloc: %8ldk  %8ldk\n", info.currentBytesFromValloc/1024, info.maxBytesFromValloc/1024);
  printf("PagesAlloc:      %8ld   %8ld \n", info.usedPages, info.maxPages);
  printf("RegionsAlloc:    %8ld   %8ld \n", info.currentRegionsAlloc, info.maxRegionsAlloc);
  printf("                     Used:     Avail:\n");
  printf("BytesAppl:       %8ldk  %8ldk\n", info.usedBytes/1024, info.availableBytes/1024);
  printf("BytesMalloc:     %8ldk  %8ldk\n", info.usedBytesMalloc/1024, info.availableBytesMalloc/1024);
  printf("BytesValloc:     %8ldk  %8ldk\n", info.usedBytesFromValloc/1024, info.availableBytesFromValloc/1024);
  printf("Pages:           %8ld   %8ld\n", info.usedPages, info.availablePages);
  */
}
// extern declaration in globals.h --- end
/************************************************
 * NOTE: These definitions need to be here since
 *       the functionality of getting and freeing
 *       xSpecBins need to be allocated here
 ***********************************************/
