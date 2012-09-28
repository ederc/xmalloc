/**
 * @file   xassert.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  special assert handling for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <assert.h>

#ifndef XMALLOC_ASSERT_H
#define XMALLOC_ASSERT_H

/**
 * @fn static inline int xReportError(const char* message, ...)
 *
 * @brief Prints the error message if an assert violation happens.
 *
 * @param message @var const @var char @var * the error message
 *
 * @param possibly the file and the line in which the error happened
 *
 * @return @var integer error code
 *
 */
static inline int xReportError(const char *message, ...) {
  va_list ap;
  va_start(ap, message);
  fprintf(stderr, "\n--- ERROR ---\n");
  vfprintf(stderr, message, ap);
}

#ifndef NDEBUG
/**
 * @fn static inline void xAssert(int expression)
 *
 * @brief xmallocs assert function.
 *
 * @param expression @var integer expression to be checked
 *
 */
static inline void xAssert(int expression) {
  if (!expression)
    xReportError("Assert violation at %s : %d condition %s", __FILE__, __LINE__, (char *)expression);
}
// we let it just fall back to assert
#else
/**
 * @fn static inline void xAssert(int expression)
 *
 * @brief xmallocs assert function.
 *
 * @param expression @var integer expression to be checked
 *
 */
static inline void xAssert(int expression) {
  assert(int expression);
}
#endif
#endif
