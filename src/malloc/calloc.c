#include "include/mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * This file contains the implementation of the function calloc()
 * For the details on malloc() and align4() refer the file malloc.c
 * calloc() first creates the required chunk of memory using malloc()
 * then it sets the values of each byte to 0 by iterating through it.
 */

void *calloc(size_t number, size_t size) {
  size_t *new;

  new = malloc(number * size);

  if (new)
    memset(new, 0, number * size);

  return new;
}
