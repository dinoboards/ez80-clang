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
#define O_APPEND   0x1000 /* Append on each write */
#define O_NONBLOCK 0x2000 /* Non-blocking mode */
#define O_SYNC     0x4000 /* Synchronous writes */

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

/* Function prototypes */
int open(const char *pathname, int flags, ...);
int creat(const char *pathname, mode_t mode);
// int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif /* _FCNTL_H */
