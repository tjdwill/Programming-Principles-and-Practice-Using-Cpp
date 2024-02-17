#include <iostream>

/*
    @author: tjdwill
    @date: 16 February 2024
    @title: PPP Exercise 17.03
        Write a function that lower-cases C-style strings
*/

char lower(char c)
{
    constexpr char upper_to_lower {'a'-'A'};
    if (c < 'A' || c > 'Z') return c;
    else return c + upper_to_lower;
}
void to_lower(char* s)
{
    char* curr {s};
    while (s != nullptr && *s != 0)  // guard against dereferencing nullptr
    {
        *s = lower(*s);
        ++s;
    }
}

int main()
{
    using std::cout;
    char old[] = "HELLO! I'm Testing My program for lowering Strings!\nABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+\n";
    cout << old << '\n';
    to_lower(old);
    cout << old << '\n';
}

/*
    I approached the solution using character arithmetic to practice staying in the layer of abstraction if possible. I know
    chars are implemented using numeric values, but if I don't need to dip into a lower level of abstraction, why do it?

    One thing I'm exploring is approaching some programming problams like a proof or logical argument. Given premises, can I reason
    the program to correctness? In this case, converting between lower and upper cases was algebraic:

    // L = U + K; K > 0
    // K = L-U, but only if L > U
    // otherwise, L = U - K such that K= U - L
    // where L is lowercase and U is uppercase

    However, the conversion factor, K, must be positive to constrain us to valid char subtraction (just in case negative numbers are not
    handled properly). However the comparison between lower and upper would need to be done on every call to the function. My original
    thought was to do the following:

    `constexpr char upper_to_lower {'A' > 'a' ? ('A'-'a') : ('a'-'A')};`

    This works for finding a positive K, but then how do I know which equation to use (subtracting K or adding it)? I would need to check
    if 'A' > 'a' on every call; I don't know how to check for this during compilation time. As a result, I have to use the explicit
    knowledge I have of how chars are represented in C++ (ASCII) to solve the problem efficiently, knowing that 'a' > 'A'  and that the
    lower and upper case letters are indeed distanced by the same factor for all letter pairs.

    This is a simple problem to solve practically, but attempting to solve the problem for a more general case leads to problems due to my
    limited understanding of the language. Is there a way to (programmatically) determine how characters are relate to one another
    at compile time?
*/
