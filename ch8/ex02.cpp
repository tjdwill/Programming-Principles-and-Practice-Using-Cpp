// #include "../std_lib_facilities.h"
#include "ex.hpp"


void print(const vector<int>& nums, const string& label)
{
    // prints the content of a vector of ints.
    cout << '\n' << label << '\n';
    for (int x: nums)
        cout << x << '\n';
}

// Added for Ex 8.6
void print(const vector <string>& strs, const string& label)
{
    // prints vector of strings
    cout << '\n' << label << '\n';
    for (string s: strs)
        cout << s << '\n';
}

