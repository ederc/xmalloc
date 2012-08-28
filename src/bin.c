/**
 * @file   xBin.c
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline bin handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include "src/bin.h"

xPage xPageForMalloc  = (xPage)1;
xRegion xxBaseRegion    = NULL;
xSpecBin xBaseSpecBin  = NULL;

#if __XMALLOC_SIZEOF_LONG == 8
struct xBinStruct xStaticBin[] = {
{__XMALLOC_ZERO_PAGE, NULL, NULL, 1}, /*0 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 2}, /*1 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 3}, /*2 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 4}, /*3 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 5}, /*4 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 6}, /*5 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 7}, /*6 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 8}, /*7 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 9}, /*8 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 10}, /*9 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 12}, /*10*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 14}, /*11*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 16}, /*12*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 18}, /*13*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 20}, /*14*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 24}, /*15*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 28}, /*16*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 38}, /*17*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 50}, /*18*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 63}, /*19*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 84}, /*20*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 101}, /*21*/
{__XMALLOC_ZERO_PAGE, NULL, NULL, 126}  /*22*/
};

xBin xSize2Bin[/*126*/] = {
&xStaticBin[0], /* 8 */
&xStaticBin[1], /* 16 */
&xStaticBin[2], /* 24 */
&xStaticBin[3], /* 32 */
&xStaticBin[4], /* 40 */
&xStaticBin[5], /* 48 */
&xStaticBin[6], /* 56 */
&xStaticBin[7], /* 64 */
&xStaticBin[8], /* 72 */
&xStaticBin[9], /* 80 */
&xStaticBin[10], /* 88 */
&xStaticBin[10], /* 96 */
&xStaticBin[11], /* 104 */
&xStaticBin[11], /* 112 */
&xStaticBin[12], /* 120 */
&xStaticBin[12], /* 128 */
&xStaticBin[13], /* 136 */
&xStaticBin[13], /* 144 */
&xStaticBin[14], /* 152 */
&xStaticBin[14], /* 160 */
&xStaticBin[15], /* 168 */
&xStaticBin[15], /* 176 */
&xStaticBin[15], /* 184 */
&xStaticBin[15], /* 192 */
&xStaticBin[16], /* 200 */
&xStaticBin[16], /* 208 */
&xStaticBin[16], /* 216 */
&xStaticBin[16], /* 224 */
&xStaticBin[17], /* 232 */
&xStaticBin[17], /* 240 */
&xStaticBin[17], /* 248 */
&xStaticBin[17], /* 256 */
&xStaticBin[17], /* 264 */
&xStaticBin[17], /* 272 */
&xStaticBin[17], /* 280 */
&xStaticBin[17], /* 288 */
&xStaticBin[17], /* 296 */
&xStaticBin[17], /* 304 */
&xStaticBin[18], /* 312 */
&xStaticBin[18], /* 320 */
&xStaticBin[18], /* 328 */
&xStaticBin[18], /* 336 */
&xStaticBin[18], /* 344 */
&xStaticBin[18], /* 352 */
&xStaticBin[18], /* 360 */
&xStaticBin[18], /* 368 */
&xStaticBin[18], /* 376 */
&xStaticBin[18], /* 384 */
&xStaticBin[18], /* 392 */
&xStaticBin[18], /* 400 */
&xStaticBin[19], /* 408 */
&xStaticBin[19], /* 416 */
&xStaticBin[19], /* 424 */
&xStaticBin[19], /* 432 */
&xStaticBin[19], /* 440 */
&xStaticBin[19], /* 448 */
&xStaticBin[19], /* 456 */
&xStaticBin[19], /* 464 */
&xStaticBin[19], /* 472 */
&xStaticBin[19], /* 480 */
&xStaticBin[19], /* 488 */
&xStaticBin[19], /* 496 */
&xStaticBin[19], /* 504 */
&xStaticBin[20], /* 512 */
&xStaticBin[20], /* 520 */
&xStaticBin[20], /* 528 */
&xStaticBin[20], /* 536 */
&xStaticBin[20], /* 544 */
&xStaticBin[20], /* 552 */
&xStaticBin[20], /* 560 */
&xStaticBin[20], /* 568 */
&xStaticBin[20], /* 576 */
&xStaticBin[20], /* 584 */
&xStaticBin[20], /* 592 */
&xStaticBin[20], /* 600 */
&xStaticBin[20], /* 608 */
&xStaticBin[20], /* 616 */
&xStaticBin[20], /* 624 */
&xStaticBin[20], /* 632 */
&xStaticBin[20], /* 640 */
&xStaticBin[20], /* 648 */
&xStaticBin[20], /* 656 */
&xStaticBin[20], /* 664 */
&xStaticBin[20], /* 672 */
&xStaticBin[21], /* 680 */
&xStaticBin[21], /* 688 */
&xStaticBin[21], /* 696 */
&xStaticBin[21], /* 704 */
&xStaticBin[21], /* 712 */
&xStaticBin[21], /* 720 */
&xStaticBin[21], /* 728 */
&xStaticBin[21], /* 736 */
&xStaticBin[21], /* 744 */
&xStaticBin[21], /* 752 */
&xStaticBin[21], /* 760 */
&xStaticBin[21], /* 768 */
&xStaticBin[21], /* 776 */
&xStaticBin[21], /* 784 */
&xStaticBin[21], /* 792 */
&xStaticBin[21], /* 800 */
&xStaticBin[21], /* 808 */
&xStaticBin[22], /* 816 */
&xStaticBin[22], /* 824 */
&xStaticBin[22], /* 832 */
&xStaticBin[22], /* 840 */
&xStaticBin[22], /* 848 */
&xStaticBin[22], /* 856 */
&xStaticBin[22], /* 864 */
&xStaticBin[22], /* 872 */
&xStaticBin[22], /* 880 */
&xStaticBin[22], /* 888 */
&xStaticBin[22], /* 896 */
&xStaticBin[22], /* 904 */
&xStaticBin[22], /* 912 */
&xStaticBin[22], /* 920 */
&xStaticBin[22], /* 928 */
&xStaticBin[22], /* 936 */
&xStaticBin[22], /* 944 */
&xStaticBin[22], /* 952 */
&xStaticBin[22], /* 960 */
&xStaticBin[22], /* 968 */
&xStaticBin[22], /* 976 */
&xStaticBin[22], /* 984 */
&xStaticBin[22], /* 992 */
&xStaticBin[22], /* 1000 */
&xStaticBin[22] /* 1008 */};
#else
struct xBinStruct xStaticBin[/*24*/] = {
{__XMALLOC_ZERO_PAGE, NULL, NULL, 2}, /* 0 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 3}, /* 1 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 4}, /* 2 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 5}, /* 3 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 6}, /* 4 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 7}, /* 5 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 8}, /* 6 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 10}, /* 7 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 12}, /* 8 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 14}, /* 9 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 16}, /* 10 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 20}, /* 11 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 24}, /* 12 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 28}, /* 13 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 32}, /* 14 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 40}, /* 15 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 48}, /* 16 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 56}, /* 17 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 78}, /* 18 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 101}, /* 19 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 127}, /* 20 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 169}, /* 21 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 203}, /* 22 */
{__XMALLOC_ZERO_PAGE, NULL, NULL, 254} /* 23 */
};

xBin xSize2Bin[/*254*/] = {
&xStaticBin[0], /* 4 */
&xStaticBin[0], /* 8 */
&xStaticBin[1], /* 12 */
&xStaticBin[2], /* 16 */
&xStaticBin[3], /* 20 */
&xStaticBin[4], /* 24 */
&xStaticBin[5], /* 28 */
&xStaticBin[6], /* 32 */
&xStaticBin[7], /* 36 */
&xStaticBin[7], /* 40 */
&xStaticBin[8], /* 44 */
&xStaticBin[8], /* 48 */
&xStaticBin[9], /* 52 */
&xStaticBin[9], /* 56 */
&xStaticBin[10], /* 60 */
&xStaticBin[10], /* 64 */
&xStaticBin[11], /* 68 */
&xStaticBin[11], /* 72 */
&xStaticBin[11], /* 76 */
&xStaticBin[11], /* 80 */
&xStaticBin[12], /* 84 */
&xStaticBin[12], /* 88 */
&xStaticBin[12], /* 92 */
&xStaticBin[12], /* 96 */
&xStaticBin[13], /* 100 */
&xStaticBin[13], /* 104 */
&xStaticBin[13], /* 108 */
&xStaticBin[13], /* 112 */
&xStaticBin[14], /* 116 */
&xStaticBin[14], /* 120 */
&xStaticBin[14], /* 124 */
&xStaticBin[14], /* 128 */
&xStaticBin[15], /* 132 */
&xStaticBin[15], /* 136 */
&xStaticBin[15], /* 140 */
&xStaticBin[15], /* 144 */
&xStaticBin[15], /* 148 */
&xStaticBin[15], /* 152 */
&xStaticBin[15], /* 156 */
&xStaticBin[15], /* 160 */
&xStaticBin[16], /* 164 */
&xStaticBin[16], /* 168 */
&xStaticBin[16], /* 172 */
&xStaticBin[16], /* 176 */
&xStaticBin[16], /* 180 */
&xStaticBin[16], /* 184 */
&xStaticBin[16], /* 188 */
&xStaticBin[16], /* 192 */
&xStaticBin[17], /* 196 */
&xStaticBin[17], /* 200 */
&xStaticBin[17], /* 204 */
&xStaticBin[17], /* 208 */
&xStaticBin[17], /* 212 */
&xStaticBin[17], /* 216 */
&xStaticBin[17], /* 220 */
&xStaticBin[17], /* 224 */
&xStaticBin[18], /* 228 */
&xStaticBin[18], /* 232 */
&xStaticBin[18], /* 236 */
&xStaticBin[18], /* 240 */
&xStaticBin[18], /* 244 */
&xStaticBin[18], /* 248 */
&xStaticBin[18], /* 252 */
&xStaticBin[18], /* 256 */
&xStaticBin[18], /* 260 */
&xStaticBin[18], /* 264 */
&xStaticBin[18], /* 268 */
&xStaticBin[18], /* 272 */
&xStaticBin[18], /* 276 */
&xStaticBin[18], /* 280 */
&xStaticBin[18], /* 284 */
&xStaticBin[18], /* 288 */
&xStaticBin[18], /* 292 */
&xStaticBin[18], /* 296 */
&xStaticBin[18], /* 300 */
&xStaticBin[18], /* 304 */
&xStaticBin[18], /* 308 */
&xStaticBin[18], /* 312 */
&xStaticBin[19], /* 316 */
&xStaticBin[19], /* 320 */
&xStaticBin[19], /* 324 */
&xStaticBin[19], /* 328 */
&xStaticBin[19], /* 332 */
&xStaticBin[19], /* 336 */
&xStaticBin[19], /* 340 */
&xStaticBin[19], /* 344 */
&xStaticBin[19], /* 348 */
&xStaticBin[19], /* 352 */
&xStaticBin[19], /* 356 */
&xStaticBin[19], /* 360 */
&xStaticBin[19], /* 364 */
&xStaticBin[19], /* 368 */
&xStaticBin[19], /* 372 */
&xStaticBin[19], /* 376 */
&xStaticBin[19], /* 380 */
&xStaticBin[19], /* 384 */
&xStaticBin[19], /* 388 */
&xStaticBin[19], /* 392 */
&xStaticBin[19], /* 396 */
&xStaticBin[19], /* 400 */
&xStaticBin[19], /* 404 */
&xStaticBin[20], /* 408 */
&xStaticBin[20], /* 412 */
&xStaticBin[20], /* 416 */
&xStaticBin[20], /* 420 */
&xStaticBin[20], /* 424 */
&xStaticBin[20], /* 428 */
&xStaticBin[20], /* 432 */
&xStaticBin[20], /* 436 */
&xStaticBin[20], /* 440 */
&xStaticBin[20], /* 444 */
&xStaticBin[20], /* 448 */
&xStaticBin[20], /* 452 */
&xStaticBin[20], /* 456 */
&xStaticBin[20], /* 460 */
&xStaticBin[20], /* 464 */
&xStaticBin[20], /* 468 */
&xStaticBin[20], /* 472 */
&xStaticBin[20], /* 476 */
&xStaticBin[20], /* 480 */
&xStaticBin[20], /* 484 */
&xStaticBin[20], /* 488 */
&xStaticBin[20], /* 492 */
&xStaticBin[20], /* 496 */
&xStaticBin[20], /* 500 */
&xStaticBin[20], /* 504 */
&xStaticBin[20], /* 508 */
&xStaticBin[21], /* 512 */
&xStaticBin[21], /* 516 */
&xStaticBin[21], /* 520 */
&xStaticBin[21], /* 524 */
&xStaticBin[21], /* 528 */
&xStaticBin[21], /* 532 */
&xStaticBin[21], /* 536 */
&xStaticBin[21], /* 540 */
&xStaticBin[21], /* 544 */
&xStaticBin[21], /* 548 */
&xStaticBin[21], /* 552 */
&xStaticBin[21], /* 556 */
&xStaticBin[21], /* 560 */
&xStaticBin[21], /* 564 */
&xStaticBin[21], /* 568 */
&xStaticBin[21], /* 572 */
&xStaticBin[21], /* 576 */
&xStaticBin[21], /* 580 */
&xStaticBin[21], /* 584 */
&xStaticBin[21], /* 588 */
&xStaticBin[21], /* 592 */
&xStaticBin[21], /* 596 */
&xStaticBin[21], /* 600 */
&xStaticBin[21], /* 604 */
&xStaticBin[21], /* 608 */
&xStaticBin[21], /* 612 */
&xStaticBin[21], /* 616 */
&xStaticBin[21], /* 620 */
&xStaticBin[21], /* 624 */
&xStaticBin[21], /* 628 */
&xStaticBin[21], /* 632 */
&xStaticBin[21], /* 636 */
&xStaticBin[21], /* 640 */
&xStaticBin[21], /* 644 */
&xStaticBin[21], /* 648 */
&xStaticBin[21], /* 652 */
&xStaticBin[21], /* 656 */
&xStaticBin[21], /* 660 */
&xStaticBin[21], /* 664 */
&xStaticBin[21], /* 668 */
&xStaticBin[21], /* 672 */
&xStaticBin[21], /* 676 */
&xStaticBin[22], /* 680 */
&xStaticBin[22], /* 684 */
&xStaticBin[22], /* 688 */
&xStaticBin[22], /* 692 */
&xStaticBin[22], /* 696 */
&xStaticBin[22], /* 700 */
&xStaticBin[22], /* 704 */
&xStaticBin[22], /* 708 */
&xStaticBin[22], /* 712 */
&xStaticBin[22], /* 716 */
&xStaticBin[22], /* 720 */
&xStaticBin[22], /* 724 */
&xStaticBin[22], /* 728 */
&xStaticBin[22], /* 732 */
&xStaticBin[22], /* 736 */
&xStaticBin[22], /* 740 */
&xStaticBin[22], /* 744 */
&xStaticBin[22], /* 748 */
&xStaticBin[22], /* 752 */
&xStaticBin[22], /* 756 */
&xStaticBin[22], /* 760 */
&xStaticBin[22], /* 764 */
&xStaticBin[22], /* 768 */
&xStaticBin[22], /* 772 */
&xStaticBin[22], /* 776 */
&xStaticBin[22], /* 780 */
&xStaticBin[22], /* 784 */
&xStaticBin[22], /* 788 */
&xStaticBin[22], /* 792 */
&xStaticBin[22], /* 796 */
&xStaticBin[22], /* 800 */
&xStaticBin[22], /* 804 */
&xStaticBin[22], /* 808 */
&xStaticBin[22], /* 812 */
&xStaticBin[23], /* 816 */
&xStaticBin[23], /* 820 */
&xStaticBin[23], /* 824 */
&xStaticBin[23], /* 828 */
&xStaticBin[23], /* 832 */
&xStaticBin[23], /* 836 */
&xStaticBin[23], /* 840 */
&xStaticBin[23], /* 844 */
&xStaticBin[23], /* 848 */
&xStaticBin[23], /* 852 */
&xStaticBin[23], /* 856 */
&xStaticBin[23], /* 860 */
&xStaticBin[23], /* 864 */
&xStaticBin[23], /* 868 */
&xStaticBin[23], /* 872 */
&xStaticBin[23], /* 876 */
&xStaticBin[23], /* 880 */
&xStaticBin[23], /* 884 */
&xStaticBin[23], /* 888 */
&xStaticBin[23], /* 892 */
&xStaticBin[23], /* 896 */
&xStaticBin[23], /* 900 */
&xStaticBin[23], /* 904 */
&xStaticBin[23], /* 908 */
&xStaticBin[23], /* 912 */
&xStaticBin[23], /* 916 */
&xStaticBin[23], /* 920 */
&xStaticBin[23], /* 924 */
&xStaticBin[23], /* 928 */
&xStaticBin[23], /* 932 */
&xStaticBin[23], /* 936 */
&xStaticBin[23], /* 940 */
&xStaticBin[23], /* 944 */
&xStaticBin[23], /* 948 */
&xStaticBin[23], /* 952 */
&xStaticBin[23], /* 956 */
&xStaticBin[23], /* 960 */
&xStaticBin[23], /* 964 */
&xStaticBin[23], /* 968 */
&xStaticBin[23], /* 972 */
&xStaticBin[23], /* 976 */
&xStaticBin[23], /* 980 */
&xStaticBin[23], /* 984 */
&xStaticBin[23], /* 988 */
&xStaticBin[23], /* 992 */
&xStaticBin[23], /* 996 */
&xStaticBin[23], /* 1000 */
&xStaticBin[23], /* 1004 */
&xStaticBin[23], /* 1008 */
&xStaticBin[23], /* 1012 */
&xStaticBin[23] /* 1016 */};
#endif

#define xSmallSize2Bin(size)                              \
  xSize2Bin[((size)-1) >> __XMALLOC_LOG_SIZEOF_ALIGNMENT]

#define __XMALLOC_LARGE_BIN ((xBin) 1)

/************************************************
 * SPEC-BIN STUFF
 ***********************************************/
xBin xGetSpecBin(size_t size) {
  xBin newSpecBin;
  long numberBlocks;
  long sizeInWords;

  size  = xAlignSize(size);

  if (size > __XMALLOC_SIZEOF_PAGE) {
    // large memory chunks
    // reserve memory for page header
    numberBlocks  = - (long)
      ((size + (__XMALLOC_SIZEOF_SYSTEM_PAGE - __XMALLOC_SIZEOF_PAGE)) +
       __XMALLOC_SIZEOF_SYSTEM_PAGE-1) / __XMALLOC_SIZEOF_SYSTEM_PAGE;

    sizeInWords   = ((-numberBlocks * __XMALLOC_SIZEOF_SYSTEM_PAGE) -
      (__XMALLOC_SIZEOF_SYSTEM_PAGE - __XMALLOC_SIZEOF_PAGE)) /
      __XMALLOC_SIZEOF_LONG;

    newSpecBin    = __XMALLOC_LARGE_BIN;
  } else {
    // small memory chunks
    // reserve memory for page header
    numberBlocks  = __XMALLOC_SIZEOF_PAGE / size;

    sizeInWords   = (__XMALLOC_SIZEOF_PAGE % size) / numberBlocks;
    sizeInWords   = ((size + sizeInWords) &
      ~(__XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE));

    assert(sizeInWords >= size);
    assert(numberBlocks * sizeInWords <= __XMALLOC_SIZEOF_PAGE);

    sizeInWords = sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG;

    if (size > __XMALLOC_MAX_SMALL_BLOCK_SIZE)
      newSpecBin  = __XMALLOC_LARGE_BIN;
    else
      newSpecBin  = xSmallSize2Bin(size);
  }

  if (__XMALLOC_LARGE_BIN == newSpecBin ||
      numberBlocks > newSpecBin->numberBlocks) {
    xSpecBin specBin  = xFindInSortedList(newSpecBin, numberBlocks);

    // we get a specBin from the list search in above
    if (NULL != specBin) {
      (specBin->ref)++;
      assert(NULL != specBin->bin &&
          specBin->bin->numberBlocks  ==  specBin->numberBlocks &&
          specBin->bin->sizeInWords   ==  sizeInWords);
      return specBin->bin;
    }
    // we do not get a specBin from the above list, thus we have to allocate and
    // register it by hand
    specBin               = (xSpecBin) xMalloc(sizeof(xSpecBinType));
    specBin->ref          = 1;
    specBin->next         = NULL;
    specBin->numberBlocks = numberBlocks;
    specBin->bin          = (xBin) xMalloc(sizeof(xBinType));
    specBin->bin->currentPage   = __XMALLOC_ZERO_PAGE;
    specBin->bin->lastPage      = NULL;
    specBin->bin->sizeInWords   = sizeInWords;
    specBin->bin->numberBlocks  = numberBlocks;
    // OMALLOC FUNCTIONALITY MISSING
    // until now we have no concept of a sticky bin in xmalloc
    // do we really need this?
    //specBin->bin->sticky        = 0;
  }
  /*
  if (NULL == bin) {
    bin = (xBin)malloc(sizeof(*bin));
    memset(bin, 0, sizeof(*bin));
    bin->sizeInWords  = (size + __XMALLOC_SIZEOF_LONG - 1) / __XMALLOC_SIZEOF_LONG;
    bin->currentPage  = xPageForMalloc;
  }
  */
  return bin;
}

//void xUnGetSpecBin(xBin* bin) {
//  if (*bin  ==  NULL) {
//    printf("xUnGetSpecBin(NULL\n");
//  } else {
//    if ((*bin)->currentPage == xPageForMalloc) {
//      /* TODO */
//      free(*bin);
//    }
//  }
//  *bin  = NULL;
//}

/************************************************
 * PAGE-BIN-CONNECTIONS
 ***********************************************/
//xPage xGetPageFromBin(xBin bin) {
//  if (bin->currentPage != NULL) {
//    if (bin->currentPage->free != NULL)
//      return bin->currentPage;
//    else {
//      xPage page  = bin->lastPage;
//      while ((page != NULL) && (page->free == NULL))
//        page  = page->prev;
//      if ((page != NULL) && (page->free != NULL)) {
//        bin->currentPage  = page;
//        return page;
//      }
//    }
//  }
//  /* now b->current==NULL or all pages are full */
//  //extern void *xGetNewPage();
//  xPage page  = (xPage)xGetNewPage();
//  xMakePage(page, bin->sizeInWords * __XMALLOC_SIZEOF_LONG);
//  page->prev  = bin->lastPage;
//  page->next  = NULL;
//  if (bin->lastPage !=  NULL)
//    bin->lastPage->next = page;
//  bin->lastPage         = page;
//  bin->currentPage      = page;
//  page->bin             = bin;
//  return page;
//  //return b->currentPage;
//}

void xInsertPageToBin(xBin bin, xPage page) {
  if (__XMALLOC_ZERO_PAGE == bin->currentPage) {
    page->prev        = NULL;
    page->next        = NULL;
    bin->currentPage  = page;
    bin->lastPage     = page;
  } else {
    if (bin->currentPage == bin->lastPage) {
      bin->lastPage = page;
    } else {
      bin->currentPage->next->prev  = page;
    }
    page->next              = bin->currentPage->next;
    bin->currentPage->next  = page;
    page->prev              = bin->currentPage;
  }
}

/************************************************
 * ALLOCATING PAGES IN BINS
 ***********************************************/
void xAllocFromFullPage(void *addr, xBin bin) {
  if (__XMALLOC_ZERO_PAGE != bin->currentPage) {
    bin->currentPage->numberUsedBlocks  = 0;
  }
  xPage newPage     = xAllocNewPageForBin(bin);
  xInsertPageToBin(bin, newPage);
  bin->currentPage  = newPage;
  xAllocFromNonEmptyPage(addr, newPage);
}

/************************************************
 * ALLOCATING PAGES FOR BINS
 ***********************************************/
xPage xAllocNewPageForBin(xBin bin) {
  xPage newPage;
  void *tmp;
  int i = 1;

  // block size < page size
  if (bin->numberBlocks > 0)
    newPage = xAllocSmallBlockPageForBin(); // TOODOO
  // block size > page size
  else
    newPage = xAllocBigBlockPagesForBin(-bin->numberBlocks); // TOODOO

  newPage->numberUsedBlocks = -1;
  newPage->current  = (void*) (((char*) newPage) +
                        __XMALLOC_SIZEOF_PAGE_HEADER);
  tmp               = newPage->current;
  while (i < bin->numberBlocks) {
    tmp = __XMALLOC_NEXT(tmp)  = ((void**) tmp) + bin->sizeInWords;
    i++;
  }
  __XMALLOC_NEXT(tmp) = NULL;
  return newPage;
}

xPage xAllocSmallBlockPageForBin() {
  xPage newPage;

  if (NULL == xBaseRegion)
    xBaseRegion  = xAllocNewRegion(1); // TOODOO

  while (1) {
    // current page in region can be used
    if (NULL != xBaseRegion->current) {
      newPage             = xBaseRegion->current;
      xBaseRegion->current = __XMALLOC_NEXT(newPage);
      goto Found;
    }
    // there exist pages in this region we can use
    if (xBaseRegion->numberInitPages > 0) {
      newPage = (xPage) xBaseRegion->initAddr;
      xBaseRegion->numberInitPages--;
      if (xBaseRegion->numberInitPages > 0)
        xBaseRegion->initAddr  +=  __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        xBaseRegion->initAddr  =   NULL;
      goto Found;
    }
    // there exists already a next region we can allocate from
    if (NULL != xBaseRegion->next) {
      xBaseRegion  = xBaseRegion->next;
    } else {
      xRegion region  = xAllocNewRegion(1);
      region->prev    = xBaseRegion;
      xBaseRegion      = xBaseRegion->next  = region;
    }
  }

  Found:
  newPage->region = xBaseRegion;
  xBaseRegion->numberUsedPages++;
  return newPage;
}

xPage xAllocBigBlockPagesForBin(int numberNeeded) {
  register xPage page;
  xRegion region;

  // take care that there is at least 1 region active, if
  // not then we allocate a big enough region for the memory chunk
  if (NULL == xBaseRegion)
    xBaseRegion  = xAllocNewRegion(numberNeeded);

  region  = xBaseRegion;
  while (1) {
    // memory chunk fits in this region
    if (region->numberInitPages >= numberNeeded) {
      page                    =   (xPage) region->initAddr;
      region->numberInitPages -=  numberNeeded;
      if (region->numberInitPages > 0)
        region->initAddr  +=  numberNeeded * __XMALLOC_SIZEOF_SYSTEM_PAGE;
      else
        region->initAddr  =   NULL;
      goto Found;
    }
    // check if there is a consecutive chunk of numberNeeded pages in region we
    // can get
    page  = xGetConsecutivePagesFromRegion(region, numberNeeded);
    if (NULL != page)
      goto Found;
    // there already exists a next region we can allocate from
    if (NULL != region->next) {
      region  = region->next;
    } else {
      xRegion newRegion = xAllocNewRegion(numberNeeded);
      region->next      = newRegion;
      newRegion->prev   = region;
      region            = newRegion;
    }
  }

  Found:
  page->region            =   region;
  region->numberUsedPages +=  numberNeeded;

  if (xBaseRegion != region) {
    xTakeOutRegion(region);
    xInsertRegionBefore(region, xBaseRegion);
  }
  return page;
}
