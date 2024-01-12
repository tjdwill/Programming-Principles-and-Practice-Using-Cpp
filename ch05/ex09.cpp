// PPP Exercise 5.9
#include "../std_lib_facilities.h"

/*
	Task: Read in and sum 'N' integers that a user provides. Handle all inputs
	and errors; Handle overflow case.
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
	int prev_sum {0};
	cout << "The sum of \n(";
	for (int i {0}; i < n; ++i){
		curr_val = int_list[i];
		cout << curr_val << ' ';
		// check for overflow
		prev_sum = sum;
		sum += curr_val;
		if (
			(sum < 0 && (prev_sum > 0 && curr_val > 0)) ||
			(sum >= 0 && (prev_sum < 0 && curr_val < 0)))
		{
			error("\nOverflow: The sum cannot be represented as an int.\n");
		}
	}
	cout << ")\nis " << sum << '\n';
}
catch(exception& e){
	cerr << "Error: " << e.what() << '\n';
	return 1;
}
/*
	Testing Output:

	The max positive integer is (2^32)/2 - 1

	"""
	Insert number of integers to sum: 4

	Please input the integer sequence (press '|' to signal the end):
	100 2147483547 1 0 10
	|
	The sum of
	(100 2147483547 1
	Overflow: The sum cannot be represented as an int.
	"""
	"""
	Insert number of integers to sum: 5

	Please input the integer sequence (press '|' to signal the end): 
	2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 
	|
	The sum of 
	(2147483647 2147483647 
	Overflow: The sum cannot be represented as an int.
	"""


	This method should work for all cases then because (MAX_INT + MAX_INT) -> -1).
	Meaning, the max positive sum attempt is bounded by a negative number;
	the check should always trigger (?).

	Similarly, the negative case should also always work because the greatest
	negative sum (MIN_INT + MIN_INT) -> 0, which hits the check.
*/
