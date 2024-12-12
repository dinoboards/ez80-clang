#ifndef _STDIO_H
#define _STDIO_H

#include <cdefs.h>
#include <stdarg.h>

#ifdef HAS_CUSTOM_FILE
#include CUSTOM_FILE_FILE
#else
typedef void *FILE;
#define FOPEN_MAX 5
#define stdin     ((FILE *)1)
#define stdout    ((FILE *)2)
#define stderr    ((FILE *)2)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif
#ifndef SEEK_SET
#define SEEK_SET 0
#endif

__BEGIN_DECLS

/**
 * @brief Opens a file.
 *
 * @details The `fopen` function opens the file whose name is the string pointed to by `filename` and associates a stream with it.
 *
 * The `mode` argument is a string that indicates the type of access requested for the file. The allowed modes are:
 * - `"r"` : Open text file for reading. The stream is positioned at the beginning of the file.
 * - `"w"` : Truncate to zero length or create text file for writing. The stream is positioned at the beginning of the file.
 * - `"a"` : Open for writing. The file is created if it does not exist. The stream is positioned at the end of the file.
 * - `"r+"`: Open for reading and writing. The stream is positioned at the beginning of the file.
 * - `"w+"`: Truncate to zero length or create text file for reading and writing. The stream is positioned at the beginning of the
 * file.
 * - `"a+"`: Open for reading and writing. The file is created if it does not exist. The stream is positioned at the end of the
 * file.
 * - `"rb"`: Open binary file for reading. The stream is positioned at the beginning of the file.
 * - `"wb"`: Truncate to zero length or create binary file for writing. The stream is positioned at the beginning of the file.
 * - `"ab"`: Open binary file for writing. The file is created if it does not exist. The stream is positioned at the end of the
 * file.
 * - `"r+b"` or `"rb+"`: Open binary file for reading and writing. The stream is positioned at the beginning of the file.
 * - `"w+b"` or `"wb+"`: Truncate to zero length or create binary file for reading and writing. The stream is positioned at the
 * beginning of the file.
 * - `"a+b"` or `"ab+"`: Open binary file for reading and writing. The file is created if it does not exist. The stream is
 * positioned at the end of the file.
 *
 * The `fopen` function returns a pointer to a `FILE` object that can be used to identify the stream in subsequent operations. If
 * the file cannot be opened, a `NULL` pointer is returned.
 *
 * @param[in] filename The name of the file to be opened.
 * @param[in] mode The mode in which to open the file.
 *
 * @return A pointer to a `FILE` object on success, or `NULL` on failure.
 */
FILE *fopen(const char *__restrict filename, const char *__restrict mode);

/**
 * @brief Closes a file.
 *
 * The fclose function closes the file associated with the given stream and
 * disassociates it. Any buffered output is written to the file.
 *
 * @param stream The file stream to be closed.
 *
 * @return 0 on success, EOF on error.
 */
int fclose(FILE *stream);

/**
 * @brief Flushes a file stream.
 *
 * The fflush function flushes the output buffer of a stream. If the stream is
 * an output stream or update stream, the function writes any buffered data to
 * the file.
 *
 * @param stream The file stream to be flushed.
 *
 * @return 0 on success, EOF on error.
 */
int fflush(FILE *stream);

/**
 * @brief Checks for a file error.
 *
 * The ferror function tests the error indicator for the given stream.
 *
 * @param stream The file stream to be checked.
 *
 * @return Non-zero if the error indicator is set, 0 otherwise.
 */
int ferror(FILE *stream);

/**
 * @brief Checks for end-of-file.
 *
 * The feof function tests the end-of-file indicator for the given stream.
 *
 * @param stream The file stream to be checked.
 *
 * @return Non-zero if the end-of-file indicator is set, 0 otherwise.
 */
int feof(FILE *stream);

/**
 * @brief Clears error indicators.
 *
 * The clearerr function clears the end-of-file and error indicators for the
 * given stream.
 *
 * @param stream The file stream for which to clear the indicators.
 */
void clearerr(FILE *stream);

int fputs(const char *__restrict str, FILE *__restrict stream);

size_t fread(void *ptr, size_t size, size_t count, FILE *__restrict stream);

size_t fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream);

long ftell(FILE *stream) __attribute__((__warn_unused_result__));

/**
 * @brief Reposition the file offset of the stream.
 *
 * The fseek function sets the file position indicator for the stream pointed to by stream.
 * The new position, measured in bytes, is obtained by adding offset bytes to the position
 * specified by origin. If origin is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset is
 * relative to the start of the file, the current position indicator, or end-of-file, respectively.
 *
 * @param stream A pointer to a FILE object that identifies the stream.
 * @param offset The number of bytes to offset from origin.
 * @param origin The position from where offset is added. It can be SEEK_SET, SEEK_CUR, or SEEK_END.
 * @return int Returns 0 on success, or a non-zero value on error.
 */
int fseek(FILE *stream, long offset, int origin);

int fgetc(FILE *stream);
#define getc(...) fgetc(__VA_ARGS__)

int fputc(int c, FILE *stream);
#define putc(...) fputc(__VA_ARGS__)

char *fgets(char *__restrict str, int num, FILE *__restrict stream);

int remove(const char *filename);

void rewind(FILE *stream);

/* standard impls */
int getchar(void);

int putchar(int character);

int puts(const char *str);

/**
 * @brief Sends formatted output to stdout.
 *
 * The printf function sends formatted output to stdout using the format string
 * specified. The format string can contain format specifiers that are replaced
 * by the values specified in subsequent arguments.
 *
 * @param format The format string that specifies how subsequent arguments are
 * converted for output.
 * @param ... Additional arguments specifying the data to be printed according
 * to the format string.
 *
 * @return The number of characters printed (excluding the null byte used to end
 * output to strings). On failure, a negative number is returned.
 *
 */
int printf(const char *__restrict format, ...) __attribute__((format(__printf__, 1, 2)));

int vprintf(const char *__restrict format, va_list va) __attribute__((format(__printf__, 1, 0)));

int vsprintf(char *__restrict buffer, const char *__restrict format, va_list va) __attribute__((format(__printf__, 1, 0)));

int snprintf(char *buffer, size_t count, const char *__restrict format, ...) __attribute__((format(__printf__, 3, 4)));

int vsnprintf(char *buffer, size_t count, const char *__restrict format, va_list va) __attribute__((format(__printf__, 3, 0)));

int sprintf(char *__restrict buffer, const char *__restrict format, ...) __attribute__((format(__printf__, 2, 3)));

int fprintf(FILE *stream, const char *__restrict format, ...) __attribute__((format(__printf__, 2, 3)));

int vfprintf(FILE *stream, const char *__restrict format, va_list va) __attribute__((format(__printf__, 2, 0)));

typedef size_t rsize_t;

char *gets_s(char *__restrict str, rsize_t n);
int   scanf(const char *format, ...);

/**
 * @brief Reads formatted input from a string.
 *
 * The sscanf function reads data from the null-terminated string `string` and
 * stores them according to the format string `fmt` into the locations pointed
 * to by the additional arguments.
 *
 * @param string The null-terminated string to read data from.
 * @param fmt The format string that specifies how to interpret the input.
 * @param ... Pointers to variables where the converted values are stored.
 *
 * @return The number of input items successfully matched and assigned. If a
 * matching failure occurs before the first input item is assigned, the function
 * returns EOF.
 *
 * @note This function is part of the C standard library.
 */
int sscanf(const char *s, const char *format, ...);

int   fscanf(FILE *fp, const char *fmt, ...);
FILE *freopen(const char *__restrict filename, const char *__restrict mode, FILE *stream);
int   ungetc(int c, FILE *stream);

void perror(const char *s);

static inline int fileno(const FILE *stream) { return (int)stream; }

__END_DECLS

#endif /* _STDIO_H */
