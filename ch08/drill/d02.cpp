#include <iostream>

void swap_v(int a, int b)
{
	// This will not actually swap the values outside of the function call
	// due to it being a pass-by-value (arguments get a copy of input values)
	// This function is a silent logic failure.
	int temp {a};
	a = b;
	b = temp;
}

void swap_r(int& a, int& b)
{
	// This swap will work because the signature is a pass-by-reference.
	// The objects are writable.

	int temp {a};
	a = b;
	b = temp;
}

/*
void swap_cr(const int& a, const int& b)
{
	// This swap will fail and will likely fail to compile
	// Pass-by-const-reference essentially makes the object(s)
	// read-only. You can't write to them.

	int temp {a};
	a=b;
	b=temp;
}
*/

void print_swap(int& x, int& y)
{
	// makes my life easier
	using std::cout;
	cout << "Original Values:\nX: " << x << "\tY: " << y << '\n';
	swap_r(x, y); // Change to call swap_v or swap_r
	cout << "Swapped Values:\nX: " << x << "\tY: " << y << '\n';
	cout << '\n';
}

int main()
{
	int x = 7;
	int y = 9;
	print_swap(x, y);
	
	const int cx {7};
	const int cy {9};
	std::cout << "Original Values:\nX: " << cx << "\tY: " << cy << '\n';
	swap_v(cx, cy); // Change to call swap_v or swap_r
	std::cout << "Swapped Values:\nX: " << cx << "\tY: " << cy << '\n';

	{
		/*
		Still don't do this. The common ancestor of this unnamed scope and the target namespace "std" is 
		the global scope! This means all of the names in `std` are placed into the global scope (I think),
		and are only temporarily accessible in this unnamed scope. Once we leave the scope, the "std" names
		still persist but are not visible. Naming collisions are possible and, depending on how large a 
		given library is and how uncreative we are with naming, highly likely.
		*/
		using namespace std;
		cout  << "\nTesting using-directive scoping.\n";
	}
	// cout << "Compilation fail point.\n";  // Compilation Error: undeclared identifier "cout"

}
