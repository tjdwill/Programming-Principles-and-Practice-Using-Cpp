#include "../std_lib_facilities.h"


int get_max(int a, int b){
	int greater;
	int diff = a - b;
	if (diff > 0)
		greater = a;
	else
		// include case where a = b
		greater = b;
	return greater;
}
int get_min(int a, int b){
	int min;
	int diff = a - b;
	if (diff > 0)
		min = b;
	else
		// include case where a = b
		min = a;
	return min;
}
/* Using the above two functions, we can easily find the
 * order of the numbers x, y, z by 
 * min = get_min(x, get_min(y, z));
 * max = get_max(x, get_max(y, z));
 * middle = (x + y + z) - (min + max);
 * such that the order is min, middle, max.
 * However, I think Stroustrup would like the problem to be
 * solved using conditionals.
*/
int main(){
	int x = 0;
	int y = 0;
	int z = 0;
	cout << "Input three integers: ";
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
