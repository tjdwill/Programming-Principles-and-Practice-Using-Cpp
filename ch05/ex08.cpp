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
try{
	vector<int> int_list {};
	int n {-1};
	cout << "Insert number of integers to sum: ";
	cin >> n;
	if (n < 1){
        error("You must sum at least one value.\n");
    }

	cout << "\nPlease input the integer sequence (press '|' to signal the end)"
	<< ": \n";
	
	int curr_input;
	while(cin >> curr_input)
		int_list.push_back({curr_input});
/*    
	// debugging
	cout << "Vector Elements:\n";
	for (int x: int_list){
		cout << x << '\n';
	}
*/
	// sum the values of the vector as specified.
	if (n > int_list.size()){
		error("Not enough integers to add.\n");
	}
	int sum {0};
	int prev_val {0};
	int curr_val {0};
	cout << "The sum of \n(";
	for (int i {0}; i < n; ++i){
		curr_val = int_list[i];
		cout << curr_val << ' ';
		sum += curr_val;
	}
	cout << ")\nis " << sum << '\n';
}
catch(exception& e){
    cerr << "Error: " << e.what() << '\n';
    return 1;
}

