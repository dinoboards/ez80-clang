#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern void print_something(const char *str, float aa);

// float b = 45.0;

extern void bob();

extern void exit(int);

void maybe_exit(uint24_t c)
{
	if (c == 3)
	{
		exit(0);
	}
}

void exit_hook1(void) {
   printf("exit hook 1 called\n");
}


int main()
{
	uint24_t a = 1;
	uint24_t b = 2;
	uint24_t c = a + b;

   if (atexit(exit_hook1) != 0) {
      printf("Failed to register exit hook\n");
      return EXIT_FAILURE;
   }

	printf("Hello, World! %d\r\n", c);

	maybe_exit(c);

	printf("Should not be here\r\n");

	return c;
}

