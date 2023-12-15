#include "../../std_lib_facilities.h"
#include "my.h"

void print(int i){
	cout << '\n' << i << '\n';
}

void print_foo()
{
	print(foo);
}
