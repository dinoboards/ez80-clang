/*****************************************************************************
 * getopt.h - competent and free getopt library.
 *
 * Copyright (c)2002-2003 Mark K. Kim
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *   * Neither the original author of this software nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef GETOPT_H_
#define GETOPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/**
 * @brief Argument value for the current option.
 *
 * This variable points to the value of the current option argument, if an option requires an argument.
 */
extern char *optarg;

/**
 * @brief Index of the next element to be processed in argv.
 *
 * This variable is the index of the next element of the argv array to be processed.
 */
extern int optind;

/**
 * @brief Error indicator for getopt.
 *
 * This variable is set to 0 to suppress error messages from getopt, or non-zero to enable them.
 */
extern int opterr;

/**
 * @brief Option character that caused an error.
 *
 * This variable contains the option character that caused an error, if an unrecognized option character is encountered.
 */
extern int optopt;

/**
 * @brief Parses command-line options.
 *
 * This function parses command-line arguments. It is used to parse options in the argument list argv.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param optstring A string containing the legitimate option characters.
 * @return The next option character from argv that matches a character in optstring, or -1 if there are no more options.
 */
int getopt(int argc, char *argv[], const char *optstring);

/**
 * @brief Closes a file descriptor.
 *
 * This function closes the file descriptor indicated by fd.
 * Any further operations on the closed file descriptor will result in an error.
 *
 * @param fd The file descriptor to be closed.
 * @return 0 on success, -1 on error and sets errno appropriately.
 */
int close(int fd);

/**
 * @brief Reads from a file descriptor.
 *
 * This function attempts to read count bytes from the file descriptor fd into the buffer starting at buf.
 *
 * @param fd The file descriptor to read from.
 * @param buf The buffer to read data into.
 * @param count The number of bytes to read.
 * @return The number of bytes read on success, -1 on error and sets errno appropriately.
 */
ssize_t read(int fd, void *buf, size_t count);

/**
 * @brief Writes to a file descriptor.
 *
 * This function attempts to write count bytes from the buffer starting at buf to the file descriptor fd.
 *
 * @param fd The file descriptor to write to.
 * @param buf The buffer containing the data to write.
 * @param count The number of bytes to write.
 * @return The number of bytes written on success, -1 on error and sets errno appropriately.
 */
ssize_t write(int fd, const void *buf, size_t count);

/**
 * @brief Repositions the file offset.
 *
 * This function repositions the offset of the open file associated with the file descriptor fd to the argument offset according to
 * the directive whence.
 *
 * @param fd The file descriptor.
 * @param offset The offset to set.
 * @param whence The directive for setting the offset.
 * @return The resulting offset location as measured in bytes from the beginning of the file, or -1 on error and sets errno
 * appropriately.
 */
off_t lseek(int fd, off_t offset, int whence);

/**
 * @brief Deletes a name from the filesystem.
 *
 * This function deletes the name specified by pathname from the filesystem.
 *
 * @param pathname The name to be deleted.
 * @return 0 on success, -1 on error and sets errno appropriately.
 */
int unlink(const char *pathname);

/**
 * @brief Removes a directory.
 *
 * This function removes the directory specified by pathname.
 *
 * @param pathname The directory to be removed.
 * @return 0 on success, -1 on error and sets errno appropriately.
 */
int rmdir(const char *pathname);

/**
 * @brief Changes the current working directory.
 *
 * This function changes the current working directory to the directory specified in path.
 *
 * @param path The path to the new working directory.
 * @return 0 on success, -1 on error and sets errno appropriately.
 */
int chdir(const char *path);

/**
 * @brief Gets the current working directory.
 *
 * This function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length
 * size.
 *
 * @param buf The buffer to store the current working directory.
 * @param size The size of the buffer.
 * @return buf on success, NULL on error and sets errno appropriately.
 */
char *getcwd(char *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* GETOPT_H_ */
