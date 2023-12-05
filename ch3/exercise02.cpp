#include "../std_lib_facilities.h"

// miles to kilometers

double kilo_per_mile = 1.609;

int main(){
	double miles = -1;
	cout << "miles: ";
	cin >> miles;
	cout << "\nkilometers: " << miles * kilo_per_mile << '\n';
	return 0;
}

