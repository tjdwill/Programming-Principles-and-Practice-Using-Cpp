// PPP Exercise 5.8
#include "../std_lib_facilities.h"

/*
	Testing some inputs for vector push backs. I'm trying to figure out
 	if there is a standard way to ensure *only* a certain type is appended
  	to a given vector.

   	UPDATE: I think the check is done automatically based on re-reading the material in
	section 4.6 "Vectors".
*/

int main()
{
	vector<int> int_list {};
	for (int i=0; i < 10;  ++i){
		double x = i + 1.;
		int_list.push_back({x}); // RAISES ERROR
	}
	// try to add a string (RAISED COMPILER ERROR)
	// int_list.push_back("testing");
	// try to add a char (narrowing)
	int_list.push_back({'A'});

	for (int x: int_list){
		cout << x <<'\n';
	}
}
