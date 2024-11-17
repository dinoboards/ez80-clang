// This file is intentionally empty.
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <stddef.h> // For size_t
#include <stdint.h> // For fixed-width integer types

#ifdef __cplusplus
extern "C" {
#endif

typedef int           dev_t;     /* Device number */
typedef unsigned long ino_t;     /* Inode number */
typedef unsigned int  mode_t;    /* File mode */
typedef unsigned int  nlink_t;   /* Number of links */
typedef unsigned int  uid_t;     /* User ID */
typedef unsigned int  gid_t;     /* Group ID */
typedef long          off_t;     /* File offset */
typedef int           blksize_t; /* Block size */
typedef long          blkcnt_t;  /* Block count */
typedef long          time_t;    /* Time */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TYPES_H */
