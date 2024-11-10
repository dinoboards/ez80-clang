#ifndef _STRING_H
#define _STRING_H

#include <cdefs.h>

__BEGIN_DECLS

extern void *memcpy(void *__restrict dest, const void *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

extern void *memmove(void *dest, const void *src, size_t n) __attribute__((nonnull(1, 2)));

extern void *memset(void *s, int c, size_t n) __attribute__((nonnull(1)));

extern int memcmp(const void *s1, const void *s2, size_t n) __attribute__((nonnull(1, 2)));

extern void *memchr(const void *s, int c, size_t n) __attribute__((nonnull(1)));

extern char *strcpy(char *__restrict dest, const char *__restrict src) __attribute__((nonnull(1, 2)));

extern char *strncpy(char *__restrict dest, const char *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

extern char *strcat(char *__restrict dest, const char *__restrict src) __attribute__((nonnull(1, 2)));

extern char *strncat(char *__restrict dest, const char *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

extern char *strchr(const char *s, int c) __attribute__((nonnull(1)));

extern char *strrchr(const char *s, int c) __attribute__((nonnull(1)));

extern char *strpbrk(const char *s, const char *accept) __attribute__((nonnull(1, 2)));

extern char *strstr(const char *haystack, const char *needle) __attribute__((nonnull(1, 2)));

extern char *strtok(char *__restrict s, const char *__restrict delim) __attribute__((nonnull(2)));

extern char *strdup(const char *s) __attribute__((__malloc__)) __attribute__((nonnull(1)));

extern char *strndup(const char *s, size_t n) __attribute__((__malloc__)) __attribute__((nonnull(1)));

extern size_t strcspn(const char *s, const char *reject) __attribute__((nonnull(1, 2)));

extern size_t strspn(const char *s, const char *accept) __attribute__((nonnull(1, 2)));

extern size_t strlen(const char *s) __attribute__((nonnull(1)));

extern size_t strnlen(const char *s, size_t maxlen) __attribute__((nonnull(1)));

extern int strcmp(const char *s1, const char *s2) __attribute__((nonnull(1, 2)));

extern int strncmp(const char *s1, const char *s2, size_t n) __attribute__((nonnull(1, 2)));

extern int strcasecmp(const char *s1, const char *s2) __attribute__((nonnull(1, 2)));

extern int strncasecmp(const char *s1, const char *s2, size_t n) __attribute__((nonnull(1, 2)));

__END_DECLS

#endif /* _STRING_H */
