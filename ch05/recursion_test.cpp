/*
	PPP Recursive Fibonacci
	7 December 2023
	Find the largest Fibonacci number that fits in an int.
*/
#include "../std_lib_facilities.h"

// Define an inner recursive function; 
// TURNS OUT: can't define function within a function.
// Will this work?
int iter(int x1, int x2, int remaining){
	if (remaining == 0)
		return x2;
	else{
		return iter(x2, x1+x2, remaining - 1); // pass the value up the chain of calls
	}
}
int Fibonacci(int iterations){
	// Generate Fibonacci sequence up to a certain amount
	if (iterations <= 0)
		error("Must have a positive number of iterations.\n");
	const int n = iterations;
	constexpr int first = 0; // Begins the sequence
	constexpr int second = 1;

	return iter(first, second, n);
}

int main()
try{
	int iterations;
	cout << "Test Recursive Fibonacci Generation.\n"
		<< "Insert 'n' (the nth FibNum  will be returned): ";
	cin >> iterations;
	cout << "\nThe " << iterations;
	if (iterations == 1)
		cout << "st ";
	else if (iterations == 2)
		cout << "nd ";
	else if (iterations == 3)
		cout << "rd ";
	else
		cout << "th ";
	cout << "Fibonacci number is " << Fibonacci(iterations) << ".\n";
}
catch(runtime_error& e){
	cerr << "Runtime Error: " << e.what() << '\n';
}



