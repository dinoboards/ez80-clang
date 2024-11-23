#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>

int open(const char *pathname, int flags, ...) {
  const char *mode;
  FILE       *file;
  int         fd;

  // Determine the mode string based on the flags
  if ((flags & O_RDWR) == O_RDWR) {
    mode = "r+";
  } else if (flags & O_WRONLY) {
    mode = "w";
  } else {
    mode = "r";
  }

  // Handle the O_CREAT flag
  if (flags & O_CREAT) {
    // va_list args;
    // va_start(args, flags);
    // mode_t mode_flags = va_arg(args, mode_t);
    // va_end(args);

    // If O_CREAT is specified, we need to use "w+" mode to create the file
    if ((flags & O_RDWR) == O_RDWR) {
      mode = "w+";
    } else if (flags & O_WRONLY) {
      mode = "w";
    } else {
      mode = "w";
    }
  }

  // Open the file using fopen
  file = fopen(pathname, mode);
  if (!file) {
    return -1; // Return -1 on failure
  }

  // Get the file descriptor from the FILE pointer
  fd = fileno(file);
  if (fd == -1) {
    fclose(file);
    return -1;
  }

  return fd;
}
