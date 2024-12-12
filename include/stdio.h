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

/**
 * @brief Writes a string to a file stream.
 *
 * The fputs function writes the string `str` to the file stream `stream`.
 *
 * @param str The null-terminated string to be written.
 * @param stream The file stream to write to.
 *
 * @return A non-negative value on success, EOF on error.
 */
int fputs(const char *__restrict str, FILE *__restrict stream);

/**
 * @brief Reads data from a file stream.
 *
 * The fread function reads `count` elements of data, each `size` bytes long,
 * from the file stream `stream` into the array pointed to by `ptr`.
 *
 * @param ptr Pointer to the array where the read data will be stored.
 * @param size Size in bytes of each element to be read.
 * @param count Number of elements to be read.
 * @param stream The file stream to read from.
 *
 * @return The number of elements successfully read, which may be less than
 * `count` if an error or end-of-file occurs.
 */
size_t fread(void *ptr, size_t size, size_t count, FILE *__restrict stream);

/**
 * @brief Writes data to a file stream.
 *
 * The fwrite function writes `count` elements of data, each `size` bytes long,
 * from the array pointed to by `ptr` to the file stream `stream`.
 *
 * @param ptr Pointer to the array containing the data to be written.
 * @param size Size in bytes of each element to be written.
 * @param count Number of elements to be written.
 * @param stream The file stream to write to.
 *
 * @return The number of elements successfully written, which may be less than
 * `count` if an error occurs.
 */
size_t fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream);

/**
 * @brief Returns the current file position.
 *
 * The ftell function obtains the current value of the file position indicator
 * for the file stream `stream`.
 *
 * @param stream The file stream to be queried.
 *
 * @return The current file position indicator on success, -1L on error.
 */
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

/**
 * @brief Gets a character from a file stream.
 *
 * The fgetc function reads the next character from the file stream `stream`
 * and returns it as an unsigned char cast to an int, or EOF on end-of-file or error.
 *
 * @param stream The file stream to read from.
 *
 * @return The character read as an unsigned char cast to an int, or EOF on end-of-file or error.
 */
int fgetc(FILE *stream);

/**
 * @brief Gets a character from a file stream.
 *
 * The getc function reads the next character from the file stream `stream`
 * and returns it as an unsigned char cast to an int, or EOF on end-of-file or error.
 * This macro is equivalent to the fgetc function.
 *
 * @param stream The file stream to read from.
 *
 * @return The character read as an unsigned char cast to an int, or EOF on end-of-file or error.
 */
#define getc(...) fgetc(__VA_ARGS__)

/**
 * @brief Writes a character to a file stream.
 *
 * The fputc function writes the character `c` (cast to an unsigned char) to the file stream `stream`.
 *
 * @param c The character to be written.
 * @param stream The file stream to write to.
 *
 * @return The character written as an unsigned char cast to an int, or EOF on error.
 */
int fputc(int c, FILE *stream);

/**
 * @brief Writes a character to a file stream.
 *
 * The putc function writes the character `c` (cast to an unsigned char) to the file stream `stream`.
 * This macro is equivalent to the fputc function.
 *
 * @param c The character to be written.
 * @param stream The file stream to write to.
 *
 * @return The character written as an unsigned char cast to an int, or EOF on error.
 */
#define putc(...) fputc(__VA_ARGS__)

/**
 * @brief Gets a string from a file stream.
 *
 * The fgets function reads up to `num - 1` characters from the file stream `stream` and stores them into the string `str`.
 * The string is null-terminated.
 *
 * @param str The array where the read string will be stored.
 * @param num The maximum number of characters to be read (including the null terminator).
 * @param stream The file stream to read from.
 *
 * @return `str` on success, NULL on error or when end-of-file occurs while no characters have been read.
 */
char *fgets(char *__restrict str, int num, FILE *__restrict stream);

/**
 * @brief Removes a file.
 *
 * The remove function deletes the file specified by `filename`.
 *
 * @param filename The name of the file to be deleted.
 *
 * @return 0 on success, non-zero on error.
 */
int remove(const char *filename);

/**
 * @brief Sets the file position to the beginning of the file.
 *
 * The rewind function sets the file position indicator for the file stream `stream` to the beginning of the file.
 * It also clears the error and end-of-file indicators for the stream.
 *
 * @param stream The file stream to be rewound.
 */
void rewind(FILE *stream);

/**
 * @brief Gets a character from the standard input (stdin).
 *
 * The getchar function reads the next character from the standard input stream (stdin)
 * and returns it as an unsigned char cast to an int, or EOF on end-of-file or error.
 *
 * @return The character read as an unsigned char cast to an int, or EOF on end-of-file or error.
 */
int getchar(void);

/**
 * @brief Writes a character to the standard output (stdout).
 *
 * The putchar function writes the character specified by the argument character
 * to the standard output stream (stdout) and returns the character written as an unsigned char cast to an int,
 * or EOF on error.
 *
 * @param character The character to be written.
 *
 * @return The character written as an unsigned char cast to an int, or EOF on error.
 */
int putchar(int character);

/**
 * @brief Writes a string to the standard output (stdout).
 *
 * The puts function writes the string pointed to by str to the standard output stream (stdout)
 * and appends a newline character. It returns a non-negative number on success, or EOF on error.
 *
 * @param str The string to be written.
 *
 * @return A non-negative number on success, or EOF on error.
 */
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

/**
 * @brief Prints formatted output to the standard output (stdout) using a variable argument list.
 *
 * The vprintf function formats and prints a series of characters and values to the standard output stream (stdout)
 * using the format string and the variable argument list provided.
 *
 * @param format The format string.
 * @param va The variable argument list.
 *
 * @return The number of characters printed, or a negative value on error.
 */
int vprintf(const char *__restrict format, va_list va) __attribute__((format(__printf__, 1, 0)));

/**
 * @brief Prints formatted output to a string using a variable argument list.
 *
 * The vsprintf function formats and stores a series of characters and values in the buffer provided
 * using the format string and the variable argument list.
 *
 * @param buffer The buffer to store the formatted string.
 * @param format The format string.
 * @param va The variable argument list.
 *
 * @return The number of characters written, excluding the null terminator, or a negative value on error.
 */
int vsprintf(char *__restrict buffer, const char *__restrict format, va_list va) __attribute__((format(__printf__, 1, 0)));

/**
 * @brief Prints formatted output to a string with a limit on the number of characters.
 *
 * The snprintf function formats and stores a series of characters and values in the buffer provided,
 * with a limit on the number of characters, using the format string and additional arguments.
 *
 * @param buffer The buffer to store the formatted string.
 * @param count The maximum number of characters to write, including the null terminator.
 * @param format The format string.
 * @param ... Additional arguments specifying the data to print.
 *
 * @return The number of characters that would have been written if count was sufficiently large, not counting the null terminator.
 */
int snprintf(char *buffer, size_t count, const char *__restrict format, ...) __attribute__((format(__printf__, 3, 4)));

/**
 * @brief Prints formatted output to a string with a limit on the number of characters using a variable argument list.
 *
 * The vsnprintf function formats and stores a series of characters and values in the buffer provided,
 * with a limit on the number of characters, using the format string and the variable argument list.
 *
 * @param buffer The buffer to store the formatted string.
 * @param count The maximum number of characters to write, including the null terminator.
 * @param format The format string.
 * @param va The variable argument list.
 *
 * @return The number of characters that would have been written if count was sufficiently large, not counting the null terminator.
 */
int vsnprintf(char *buffer, size_t count, const char *__restrict format, va_list va) __attribute__((format(__printf__, 3, 0)));

/**
 * @brief Prints formatted output to a string.
 *
 * The sprintf function formats and stores a series of characters and values in the buffer provided
 * using the format string and additional arguments.
 *
 * @param buffer The buffer to store the formatted string.
 * @param format The format string.
 * @param ... Additional arguments specifying the data to print.
 *
 * @return The number of characters written, excluding the null terminator.
 */
int sprintf(char *__restrict buffer, const char *__restrict format, ...) __attribute__((format(__printf__, 2, 3)));

/**
 * @brief Prints formatted output to a file stream.
 *
 * The fprintf function formats and prints a series of characters and values to the specified file stream
 * using the format string and additional arguments.
 *
 * @param stream The file stream to write to.
 * @param format The format string.
 * @param ... Additional arguments specifying the data to print.
 *
 * @return The number of characters printed, or a negative value on error.
 */
int fprintf(FILE *stream, const char *__restrict format, ...) __attribute__((format(__printf__, 2, 3)));

/**
 * @brief Prints formatted output to a file stream using a variable argument list.
 *
 * The vfprintf function formats and prints a series of characters and values to the specified file stream
 * using the format string and the variable argument list provided.
 *
 * @param stream The file stream to write to.
 * @param format The format string.
 * @param va The variable argument list.
 *
 * @return The number of characters printed, or a negative value on error.
 */
int vfprintf(FILE *stream, const char *__restrict format, va_list va) __attribute__((format(__printf__, 2, 0)));

typedef size_t rsize_t;

/**
 * @brief Reads a line from the standard input (stdin) into a buffer with bounds checking.
 *
 * The gets_s function reads a line from the standard input stream (stdin) into the buffer pointed to by str,
 * up to a maximum of n-1 characters, and null-terminates the string. It ensures that the buffer is not overflowed.
 *
 * @param str The buffer to store the input string.
 * @param n The maximum number of characters to read, including the null terminator.
 *
 * @return A pointer to the buffer containing the input string, or NULL on error.
 */
char *gets_s(char *__restrict str, rsize_t n);

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
int scanf(const char *format, ...);

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

/**
 * @brief Reads formatted input from a file stream.
 *
 * The fscanf function reads data from the specified file stream and stores them according to the format string.
 *
 * @param fp The file stream to read from.
 * @param fmt The format string.
 * @param ... Additional arguments specifying the data to read.
 *
 * @return The number of input items successfully matched and assigned, or EOF on error or end-of-file.
 */
int fscanf(FILE *fp, const char *fmt, ...);

/**
 * @brief Reopens a file stream with a different file or mode.
 *
 * The freopen function opens the file specified by filename and associates it with the specified file stream,
 * which is then reopened with the specified mode.
 *
 * @param filename The name of the file to open.
 * @param mode The mode to open the file with.
 * @param stream The file stream to associate with the file.
 *
 * @return A pointer to the reopened file stream, or NULL on error.
 */
FILE *freopen(const char *__restrict filename, const char *__restrict mode, FILE *stream);

/**
 * @brief Pushes a character back onto a file stream.
 *
 * The ungetc function pushes the character specified by c back onto the specified file stream,
 * making it available for subsequent reads.
 *
 * @param c The character to push back.
 * @param stream The file stream to push the character onto.
 *
 * @return The character pushed back, or EOF on error.
 */
int ungetc(int c, FILE *stream);

/**
 * @brief Prints a descriptive error message to the standard error stream (stderr).
 *
 * The perror function prints a descriptive error message to the standard error stream (stderr),
 * based on the string provided and the current value of the global variable errno.
 *
 * @param s The custom message to print before the error description.
 */
void perror(const char *s);

/**
 * @brief Gets the file descriptor associated with a file stream.
 *
 * The fileno function returns the file descriptor associated with the specified file stream.
 *
 * @param stream The file stream to get the file descriptor for.
 *
 * @return The file descriptor associated with the file stream.
 */
static inline int fileno(const FILE *stream) { return (int)stream; }

__END_DECLS

#endif /* _STDIO_H */
