/**
 * \file   globals.h
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  Global variables needed for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_GLOBALS_H
#define XMALLOC_GLOBALS_H

#define X_XMALLOC

extern xPage xPageForMalloc;
extern xSpecBin xBaseSpecBin;
extern xRegion xBaseRegion;
/* zero page for initializing static bins */
extern struct xPageStruct __XMALLOC_ZERO_PAGE[];

extern unsigned long xMinPageIndex;
extern unsigned long xMaxPageIndex;
extern unsigned long *xPageShifts;

extern struct xBinStruct xStaticBin[];

extern xBin xStickyBins;

//extern size_t xCacheLineSize;

/********************************************
 * MULTI-THREADED STUFF
 *******************************************/
extern BOOLEAN xIsThreaded;


/********************************************
 * STATISTICS / XINFO STUFF
 *******************************************/
extern xInfo info;
extern unsigned long xSbrkInit;

void xPrintInfo();
void xUpdateInfo();


#endif
