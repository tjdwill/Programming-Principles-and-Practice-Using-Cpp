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
void print(const vector<int> &, const string&);
void print(const vector<string>&, const string&);

void swap(int&, int&);
void swap(string&, string&);

void reversed(vector<int> &);  // in-place vector reversal
void reversed(vector<string>&);

vector<int> reverse(const vector<int>&);  // returns reversed copy
vector<string> reverse_str(const vector<string>&);