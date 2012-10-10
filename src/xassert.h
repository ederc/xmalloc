/**
 * \file   xassert.h
 * \Author Christian Eder ( ederc\mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  special assert handling for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_ASSERT_H
#define XMALLOC_ASSERT_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include "xmalloc-config.h"

/**
 * \fn static inline int xReportError(const char* message, ...)
 *
 * \brief Prints the error message if an assert violation happens.
 *
 * \param message \c const \c char \c * the error message
 *
 * \param possibly the file and the line in which the error happened
 *
 * \return \c integer error code
 *
 */
static inline int xReportError(const char *message, ...) {
  va_list ap;
  va_start(ap, message);
  fprintf(stderr, "\n--- ERROR -> ");
  vfprintf(stderr, message, ap);
  
  return 0;
}

#ifndef NDEBUG

/**
 * \brief xmalloc-specific assert
 */
#define xAssert(expression, file, line)                                       \
do {                                                                          \
  if (!(expression)) {                                                        \
    xReportError("Assert violation at %s ( line %d ):\n             %s\n\n",  \
        file, line, #expression);                                             \
    exit(EXIT_FAILURE);                                                       \
  }                                                                           \
} while(0)

// we let it just fall back to assert
#else

/**
 * \brief xmalloc-specific assert
 */
#define xAssert(expression, file, line) assert(expression)

#endif
#endif
