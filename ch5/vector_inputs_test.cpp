// PPP Exercise 5.8
#include "../std_lib_facilities.h"

/*
Task: Read in and sum 'N' integers that a user provides. Handle all inputs
and errors.

Thinking:

The user can input anything. To prevent reading in an undesired value
(char, string, or float), can I use list-style initialization {} for the
vector?
Will this prevent narrowing for subsequent values appended to the vector?
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
