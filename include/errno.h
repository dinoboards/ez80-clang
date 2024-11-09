#ifndef _ERRNO_H
#define _ERRNO_H

extern int errno;

typedef int error_t;

#define EOK         0
#define ENOENT      2          /* No such file or directory */
#define EIO         5          /* Input/output error */
#define E2BIG       7          /* Argument list too long */
#define EBADF       9          /* Bad file descriptor */
#define EBDFD       EBADF      /* Bad file descriptor */
#define ENOMEM      12         /* Cannot allocate memory */
#define EACCES      13         /* Permission denied */
#define EEXIST      17         /* File exists */
#define EINVAL      22         /* Invalid argument */
#define ENFILE      23         /* Too many open files in system */
#define EMFILE      24         /* Too many open files */
#define ENOTTY      25         /* Inappropriate ioctl for device */
#define EFBIG       27         /* File too large */
#define EDOM        33         /* Numerical argument out of domain */
#define ERANGE      34         /* Result too large */
#define EAGAIN      35         /* Resource temporarily unavailable */
#define EWOULDBLOCK EAGAIN     /* Operation would block */
#define EOPNOTSUPP  45         /* Operation not supported */
#define ENOTSUP     EOPNOTSUPP /* Operation not supported */
#define ENOLCK      77         /* No locks available */
#define EOVERFLOW   84         /* Value too large to be stored in data type */
#define ESTAT       1024       /* Unknown driver error */

#define ELAST 1024 /* Must be equal largest errno */

#endif /* _ERRNO_H */
