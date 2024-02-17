#include <iostream>

/*
    @author: tjdwill
    @date: 16 February 2024
    @title: PPP Exercise 17.04
        Write a function that copies C-style strings
*/

unsigned int len_str(const char* s)
{
    // Get the length of a C-style string (inc. terminator)
    unsigned int length {};
    if (!s) return length;

    while(*s){
        ++length;
        ++s;
    }
   ++length;  //include terminator
    return length;  
}

char* fs_strdup(const char* s)
{
    // Copies C-style strings
    if (!s) return nullptr;

    unsigned int sz {len_str(s)};
    char* cpy = new char[sz] {};
    for (unsigned int i{}; i < sz; ++i)
    {
        cpy[i] = s[i];
    }

    return cpy;
}

int main()
{
    using std::cout;
    char old[] = "Hi, I'm testing my program for copying strings.\n";
    cout << old << '\n';
    cout << len_str(old) << '\n';
    cout << len_str(nullptr) << '\n';

    char* cpy {fs_strdup(old)};
    cout << cpy << '\n';
    cout << len_str(cpy) << '\n';
    delete[] cpy;
}



/*
*   Though this method requires each string to be iterated over twice, I do not see another way to determine the size of a C string.
*   I chose the iteration inefficiency over using a fixed-size array.
*/
