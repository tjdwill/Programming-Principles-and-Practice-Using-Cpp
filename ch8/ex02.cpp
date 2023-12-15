// #include "../std_lib_facilities.h"
#include "ex.hpp"


void print(const vector<int>& nums, string label)
{
    // prints the content of a vector of ints.
    cout << '\n' << label << '\n';
    for (int x: nums)
        cout << x << '\n';
}

