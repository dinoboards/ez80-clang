#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* File type macros */
#define S_IFMT   0170000 /* type of file */
#define S_IFDIR  0040000 /* directory */
#define S_IFCHR  0020000 /* character special */
#define S_IFBLK  0060000 /* block special */
#define S_IFREG  0100000 /* regular */
#define S_IFIFO  0010000 /* fifo */
#define S_IFLNK  0120000 /* symbolic link */
#define S_IFSOCK 0140000 /* socket */

/* File mode macros */
#define S_ISUID 0004000 /* set user id on execution */
#define S_ISGID 0002000 /* set group id on execution */
#define S_ISVTX 0001000 /* save swapped text even after use */
#define S_IRUSR 0000400 /* read permission, owner */
#define S_IWUSR 0000200 /* write permission, owner */
#define S_IXUSR 0000100 /* execute/search permission, owner */
#define S_IRGRP 0000040 /* read permission, group */
#define S_IWGRP 0000020 /* write permission, group */
#define S_IXGRP 0000010 /* execute/search permission, group */
#define S_IROTH 0000004 /* read permission, others */
#define S_IWOTH 0000002 /* write permission, others */
#define S_IXOTH 0000001 /* execute/search permission, others */

/* File status structure */
struct stat {
  dev_t     st_dev;     /* device */
  ino_t     st_ino;     /* inode */
  mode_t    st_mode;    /* protection */
  nlink_t   st_nlink;   /* number of hard links */
  uid_t     st_uid;     /* user ID of owner */
  gid_t     st_gid;     /* group ID of owner */
  dev_t     st_rdev;    /* device type (if inode device) */
  off_t     st_size;    /* total size, in bytes */
  blksize_t st_blksize; /* blocksize for filesystem I/O */
  blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
  time_t    st_atime;   /* time of last access */
  time_t    st_mtime;   /* time of last modification */
  time_t    st_ctime;   /* time of last status change */
};

/* Function prototypes */
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_STAT_H */
