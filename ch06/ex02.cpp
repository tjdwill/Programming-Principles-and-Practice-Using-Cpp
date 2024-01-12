// tjdwill
// PPP Exercise 6.2
// 11 December 2023
// Task: Add '{' '}' support to calculator. 


/* 
	In context of the program, the curly brackets would work exactly the same as
	parentheses. Therefore, they should be added under Primary as such:

	Primary:
		...
		"{" Expression "}"
*/

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

constexpr char num_kind {'k'};
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
		case '{': case '}':
			return Token(ch);        // let each character represent itself
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);         // put digit back into the input stream
			double val;
			cin >> val;              // read a floating-point number
			return Token(num_kind, val);   // let 'k' represent "a number"
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

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') 
			error("')' expected");
        return d;
    }
	case '{':
	{
		double d = expression();
		t = ts.get();
        if (t.kind != '}') 
			error("'}' expected");
        return d;
	}
    case num_kind:            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
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
{(4+5) * 6} / (3+4)=
= 7.71429
54/7=
= 7.71429
*/
//------------------------------------------------------------------------------
