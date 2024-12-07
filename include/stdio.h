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

/* weak user-defined functions */
char inchar(void);

void outchar(char character);

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

int fclose(FILE *stream);

int fflush(FILE *stream);

int ferror(FILE *stream);

int feof(FILE *stream);

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
int   sscanf(const char *s, const char *format, ...);
int   fscanf(FILE *fp, const char *fmt, ...);
FILE *freopen(const char *__restrict filename, const char *__restrict mode, FILE *stream);
int   ungetc(int c, FILE *stream);

void perror(const char *s);

static inline int fileno(const FILE *stream) { return (int)stream; }

__END_DECLS

#endif /* _STDIO_H */
