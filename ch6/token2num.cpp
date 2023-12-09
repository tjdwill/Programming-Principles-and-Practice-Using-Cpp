/* 
	@title: Token to Number Conversion
	@description: 
		Given a vector of tokens, generate the numbers from the numeric tokens.
	@thoughts:
		
*/
#include "../std_lib_facilities.h"


// declare a token type
constexpr char composed_kind  {'c'};
constexpr char digit_kind {'k'};
constexpr char decimal_kind {'.'};

class Token{
/* 
	Supported 'kind' values:
		'+'  addition
		'-'  substraction
		'*'  multiplication
		'/'  division
		'^'  exponentiation
		'%'	 modulo
		'('  grouping
		')'  grouping
		'.'  decimal delimiter
		'k'  digit
		'c'  composed digit 
*/
	public:
		char kind;
		bool is_num;
		double value;  // need this to store the composed number.
};
class TokenGenError {};
Token get_token(char input);
vector<Token> compose_nums(vector<Token> tokens);
double get_num(vector<double> nondecimals, vector<double> decimals);


int main(){
	// read user input into a string
	// only output valid tokens.

	// TEST: Begin with a pre-defined string
	string predef {"2 + 2 / 5 () jlie %^$ * 01234.56789"};
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

	cout << '\n' << "Received tokens:\n";
	for (Token token: tokens){
		cout
			<< "Kind: " << token.kind << ' '
			<< " Numeric?: ";
		if (token.is_num)
			cout << "Yes  ";
		else
			cout << "No   ";
		cout << "Value: " << token.value << '\n';
	}
}


// function defs
Token get_token(char input){
	// return the token based on the given input
	constexpr double operator_val {0.};  // Some default value until I can get MAX_DOUBLE or something
	constexpr double char_to_ascii = '0';
	constexpr double decimal_token_val = -1;

	switch (input){
		case '(': case ')': case '+': 
		case '-': case '*': case '/':
		case '%': case '^':
			return Token {input, false, operator_val};  // don't need `break` if returning, right?

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return Token {digit_kind, true, input - char_to_ascii};  // safe conversion
		// floating-point support
		case '.':
			return Token{input, true, decimal_token_val};
		default:
			throw TokenGenError{};
	}
}

vector<Token> compose_nums(vector<Token> tokens){
	// reconstruct the vector of tokens, composing numbers along the way
	// start with integers.

	string func_name = "<compose_nums>: ";

	if (tokens.size() == 0)
		error(func_name + "Empty token vector.");

	/*
		This goes against what BjS tells us to do, but I see no other way
		at this point in time. The following loop iterates through the vector
		of tokens. If it finds a numeric token, it looks until it finds a
		non-numeric token. To do so without double-counting tokens, I need
		to make an iterator variable jump.

		Sorry BjS :(
	*/
	vector<double> nondecimals;
	vector<double> decimals;
	vector<Token> updated_tokens {};
	bool decimal_found {false};
	Token token;
	for (int i {0}; i < tokens.size(); ++i){

		token = tokens[i];
		
		// We don't have vector.clear yet, so...
		nondecimals = vector<double> {};
		decimals = vector<double> {};
		
		if (!token.is_num)
			updated_tokens.push_back(token);	
		// Handle first entry of next composed token
		else{
			if (token.kind == composed_kind)
				error(func_name + "Composed numeric tokens are not allowed.\n");
			else if (token.kind == decimal_kind)
				decimal_found = true;
			else
				nondecimals.push_back(token.value);
		/*
			Here's where it gets gnarly. Look through the rest of the vector up
			until you find the next operator, you reach the end, or there is
			an error. 

			If you find the next operator, update the outer loop variable and
			break the loop. Also, reset the decimal found variable if necessary.
		*/
			for (int j {i+1}; j < tokens.size() - 1; ++j){
				token = tokens[j];
				if (token.is_num){
					// enter number-gathering context
					// found either a digit or a decimal point
					switch (token.kind){
						case composed_kind:
							error(func_name + "Composed numeric tokens are not allowed.\n");
							break;
						case decimal_kind:
							{
								if (decimal_found)
									error(func_name, "Cannot have multiple decimal points in a number.");
								else
									decimal_found = true;
							}
							break;
						default: // digit-kind
							{
								if (decimal_found)
									decimals.push_back(token.value);
								else
									nondecimals.push_back(token.value);
							}
							break;
					}
				}
				else{
					// found non-numeric token
					Token composed_tkn = {
						composed_kind, true, get_num(nondecimals, decimals)
					};
					updated_tokens.push_back(composed_tkn);
					updated_tokens.push_back(token);
					// loop updates; variable resets
					i = j;
					decimal_found = false;
					break;
				}
			}
		}
	}
	return updated_tokens;
}

double get_num(vector<double> nondecimals, vector<double> decimals){
	return 0.;
}


