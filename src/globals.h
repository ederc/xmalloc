/**
 * @file   xGlobals.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Global variables needed for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_GLOBALS_H
#define X_GLOBALS_H

#define X_XMALLOC

extern xPage xPageForMalloc;
extern xRegion baseRegion;
/* zero page for initializing static bins */
extern struct xPageStruct xZeroPage[];

extern unsigned long xMinPageIndex;
extern unsigned long xMaxPageIndex;
extern unsigned long *xPageShifts;

extern struct xBinStruct xStaticBin[];
#endif
