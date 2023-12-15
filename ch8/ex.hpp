#include <string>
#include <iostream> 
#include <vector>
#include "err.hpp"

// ---------------------------------------------------------------------------
// Make these names available across the project.
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::cerr;

// ---------------------------------------------------------------------------
// Function declarations
void print(const vector<int> &, string);
void reversed(vector<int> &);  // in-place vector reversal
vector<int> reverse(const vector<int>&);  // returns reversed copy
