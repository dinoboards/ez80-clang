#include <errno.h>
#include <stdio.h>

void perror(const char *s) { printf("%s: %d\r\n", s, errno); }
