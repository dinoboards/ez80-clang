#ifndef _STDLIB_H
#define _STDLIB_H

#include <cdefs.h>

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

typedef struct {
  long long rem;
  long long quot;
} lldiv_t;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 8388607

#define allocp _allocp

__BEGIN_DECLS

/**
 * @brief Initializes the malloc system with a reserved stack size.
 *
 * @param heap_size The size of the heap to reserve.
 *
 * The heap is allocated from after the BSS section and grows upwards.
 */
void malloc_init(size_t heap_size);

/**
 * @brief Allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element.
 * @return void* Pointer to the allocated memory.
 */
void *calloc(size_t nmemb, size_t size) __attribute__((malloc));

/**
 * @brief Allocates size bytes and returns a pointer to the allocated memory.
 *
 * @param size Number of bytes to allocate.
 * @return void* Pointer to the allocated memory.
 */
void *malloc(size_t size) __attribute__((malloc));

/**
 * @brief Changes the size of the memory block pointed to by ptr to size bytes.
 *
 * @param ptr Pointer to the memory block to be reallocated.
 * @param size New size of the memory block.
 * @return void* Pointer to the reallocated memory.
 */
void *realloc(void *ptr, size_t size) __attribute__((warn_unused_result));

/**
 * @brief Frees the memory space pointed to by ptr.
 *
 * @param ptr Pointer to the memory to be freed.
 */
void free(void *ptr) __NOEXCEPT;
/**
 * @brief Converts a string to a double.
 *
 * The atof function converts the initial portion of the string pointed to by nptr to a double.
 *
 * @param nptr The string to be converted.
 *
 * @return The converted value as a double.
 */
double atof(const char *nptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to an integer.
 *
 * The atoi function converts the initial portion of the string pointed to by nptr to an int.
 *
 * @param nptr The string to be converted.
 *
 * @return The converted value as an int.
 */
int atoi(const char *nptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a long integer.
 *
 * The atol function converts the initial portion of the string pointed to by nptr to a long.
 *
 * @param nptr The string to be converted.
 *
 * @return The converted value as a long.
 */
long atol(const char *nptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a long long integer.
 *
 * The atoll function converts the initial portion of the string pointed to by nptr to a long long.
 *
 * @param nptr The string to be converted.
 *
 * @return The converted value as a long long.
 */
long long atoll(const char *nptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a float.
 *
 * The strtof function converts the initial portion of the string pointed to by nptr to a float.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 *
 * @return The converted value as a float.
 */
float strtof(const char *__restrict nptr, char **__restrict endptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a double.
 *
 * The strtod function converts the initial portion of the string pointed to by nptr to a double.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 *
 * @return The converted value as a double.
 */
double strtod(const char *__restrict nptr, char **__restrict endptr) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a long integer.
 *
 * The strtol function converts the initial portion of the string pointed to by nptr to a long.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 * The conversion is done according to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 * @param base The base to use for the conversion.
 *
 * @return The converted value as a long.
 */
long strtol(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to a long long integer.
 *
 * The strtoll function converts the initial portion of the string pointed to by nptr to a long long.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 * The conversion is done according to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 * @param base The base to use for the conversion.
 *
 * @return The converted value as a long long.
 */
long long strtoll(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to an unsigned long integer.
 *
 * The strtoul function converts the initial portion of the string pointed to by nptr to an unsigned long.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 * The conversion is done according to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 * @param base The base to use for the conversion.
 *
 * @return The converted value as an unsigned long.
 */
unsigned long strtoul(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

/**
 * @brief Converts a string to an unsigned long long integer.
 *
 * The strtoull function converts the initial portion of the string pointed to by nptr to an unsigned long long.
 * It also sets the value of endptr to point to the character after the last character used in the conversion.
 * The conversion is done according to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
 *
 * @param nptr The string to be converted.
 * @param endptr A pointer to a pointer to character.
 * @param base The base to use for the conversion.
 *
 * @return The converted value as an unsigned long long.
 */
unsigned long long strtoull(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

/**
 * @brief Sets the seed for the random number generator.
 *
 * The srand function sets the seed for the random number generator used by the rand function.
 *
 * @param seed The seed value.
 */
void srand(unsigned int seed);

/**
 * @brief Generates a random number.
 *
 * The rand function returns a pseudo-random number in the range of 0 to RAND_MAX.
 *
 * @return A pseudo-random number in the range of 0 to RAND_MAX.
 */
int rand(void);

/**
 * @brief Performs a binary search on a sorted array.
 *
 * The bsearch function searches for a key in a sorted array pointed to by base.
 * The array contains nmemb elements, each of size bytes. The comparison function compar is used to compare elements.
 *
 * @param key The key to search for.
 * @param base The base of the array to search.
 * @param nmemb The number of elements in the array.
 * @param size The size of each element in the array.
 * @param compar The comparison function.
 *
 * @return A pointer to the matching element, or NULL if no match is found.
 */
void *bsearch(void *key, void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
    __attribute__((nonnull(1, 2, 5)));
/**
 * @brief Sorts an array.
 *
 * The qsort function sorts an array pointed to by base. The array contains nmemb elements, each of size bytes.
 * The comparison function compar is used to compare elements.
 *
 * @param base The base of the array to sort.
 * @param nmemb The number of elements in the array.
 * @param size The size of each element in the array.
 * @param compar The comparison function.
 */
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) __attribute__((nonnull(1, 4)));

/**
 * @brief Causes abnormal program termination.
 *
 * The abort function causes abnormal program termination without cleaning up.
 */
void abort(void) __NOEXCEPT __attribute__((noreturn));

/**
 * @brief Registers a function to be called at normal program termination.
 *
 * The atexit function registers the function pointed to by func to be called at normal program termination.
 *
 * @param func The function to be called at normal program termination.
 *
 * @return Zero on success, or a non-zero value on error.
 */
int atexit(void (*)(void)) __NOEXCEPT;

/**
 * @brief Registers a function to be called at normal program termination.
 *
 * The on_exit function registers the function pointed to by func to be called at normal program termination.
 * The function is passed the exit status and the argument arg.
 *
 * @param func The function to be called at normal program termination.
 * @param arg The argument to be passed to the function.
 *
 * @return Zero on success, or a non-zero value on error.
 */
int on_exit(void (*)(int, void *), void *) __NOEXCEPT;

/**
 * @brief Causes normal program termination.
 *
 * The exit function causes normal program termination and performs cleanup.
 *
 * @param status The exit status.
 */
void exit(int) __NOEXCEPT __attribute__((noreturn));

/**
 * @brief Registers a function to be called at quick program termination.
 *
 * The at_quick_exit function registers the function pointed to by func to be called at quick program termination.
 *
 * @param func The function to be called at quick program termination.
 *
 * @return Zero on success, or a non-zero value on error.
 */
int at_quick_exit(void (*)(void)) __NOEXCEPT;

/**
 * @brief Causes quick program termination.
 *
 * The quick_exit function causes quick program termination without performing cleanup.
 *
 * @param status The exit status.
 */
void quick_exit(int) __NOEXCEPT __attribute__((noreturn));

/**
 * @brief Causes immediate program termination.
 *
 * The _Exit function causes immediate program termination without performing cleanup.
 *
 * @param status The exit status.
 */
void _Exit(int) __NOEXCEPT __attribute__((noreturn));

/**
 * @brief Computes the absolute value of an integer.
 *
 * The abs function computes the absolute value of the integer n.
 *
 * @param n The integer whose absolute value is to be computed.
 *
 * @return The absolute value of the integer n.
 */
int abs(int n);

/**
 * @brief Computes the absolute value of a long integer.
 *
 * The labs function computes the absolute value of the long integer n.
 *
 * @param n The long integer whose absolute value is to be computed.
 *
 * @return The absolute value of the long integer n.
 */
long labs(long n);

/**
 * @brief Computes the absolute value of a long long integer.
 *
 * The llabs function computes the absolute value of the long long integer n.
 *
 * @param n The long long integer whose absolute value is to be computed.
 *
 * @return The absolute value of the long long integer n.
 */
long long llabs(long long n);

/**
 * @brief Computes the quotient and remainder of integer division.
 *
 * The div function computes the quotient and remainder of the division of numer by denom.
 * The result is returned as a structure of type div_t, which contains two members: quot (the quotient) and rem (the remainder).
 *
 * @param numer The numerator.
 * @param denom The denominator.
 *
 * @return A structure of type div_t containing the quotient and remainder.
 */
div_t div(int numer, int denom);

/**
 * @brief Computes the quotient and remainder of long integer division.
 *
 * The ldiv function computes the quotient and remainder of the division of numer by denom.
 * The result is returned as a structure of type ldiv_t, which contains two members: quot (the quotient) and rem (the remainder).
 *
 * @param numer The numerator.
 * @param denom The denominator.
 *
 * @return A structure of type ldiv_t containing the quotient and remainder.
 */
ldiv_t ldiv(long numer, long denom);

/**
 * @brief Computes the quotient and remainder of long long integer division.
 *
 * The lldiv function computes the quotient and remainder of the division of numer by denom.
 * The result is returned as a structure of type lldiv_t, which contains two members: quot (the quotient) and rem (the remainder).
 *
 * @param numer The numerator.
 * @param denom The denominator.
 *
 * @return A structure of type lldiv_t containing the quotient and remainder.
 */
lldiv_t lldiv(long long numer, long long denom);

__END_DECLS

#endif /* _STDLIB_H */
