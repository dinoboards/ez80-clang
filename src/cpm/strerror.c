#include <errno.h>

char *strerror(int errnum) {
  switch (errnum) {
  case 0:
    return "OK";
  case ENOENT:
    return "File not found";
  case ENOMEM:
    return "Out of memory";
  case EMFILE:
    return "Too many open files";
  case ENFILE:
    return "Too many file descriptors";
  case EEXIST:
    return "File already exists";
  case EACCES:
    return "Invalid access";
  case ENOTTY:
    return "Not a TTY";
  case EBADF:
    return "Bad file descriptor";
  case E2BIG:
    return "Arg list too long";
  case EDOM:
    return "Arg out of domain";
  case ERANGE:
    return "Arg out of range";
  case EINVAL:
    return "Invalid argument";
  default:
    return "Unknown error";
  }
}
