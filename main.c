#include <stdint.h>
#include <stdio.h>

// extern void print_something(const char *str, float aa);

// float b = 45.0;

extern void bob();

extern void exit(int);

int main()
{
	uint24_t a = 1;
	uint24_t b = 2;

	uint24_t c = a + b;

	// bob();

	printf("Hello, World!, %d\n", c);

	return c;
	// float aa = (float) b;
	// aa *= 3.2;

	// print_something("Hello, World!\n", aa);



}

