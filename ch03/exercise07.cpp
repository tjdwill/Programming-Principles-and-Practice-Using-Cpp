#include "../std_lib_facilities.h"


int main(){
	string x = "";
	string y = "";
	string z = "";
	cout << "Input three strings: ";
	while (cin >> x >> y >> z){
		cout << '\n';
		if (x >= y){
			if (y >= z)
				// x >= y >= z
				cout << z << ", " << y << ", " << x;
			else if (z >= x)
				// z >= x >= y	
				cout << y<< ", " << x << ", " << z;
			else
				// x > z > y
				cout << y << ", " << z  << ", " << x;
		}
		else if (y >= z){
			// y >= z and y > x
			if (z > x)
				// y >= z > x
				cout << x << ", " << z << ", " << y;
			else
				// y > x > z
				cout << z << ", " << x << ", " << y;
		}
		else
			// z > y > x
			cout << x << ", " << y  << ", " << z;
		cout << '\n';
	}
	return 0;
}
