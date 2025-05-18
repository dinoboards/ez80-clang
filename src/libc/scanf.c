#include <format.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Reads formatted input from the standard input (stdin).
 *
 * The scanf function reads data from the standard input stream (stdin) and stores them according to the format string.
 *
 * @param format The format string.
 * @param ... Additional arguments specifying the data to read.
 *
 * @return The number of input items successfully matched and assigned, or EOF on error or end-of-file.
 */
int scanf(const char *format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = _u_scan(stdin, NULL, format, ap);
  va_end(ap);

  return ret;
}
