/*
	PPP Exercise 5.12
	7 December 2023
	"Bulls and Cows"
*/
#include "../std_lib_facilities.h"

constexpr int num_bulls {4};

int pow(int base, int exponent){
	// Raise a base to the `exponent`th power
	// using ints, so we can only use positive exponents.
	if (exponent < 0)
		error("<pow>: This function only handles positive exponents\n");
	int out {1};
	for (int n {exponent}; n > 0; --n){
		out *= base;
	}
	return out;
}

bool is_element(int num, vector<int> numbers){
	// test if a number is an element of a vector of integers.
	bool output {false};
	for (int i {0}; i < numbers.size(); ++i){
		if (num == numbers[i]){
		  output = true;
		  break;
		}
	}
	return output;
}

vector<int> get_guess(){
	// Returns a vector of the user's guess
	// valid inputs: any number from 0 to 9999
	// assuming that an input such as `0027` is transformed into 27.

	constexpr int max_val {9999};
	constexpr int min_val {0};
	int usr_input {-1}; 
	int size {num_bulls};

	cout << "Guess the number: ";
	cin >> usr_input;
	if (usr_input < min_val || usr_input > max_val)
		error("Invalid input. Must be between 0000 and 9999 (inclusive).\n");
	
	/*
		Parse the number into its constituent digits
		Example: 
		5483 = 5*1000 + 4*100 + 8*10 + 3*1
	*/

	int temp {usr_input};
	int factor {0}; // if we divide by zero, something is wrong.
	int index {-1};
	int digit {-1}; // var. for calculated digit.
	vector<int> guess(size); // number of places.
    // initialize guess vector for digit uniqueness query
	for (int i {0}; i < guess.size(); ++i){
		guess[i] = -1; 
	}
	for (int i {size - 1}; i >= 0; --i){
		factor = pow(10, i);
		index = (size-1)-i; // preserve proper ordering
		digit = temp / factor; // relying on integer division truncation.
		// validate uniqueness of digits
		if (is_element(digit, guess))
			error("Input number must have non-repeat digits (ex. 5678).\n");
		else
			guess[index] = digit;
		temp -= (digit*factor);
	}
	return guess;
}

vector<int> bulls_and_cows(vector<int> guess, vector<int> answer){
	/* 
		Iterate through the vectors to determine how many of the digits in
		the guess vector are present in value and place in the answer vector
		(bull) and how many are present in value but not correct in place (cow)

		Output vector format:
			{num_of_bulls, num_of_cows}
	*/
	
	if (guess.size() != answer.size())
		error("Guess and answer have differing number of digits.\n");
	int bulls {0};
	int cows {0};
	
	// for each element in guess, iterate over answer and check if the value
	// is present and what place it is in. Update trackers as necessary.
	int guess_digit {-1};
	int answer_digit {-1};
	for (int i {0}; i < guess.size(); ++i){
		guess_digit = guess[i];
		for (int j {0}; j < answer.size(); ++j){
			answer_digit = answer[j];
			if (guess_digit == answer_digit){
				if (j == i)
					++bulls;
				else
					++cows;
			}
		}
	}
	return vector<int> {bulls, cows};
}

int main()
try{
	cout << "Bulls and Cows!\n";
	bool game_won {false};
	const vector <int> answer {1, 2, 3, 4};
	vector <int> guess;
	vector <int> bnc;
	while (!game_won){
		guess = get_guess();
		bnc = bulls_and_cows(guess, answer);
		if (bnc[0] == num_bulls)
			game_won = true;
		else{
			cout << "\nGuess: ";
			for (int x: guess) {
				cout << x;
			}
			cout << '\n' << "Bulls: " << bnc[0] << '\n'
				<< "Cows: " << bnc[1] << "\n\n";
		}
	}
	cout << "You win!\n";
}
catch(exception& e){
	cerr << "Error: " << e.what() << '\n';
}
catch(...){
	cerr << "Unknown Error!\n";
}

