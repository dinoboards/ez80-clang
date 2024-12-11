#ifndef _STRING_H
#define _STRING_H

#include <cdefs.h>

__BEGIN_DECLS

/**
 * @brief Copy memory area
 *
 * @param dest Destination memory area
 * @param src Source memory area
 * @param n Number of bytes to copy
 * @return void* Pointer to the destination memory area
 */
extern void *memcpy(void *__restrict dest, const void *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Move memory area
 *
 * @param dest Destination memory area
 * @param src Source memory area
 * @param n Number of bytes to move
 * @return void* Pointer to the destination memory area
 */
extern void *memmove(void *dest, const void *src, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Fill memory with a constant byte
 *
 * @param s Pointer to the memory area
 * @param c Byte to fill the memory area with
 * @param n Number of bytes to fill
 * @return void* Pointer to the memory area
 */
extern void *memset(void *s, int c, size_t n) __attribute__((nonnull(1)));

/**
 * @brief Compare memory areas
 *
 * @param s1 Pointer to the first memory area
 * @param s2 Pointer to the second memory area
 * @param n Number of bytes to compare
 * @return int An integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less
 * than, to match, or be greater than the first n bytes of s2.
 */
extern int memcmp(const void *s1, const void *s2, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Scan memory for a character
 *
 * @param s Pointer to the memory area
 * @param c Character to search for
 * @param n Number of bytes to scan
 * @return void* Pointer to the matching byte or NULL if the character does not occur in the given memory area
 */
extern void *memchr(const void *s, int c, size_t n) __attribute__((nonnull(1)));

/**
 * @brief Copy a string
 *
 * @param dest Destination string
 * @param src Source string
 * @return char* Pointer to the destination string
 */
extern char *strcpy(char *__restrict dest, const char *__restrict src) __attribute__((nonnull(1, 2)));

/**
 * @brief Copy a string with a maximum length
 *
 * @param dest Destination string
 * @param src Source string
 * @param n Maximum number of characters to copy
 * @return char* Pointer to the destination string
 */
extern char *strncpy(char *__restrict dest, const char *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Concatenate two strings
 *
 * @param dest Destination string
 * @param src Source string
 * @return char* Pointer to the destination string
 */
extern char *strcat(char *__restrict dest, const char *__restrict src) __attribute__((nonnull(1, 2)));

/**
 * @brief Concatenate two strings with a maximum length
 *
 * @param dest Destination string
 * @param src Source string
 * @param n Maximum number of characters to concatenate
 * @return char* Pointer to the destination string
 */
extern char *strncat(char *__restrict dest, const char *__restrict src, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Locate first occurrence of character in string
 *
 * @param s Pointer to the null-terminated string to be scanned
 * @param c Character to be located
 * @return char* Pointer to the first occurrence of the character c in the string s, or NULL if the character is not found
 */
extern char *strchr(const char *s, int c) __attribute__((nonnull(1)));

/**
 * @brief Locate last occurrence of character in string
 *
 * @param s Pointer to the null-terminated string to be scanned
 * @param c Character to be located
 * @return char* Pointer to the last occurrence of the character c in the string s, or NULL if the character is not found
 */
extern char *strrchr(const char *s, int c) __attribute__((nonnull(1)));

/**
 * @brief Locate first occurrence of any character in string
 *
 * @param s Pointer to the null-terminated string to be scanned
 * @param accept Pointer to the null-terminated string containing the characters to match
 * @return char* Pointer to the first occurrence in s of any of the characters in accept, or NULL if no such character is found
 */
extern char *strpbrk(const char *s, const char *accept) __attribute__((nonnull(1, 2)));

/**
 * @brief Locate substring
 *
 * @param haystack Pointer to the null-terminated string to be scanned
 * @param needle Pointer to the null-terminated substring to be located
 * @return char* Pointer to the beginning of the located substring, or NULL if the substring is not found
 */
extern char *strstr(const char *haystack, const char *needle) __attribute__((nonnull(1, 2)));

/**
 * @brief Tokenize string
 *
 * @param s Pointer to the null-terminated string to be tokenized
 * @param delim Pointer to the null-terminated string containing the delimiter characters
 * @return char* Pointer to the next token, or NULL if there are no more tokens
 */
extern char *strtok(char *__restrict s, const char *__restrict delim) __attribute__((nonnull(2)));

/**
 * @brief Duplicate string
 *
 * @param s Pointer to the null-terminated string to be duplicated
 * @return char* Pointer to the newly allocated string, or NULL if insufficient memory was available
 */
extern char *strdup(const char *s) __attribute__((__malloc__)) __attribute__((nonnull(1)));

/**
 * @brief Duplicate string with a maximum length
 *
 * @param s Pointer to the null-terminated string to be duplicated
 * @param n Maximum number of characters to duplicate
 * @return char* Pointer to the newly allocated string, or NULL if insufficient memory was available
 */
extern char *strndup(const char *s, size_t n) __attribute__((__malloc__)) __attribute__((nonnull(1)));

/**
 * @brief Get span until character in string
 *
 * @param s Pointer to the null-terminated string to be scanned
 * @param reject Pointer to the null-terminated string containing the characters to match
 * @return size_t Number of characters in the initial segment of s which consist only of characters not in reject
 */
extern size_t strcspn(const char *s, const char *reject) __attribute__((nonnull(1, 2)));

/**
 * @brief Get span of character set in string
 *
 * @param s Pointer to the null-terminated string to be scanned
 * @param accept Pointer to the null-terminated string containing the characters to match
 * @return size_t Number of characters in the initial segment of s which consist only of characters from accept
 */
extern size_t strspn(const char *s, const char *accept) __attribute__((nonnull(1, 2)));

/**
 * @brief Calculate the length of a string
 *
 * @param s Pointer to the null-terminated string
 * @return size_t Number of characters in the string, excluding the null terminator
 */
extern size_t strlen(const char *s) __attribute__((nonnull(1)));

/**
 * @brief Calculate the length of a string with a maximum length
 *
 * @param s Pointer to the null-terminated string
 * @param maxlen Maximum number of characters to examine
 * @return size_t Number of characters in the string, excluding the null terminator, but at most maxlen
 */
extern size_t strnlen(const char *s, size_t maxlen) __attribute__((nonnull(1)));

/**
 * @brief Compare two strings
 *
 * @param s1 Pointer to the first null-terminated string
 * @param s2 Pointer to the second null-terminated string
 * @return int An integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be
 * greater than s2
 */
extern int strcmp(const char *s1, const char *s2) __attribute__((nonnull(1, 2)));

/**
 * @brief Compare two strings with a maximum length
 *
 * @param s1 Pointer to the first null-terminated string
 * @param s2 Pointer to the second null-terminated string
 * @param n Maximum number of characters to compare
 * @return int An integer less than, equal to, or greater than zero if the first n characters of s1 is found, respectively, to be
 * less than, to match, or be greater than the first n characters of s2
 */
extern int strncmp(const char *s1, const char *s2, size_t n) __attribute__((nonnull(1, 2)));

/**
 * @brief Compare two strings ignoring case
 *
 * @param s1 Pointer to the first null-terminated string
 * @param s2 Pointer to the second null-terminated string
 * @return int An integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be
 * greater than s2, ignoring case
 */
extern int strcasecmp(const char *s1, const char *s2) __attribute__((nonnull(1, 2)));

/**
 * @brief Compare two strings with a maximum length, ignoring case
 *
 * @param s1 Pointer to the first null-terminated string
 * @param s2 Pointer to the second null-terminated string
 * @param n Maximum number of characters to compare
 * @return int An integer less than, equal to, or greater than zero if the first n characters of s1 is found, respectively, to be
 * less than, to match, or be greater than the first n characters of s2, ignoring case
 */
extern int strncasecmp(const char *s1, const char *s2, size_t n) __attribute__((nonnull(1, 2)));

__END_DECLS

#endif /* _STRING_H */
