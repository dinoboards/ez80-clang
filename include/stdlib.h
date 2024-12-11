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

double atof(const char *nptr) __attribute__((nonnull(1)));

int atoi(const char *nptr) __attribute__((nonnull(1)));

long atol(const char *nptr) __attribute__((nonnull(1)));

long long atoll(const char *nptr) __attribute__((nonnull(1)));

float strtof(const char *__restrict nptr, char **__restrict endptr) __attribute__((nonnull(1)));

double strtod(const char *__restrict nptr, char **__restrict endptr) __attribute__((nonnull(1)));

long strtol(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

long long strtoll(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

unsigned long strtoul(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

unsigned long long strtoull(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

void srand(unsigned int seed);

int rand(void);

void *bsearch(void *key, void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
    __attribute__((nonnull(1, 2, 5)));

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) __attribute__((nonnull(1, 4)));

void abort(void) __NOEXCEPT __attribute__((noreturn));

int atexit(void (*)(void)) __NOEXCEPT;

int on_exit(void (*)(int, void *), void *) __NOEXCEPT;

void exit(int) __NOEXCEPT __attribute__((noreturn));

int at_quick_exit(void (*)(void)) __NOEXCEPT;

void quick_exit(int) __NOEXCEPT __attribute__((noreturn));

void _Exit(int) __NOEXCEPT __attribute__((noreturn));

int abs(int n);

long labs(long n);

long long llabs(long long n);

div_t div(int numer, int denom);

ldiv_t ldiv(long numer, long denom);

lldiv_t lldiv(long long numer, long long denom);

__END_DECLS

#endif /* _STDLIB_H */
