#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef dev_t
 * @brief Device number
 */
typedef int dev_t;

/**
 * @typedef ino_t
 * @brief Inode number
 */
typedef unsigned long ino_t;

/**
 * @typedef mode_t
 * @brief File mode (permissions and type)
 */
typedef unsigned int mode_t;

/**
 * @typedef nlink_t
 * @brief Number of hard links to a file
 */
typedef unsigned int nlink_t;

/**
 * @typedef uid_t
 * @brief User ID
 */
typedef unsigned int uid_t;

/**
 * @typedef gid_t
 * @brief Group ID
 */
typedef unsigned int gid_t;

/**
 * @typedef off_t
 * @brief File offset (used for file sizes and positions)
 */
typedef long off_t;

/**
 * @typedef blksize_t
 * @brief Block size (used for filesystem block sizes)
 */
typedef int blksize_t;

/**
 * @typedef blkcnt_t
 * @brief Block count (number of blocks allocated to a file)
 */
typedef long blkcnt_t;

/**
 * @typedef time_t
 * @brief Time (used for representing time values)
 */
typedef long time_t;

/**
 * @typedef ssize_t
 * @brief Signed size type (used for functions that return a size or an error code)
 */
typedef long ssize_t;

#ifdef __cplusplus
}
#endif

#endif
