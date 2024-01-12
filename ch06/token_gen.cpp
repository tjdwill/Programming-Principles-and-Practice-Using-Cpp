/* 
	@title: Token Generator
	@description: 
		The idea of this file is to practice generating tokens for the 
		calculator program. We want to be able to parse the operators
		as well as the numbers.
	@thoughts:
		Mr. Stroustrup (BjS) uses tokens in his examples in section
		6.3 of the PPP book. Within, he has a `double` that stores
		some read-in value.

		I know the example isn't the final version of the program
		infrastructure, but I am confused: how can one read some input as
		`char`s and the others as `double`s without knowing what order they
		come in from the user input?

		As of now, I am exploring a design that only reads in user input as a
		parsable string. The string's `char`s will be looped over and tokenized
		if possible. I also propose changing the `double value` property to
		`bool is_num` such that we can distinguish operators from numbers.

		Begin exploration.
*/
#include "../std_lib_facilities.h"


// declare a token type
class Token{
	public:
		char kind;
		bool is_num;
};
class TokenGenError {};
Token get_token(char input);


int main(){
	// read user input into a string
	// only output valid tokens.

	// TEST: Begin with a pre-defined string
	string predef {"2 + 2 / 5 () jlie %^$ * 0123456789"};
	vector<Token> tokens {};
	cout << "Initialized vector size: " << tokens.size() << '\n';

	for (char x: predef){
		try{
			tokens.push_back(get_token(x));
		}
		catch(TokenGenError){
			; // do nothing
		}
	}
    /*
		Print out the tokens generated from defined string.
		Expected tokens:
		{2, true}
		{+, false}
		{2, true}
		{/, false}
		{5, true}
		{ (, false}
		{ ), false}
		{%, true}
		{^, true}
		{*, true}
		0->9...true
	*/

	cout << '\n' << "Received tokens:\n";
	for (Token token: tokens){
		cout
			<< "Kind: " << token.kind << ' '
			<< "Numeric?: ";
		if (token.is_num)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}


// function defs
Token get_token(char input){
	// return the token based on the given input
	switch (input){
		case '(': case ')': case '+': 
		case '-': case '*': case '/':
		case '%': case '^':
			return Token {input, false};  // don't need `break` if returning, right?

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		// case '.': for later floating-point support
			return Token {input, true};

		default:
			throw TokenGenError{};
	}
}


/*
	==============
	Tokenize Test
	==============
	Input: "2 + 2 / 5 () jlie %^$ * 0123456789"

	Output:
	Received tokens:
	Kind: 2 Numeric?: Yes
	Kind: + Numeric?: No
	Kind: 2 Numeric?: Yes
	Kind: / Numeric?: No
	Kind: 5 Numeric?: Yes
	Kind: ( Numeric?: No
	Kind: ) Numeric?: No
	Kind: % Numeric?: No
	Kind: ^ Numeric?: No
	Kind: * Numeric?: No
	Kind: 0 Numeric?: Yes
	Kind: 1 Numeric?: Yes
	Kind: 2 Numeric?: Yes
	Kind: 3 Numeric?: Yes
	Kind: 4 Numeric?: Yes
	Kind: 5 Numeric?: Yes
	Kind: 6 Numeric?: Yes
	Kind: 7 Numeric?: Yes
	Kind: 8 Numeric?: Yes
	Kind: 9 Numeric?: Yes
*/
