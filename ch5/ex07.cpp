// PPP Exercise 5.7
// Quadratic Formula Implementation"
#include "../std_lib_facilities.h"
// #include <cassert>

vector<double> solve_x2(double a, double b, double c)
{
	// gets coefficients for equation
	// ax^2 + bx + c = 0
	if (a == 0.)
		throw runtime_error("Not a quadric equation\n");
	
	double discriminant {b*b - 4*a*c};
	if (discriminant < 0)
		// try a user-defined exception
		throw runtime_error("No real roots\n");
	
	// initialize solution
	vector<double> zeros;
	double x1 = (-b + sqrt(discriminant))/(2*a);
	double x2 = (-b - sqrt(discriminant))/(2*a);
	
	zeros.push_back(x1);
	if (x2 != x1)
		zeros.push_back(x2);
	/*
	Check if calculated solutions are correct. 
	This is theoretically valid, but floating-point imprecision may cause
	failure.

	for (double i: zeros){
		assert(
			((a*i*i)+(b*i)+c) == 0.
		);
	}
	*/
	return zeros;
}

int main()
try{
	double a, b, c;
	cout << "Input the quadratic equation coefficients 'a b c':\n";
	cin >> a >> b >> c;
	vector<double> solutions = solve_x2(a, b, c);
	
	cout << "Solutions:\n";
	for(double x: solutions){
		cout << x << '\n';
	}
	return 0;
}
catch(runtime_error& e)
{
	cerr << "RuntimeException: " << e.what() << '\n';
	return 1;
}

