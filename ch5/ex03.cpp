/*

Problems in the original code:

First, there's no #include statement to use the iostream facilities.

Next,

double ctok(double c)
{
	int k = c + 273.15;  // incorrect type 'int'; rogue constant.
	return int  // no statement-terminating semicolon; returns type instead of value.
}

int main()
{
	double c = 0;  // not sure if this is the best initialization value due to it
				   // being in the valid range of values. We have no way to know
				   // if something went awry.\

	cin >> d;      // wrong variable
	double k = ctok("c");  // invalid input of type <string>. Should be <double>.
	Cout << k << '/n';  // undefined type Cout. Should use cout.; 
						// '/n' is not the newline character; '\n' is.
	// There's also no explicit return value, but that's fine for the main function.
}
*/

// Corrected code
#include "../std_lib_facilities.h"

double ctok(double c)
{
	// input temperature in Celcius (max value is -273.15 as that's absolute 0).
	double ctok_conversion = 273.15;
	if (c < -ctok_conversion)
		throw runtime_error("<ctok>: Can not have an input lower than -273.15 (absolute 0).\n");
	/* if we want to silently fail do the following instead:
		return -1;  // invalid Kelvin value
	*/
	return c + ctok_conversion;
}
int main()
{
	// redefine the conversion; I split the two so ctok is entirely independent.
	double ctok_conversion = 273.15;
	double c = -(ctok_conversion + 1.);
	cout << "Celcius: ";
	cin >> c;
	cout << '\n';
	cout << "Kelvin: " << ctok(c) << '\n';
}
