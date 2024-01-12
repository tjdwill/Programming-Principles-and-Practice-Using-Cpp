#include "my.h"
int foo {};

int main()
{
	foo = 7;  // shadows the implicity-declared `extern int foo`
	print_foo();
	print(99);
}
