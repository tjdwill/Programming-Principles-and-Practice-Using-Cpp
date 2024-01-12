// @name: tjdwill
// @date: 12 December 2023
// @title: PPP Exercise 6.6
// @task:
//		Implement a sentence checker that takes in user input and determines
//		if the input is a valid sentence based on our book's defined grammar.

/*
	Since we are only dealing with strings, there is not really a need to 
	create a custom type. I am thinking this will work by generating booleans.
	The booleans will check if the given string is a Noun, Verb, Conjunction, 
	or Sentence. If it is the terminator, we print the result.
	Also, because the progression of building a sentence is a bit cyclical,
	there may not be a need to ever put a token back. There's only one valid
	path to sentence construction.

	It's difficult to articulate what I mean in words, but hopefully the code
	express it properly.
*/

//------------------------------------------------------------------------------

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

bool is_noun(string test);
bool is_verb(string test);
bool is_conjunction(string test);
bool is_sentence();
bool want_quit();
const string terminator {"."};
// use `string` instead of `char` because any word that begins with 'q' would
// trigger the quit condition otherwise.
const string quit_str {"q"};  

//------------------------------------------------------------------------------

int main()
try{
	bool got_sentence {false};
	cout << "Insert '" << quit_str << "' to quit.\n\n"; 
	while (cin){
		got_sentence = is_sentence();
		cout << "Result: ";
		if (got_sentence)
			cout << "OK.\n\n";
		else
			cout << "not OK.\n\n";
		if (want_quit())
			break;
	}
}
catch(exception& e){
	cerr << "Exception: " << e.what() << '\n';
	return 1;
}
catch(...){
	cerr << "Unanticipated error.\n";
	return 2;
} 

//------------------------------------------------------------------------------
bool is_noun(string test){
	const vector<string> nouns {
		"birds", "fish", "C++"	
	};
	for (string valid: nouns){
		if (test == valid)
			return true;
	}
	return false;
}

bool is_verb(string test){
	const vector<string> verbs {
		"rules", "fly", "swim"	
	};
	for (string valid: verbs){
		if (test == valid)
			return true;
	}
	return false;
}

bool is_conjunction(string test){
	const vector<string> conjunctions {
		"and", "but", "or"	
	};
	for (string valid: conjunctions){
		if (test == valid)
			return true;
	}
	return false;
}

bool is_sentence(){
	/*
		Recall that sentences are defined as follows:

		Sentence:
			Noun Verb
			Sentence Conjunction Sentence
	*/
	bool result {false};

	string s;
	cin >> s;
	// test absolutes. As currently defined, a Sentence must begin with a Noun
	// followed by a Verb, even a Sentence made of other Sentences.
	if (!is_noun(s)){
		// flush the buffer and return
		while (s != terminator)
			cin >> s;
		return result;
	}
	
	cin >> s;
	if (!is_verb(s)){
		// error("A Noun must followed by a Verb.\n");
		while (s != terminator)
			cin >> s;
		return result;
	}

	// Test for conjoined sentence
	cin >> s;
	if (s == terminator)
		result = true;
	else if (is_conjunction(s))
		result = is_sentence();
	return result;
}

bool want_quit(){
	string s {};
	cin >> s;
	if (s == quit_str)
		return true;
	else{
		// cin.putback(s); // Can't do this; apparently we can only put back one char.
		// put back the string in reverse char order
		for (int i = s.size()-1; i >=0; --i)
			cin.putback(s[i]);
		return false;
	}
}

//------------------------------------------------------------------------------
/*
	Insert 'q' to quit.

	birds fly but fish swim .
	Result: OK.

	Bjarne is the man .
	Result: not OK.

	C++ rules .
	Result: OK.

	.
	Result: not OK.

	q
*/
//------------------------------------------------------------------------------
