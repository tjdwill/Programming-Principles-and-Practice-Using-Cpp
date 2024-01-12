// tjdwill
// PPP Exercise 6.3
// 11 December 2023
// Task: Add factorial support to calculator. 


/* 
	In context of the program, the curly brackets would work exactly the same as
	parentheses. Therefore, they should be added under Primary as such:

	Primary:
		...
		"{" Expression "}"
*/

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

constexpr char num_kind {'8'};
class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(num_kind), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer = Token(num_kind, 0.);     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream(){
    full = false; { };    // no Token in buffer
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
	if (cin){
		switch (ch) {
		case '=':   // for "print"
		case 'x':    // for "quit"
		case '(': case ')': case '+': case '-': case '*': case '/':
		case '{': case '}': case '!':
			return Token(ch);        // let each character represent itself
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);         // put digit back into the input stream
			double val;
			cin >> val;              // read a floating-point number
			return Token(num_kind, val);   // let '8' represent "a number"
		}
		default:
			error("<Token_stream.get>: Bad token");
		}
	}
	else
		error("<Token_stream.get>: No input to tokenize.\n");
}

//------------------------------------------------------------------------------

Token_stream ts {Token_stream()};        // provides get() and putback() 

//------------------------------------------------------------------------------
int factorial(int x){
	// Calculates the relevant factorial value.

	constexpr int max_input {19};
	if (x < 0)
		error("<factorial>: can't take factorial of negative number.\n");
	if (x > max_input)
		error("<factorial>: `int` cannot hold factorial value this large.\n");

	int ret {1};  // initializes to 0! (1)
	for (int i {x} ; i > 1; --i)
		{ret *= i;}
	return ret;
}
//-----------------------------------------------------------------------------
double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
	double ret {};

    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        ret = expression();
        t = ts.get();
        if (t.kind != ')') 
			error("')' expected");
/*		
		Factorials grow so quickly, we easily exceed the 
		int max value in a short while. There really isn't
		much point in using expressions, but I do it anyway
		to support inputs such as (7)!
*/
		// more factorial support
		t = ts.get();
        if (t.kind == '!')
            ret = factorial(ret);  // narrows to int
        else
            ts.putback(t); // some other operator was found
		break;
    }
	case '{':
	{
		ret = expression();
		t = ts.get();
        if (t.kind != '}') 
			error("'}' expected");
		break;
	}
    case num_kind:            // we use '8' to represent a number
		ret = t.value;
		// check for factorial
		t = ts.get();
		if (t.kind == '!')
			ret = factorial(ret);  // narrows to int
		else
			ts.putback(t); // some other operator was found
        break;  
    default:
        error("primary expected");
    }
	return ret;
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
			break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{	
	cout 
		<< "Welcome to our simple calculator.\n"
		<< "Please enter expressions using floating-point numbers.\n"
		<< "Current supported operators: '+', '-', '*', '/'\n"
		<< "Print answer using '='\n\n";
	double val {0.};
    while (cin) {
        Token t = ts.get();
		
        if (t.kind == 'x') break; // 'q' for quit
        if (t.kind == '=')        // ';' for "print now"
            cout << "= " << val << '\n';
        else{
            ts.putback(t);
        	val = expression();
		}
    }
//    keep_window_open();
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    // keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    // keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------
// Test(s)
/*
Welcome to our simple calculator.
Please enter expressions using floating-point numbers.
Current supported operators: '+', '-', '*', '/'
Print answer using '='

(7)!
=
= 5040
7!=
= 5040
7*8!=
= 282240
8!=
= 40320
7*40320=
= 282240
(7*8)!=
error: <factorial>: `int` cannot hold factorial value this large.
*/
//------------------------------------------------------------------------------
