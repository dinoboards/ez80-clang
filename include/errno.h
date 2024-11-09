#ifndef _ERRNO_H
#define _ERRNO_H

#define EPERM  1 /* permission error */
#define EINVAL 2 /* invalid argument */
#define EIO    3 /* io error */
#define EDOM   4 /* math domain error */
#define ERANGE 5 /* math range error */

extern int errno;

#define ENOENT  6  // No such directory or directory - file does not exist
#define E2BIG   7  // Argument list too long.
#define EBADF   8  // Bad file descriptor
#define ENOMEM  9  // Cannot allocate memory
#define EACCES  10 // “Permission denied.” The file permissions do not allow
#define EFAULT  11 // “Bad address.” An invalid pointer was detected.
#define EEXIST  12 // “File exists.” An existing file was specified in a context where it only makes sense to specify a new file.
#define ENOTDIR 13 // “Not a directory.” A file that isn’t a directory was specified when a directory is required.
#define EISDIR  14 // “Is a directory.” You cannot open a directory for writing, or create or remove hard links to it.
#define EMFILE                                                                                                                     \
  15 // “Too many open files.” The current process has too many files open and can’t open any more. Duplicate descriptors do count
     // toward this limit.
#define EOPNOTSUPP                                                                                                                 \
  16 // The operation you requested is not supported. Some socket functions don’t make sense for all types of sockets, and others
     // may not be implemented for all communications protocols. On GNU/Hurd systems, this error can happen for many calls when the
     // object does not support the particular operation; it is a generic indication that the server knows nothing to do for that
     // call.

#endif /* _ERRNO_H */
