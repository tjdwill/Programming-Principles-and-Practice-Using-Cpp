#include "../std_lib_facilities.h"

double ctok(double c)
{
	// input temperature in Celcius (max value is -273.15 as that's absolute 0)
	constexpr double ctok_conversion = 273.15;
	if (c < -ctok_conversion)
		throw runtime_error("<ctok>: Can not have an input lower than -273.15 (absolute 0).\n");
	/* if we want to silently fail do the following instead:
		return -1;  // invalid Kelvin value
	*/
	return c + ctok_conversion;
}

double ktoc(double k)
{
	// input temperature in Kelvin (min value is 0)
	constexpr double ktoc_conversion {-273.15};
	constexpr double absolute_zero {0.};
	if (k < absolute_zero)
		throw runtime_error("<ktoc>: Can not have an input lower than absolute 0.");
	return k + ktoc_conversion;
}

// Attempt overloading
double ctok(double temp, bool invert_direction)
{
	double converted_temp {temp}; // Something's wrong if converted_temp == temp in the end.
	// Kelvin to Celcius
	if (invert_direction)
		converted_temp = ktoc(temp);
	// Celcius to Kelvin
	else
		converted_temp = ctok(temp);
	return converted_temp;
}
int main()
try{
	constexpr double ctok_conversion {273.15};  // defining this twice to keep the other functions independent.
	double temp {-(ctok_conversion + 1.)}; // input temperature
	char current_unit {' '}; 
	// Get input to allow user to define which operation to run
	cout << "Insert temperature value and its current unit: ";
	
	while(cin >> temp >> current_unit){
		cout << '\n';

		if (current_unit == 'k' or current_unit == 'K')
			cout << temp << "K is " << ctok(temp, true) << "C.\n";
		else if (current_unit == 'c' or current_unit == 'C')
			cout << temp << "C is " << ctok(temp, false) << "K.\n";
		else{
			cerr << "Invalid unit '" << current_unit << "'. Input 'K' or 'C'.\n";
			return 1;
		}
	}
	return 0;
}
catch(runtime_error& e){
	cerr<< "\nRuntime Error: " << e.what() << '\n';
	return 2;
}
catch(...){
	cerr << "Something unexpectedly weird happened.\n";
	return 3;
}
