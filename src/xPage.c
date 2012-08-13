/**
 * @file   xPage.c 
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline page handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <xPage.h>

/**********************************************
 * PAGE REGISTRATION
 *********************************************/
void xRegisterPages(void *startAddr, int numberPages) {
  char *endAddr = (char*) startAddr +
                    (numberPages - 1) * __XMALLOC_SIZEOF_SYSTEM_PAGE;

  unsigned long startIndex  = xGetPageIndexOfAddr(startAddr);
  unsigned long endIndex    = xGetPageIndexOfAddr(endAddr);
  unsigned long shift;

  // check indices & correct them if necessary
  if (startIndex < xMinPageIndex || endIndex > xMaxPageIndex)
    xPageIndexFault(startIndex, endIndex); // TOODOO

  shift = xGetPageShiftOfAddr(startAddr);
  if (startIndex < endIndex) {
    if (0 == shift)
      xPageShifts[startIndex - xMinPageIndex]  = ULLONG_MAX;
    else
      xPageShifts[startIndex - xMinPageIndex]  |= ~((((unsigned long) 1) << shift) - 1);
    for (shift = startIndex + 1; shift < endIndex; shift++) 
      xPageShifts[startIndex - xMinPageIndex]  = ULLONG_MAX;
    shift = xGetPageShiftOfAddr(endAddr);
    if ((__XMALLOC_BIT_SIZEOF_LONG - 1) == shift)
      xPageShifts[endIndex - xMinPageIndex]  = ULLONG_MAX;
    else
      xPageShifts[endIndex - xMinPageIndex]  |=
        ((((unsigned long) 1) << (shift + 1)) - 1);
  } else {
    endIndex  = xGetPageShiftOfAddr(endAddr);
    while (endIndex > shift) {
      xPageShifts[startIndex - xMinPageIndex] |=
        (((unsigned long) 1) << endIndex);
      endIndex--;
    }
    xPageShifts[startIndex - xMinPageIndex] |= (((unsigned long) 1) << shift);
  }
}
