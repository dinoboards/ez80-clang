#ifndef _FCNTL_H
#define _FCNTL_H

#include <sys/types.h> // For mode_t, off_t
#include <unistd.h>    // For ssize_t

#ifdef __cplusplus
extern "C" {
#endif

/* File access modes */
#define O_RDONLY 0x0000 /* Open for reading only */
#define O_WRONLY 0x0001 /* Open for writing only */
#define O_RDWR   0x0002 /* Open for reading and writing */

/* File creation flags */
#define O_CREAT  0x0100 /* Create file if it does not exist */
#define O_EXCL   0x0200 /* Error if O_CREAT and the file exists */
#define O_NOCTTY 0x0400 /* Do not assign controlling terminal */
#define O_TRUNC  0x0800 /* Truncate file to zero length */

/* File status flags */
#define O_APPEND 0x1000 /* Append on each write */
// #define O_NONBLOCK 0x2000 /* Non-blocking mode - not supported */
#define O_SYNC 0x4000 /* Synchronous writes */

/* File descriptor flags */
#define FD_CLOEXEC 1 /* Close on exec */

/* File permission flags (here for compatibility - but will mostly be ignored)*/
#define S_IRUSR 0x0400 /* Read permission, owner */
#define S_IWUSR 0x0200 /* Write permission, owner */
#define S_IXUSR 0x0100 /* Execute/search permission, owner */
#define S_IRGRP 0x0040 /* Read permission, group */
#define S_IWGRP 0x0020 /* Write permission, group */
#define S_IXGRP 0x0010 /* Execute/search permission, group */
#define S_IROTH 0x0004 /* Read permission, others */
#define S_IWOTH 0x0002 /* Write permission, others */
#define S_IXOTH 0x0001 /* Execute/search permission, others */

/**
 * @brief Open a file
 *
 * @param pathname Path to the file to be opened
 * @param flags Flags to control how the file is opened
 * @param ... Optional mode_t argument specifying the file mode (permissions) if a new file is created
 * @return int File descriptor on success, or -1 on error with errno set appropriately
 *
 * The open function opens a file specified by pathname. The flags argument controls how the file is opened.
 * Common flags include:
 * - O_RDONLY: Open the file for read-only access.
 * - O_WRONLY: Open the file for write-only access.
 * - O_RDWR: Open the file for both reading and writing.
 * - O_CREAT: Create the file if it does not exist. Requires a third argument of type mode_t.
 * - O_EXCL: Ensure that this call creates the file. If this flag is specified and the file already exists, open will fail.
 * - O_TRUNC: Truncate the file to zero length if it already exists and is opened for writing.
 * - O_APPEND: Open the file in append mode. Writes will always append to the end of the file.
 * - O_SYNC: Open the file for synchronous I/O.
 *
 * If the O_CREAT flag is specified, an additional argument of type mode_t must be provided to specify the file mode (permissions).
 * The mode argument specifies the permissions to use in case a new file is created. It is typically specified using symbolic
 * constants defined in <sys/stat.h>, such as S_IRUSR (read permission for the owner), S_IWUSR (write permission for the owner),
 * etc.
 */
int open(const char *pathname, int flags, ...);

/**
 * @brief Create a new file or rewrite an existing one
 *
 * @param pathname Path to the file to be created
 * @param mode Mode (permissions) to be applied to the new file
 * @return int File descriptor on success, or -1 on error with errno set appropriately
 *
 * The creat function creates a new file or rewrites an existing file specified by pathname.
 * The mode argument specifies the file mode (permissions) for the new file.
 */
int creat(const char *pathname, mode_t mode);

// int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif /* _FCNTL_H */
