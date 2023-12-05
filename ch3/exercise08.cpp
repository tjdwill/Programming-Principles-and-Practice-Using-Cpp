#include "../std_lib_facilities.h"

int is_even(int a){
	return a % 2 == 0;
}

int is_odd(int a){
	// return a % 2 == 1; // no func call overhead; Does this matter?
	return not is_even(a);
}

int main(){
	int input;
	cout << "Test if a number is even or odd: ";
	cin >> input;
	cout << '\n';
	if (is_even(input))
		cout << input << " is an even number.\n";
	else
		cout << input << " is an odd number.\n";
	return 0;
}


