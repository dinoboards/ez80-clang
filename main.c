#include <stdint.h>
#include <stdio.h>

// extern void print_something(const char *str, float aa);

// float b = 45.0;

extern void exit();

int main()
{
	uint24_t a = 1;
	uint24_t b = 2;

	uint24_t c = a + b;

	// exit(0);

	printf("Hello, World!\n");

	return c;
	// float aa = (float) b;
	// aa *= 3.2;

	// print_something("Hello, World!\n", aa);



}

