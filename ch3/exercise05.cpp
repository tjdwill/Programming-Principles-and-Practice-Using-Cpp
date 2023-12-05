#include "../std_lib_facilities.h"

double which_greater(double a, double b){
	double greater;
	double diff = a - b;
	if (diff > 0)
		greater = a;
	else
		// include case where a = b
		greater = b;
	return greater;
}

int main(){
	double val1 = 0.;
	double val2 = -1.;
	cout << "Input two numbers: ";
	while (cin >> val1 >> val2){
		cout << '\n';
		double larger = which_greater(val1, val2);
		double smaller = val1 + val2 - larger;

		// output data
		cout << "Smaller: " << smaller << '\n';
		cout << "Larger: " << larger << '\n';
		cout << "Sum: " << val1 + val2 << '\n';
		cout << "Difference: " << val1 - val2 << '\n';
		cout << "Product: " << val1 * val2 << '\n';
		cout << "Ratio: ";
		if (val2 == 0.)
			simple_error("Can not divide by zero!");
		else
			cout << val1 / val2 << "\n\n";
	}
	return 0;
}
