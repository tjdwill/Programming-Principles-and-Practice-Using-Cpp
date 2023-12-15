// My attempt at implementing the exception handling components used thus far
// in Programming: Principles and Practice Using c++ (2nd ed.) by
// Bjarne Stroustrup
#include <string>
#include <iostream> 
#include <vector>

using std::string;
using std::cout;
using std::cerr;

// Error Handling Tooling
class runtime_error{
    public:
        runtime_error();
        runtime_error(const string&);
        runtime_error(const string&, const string&);
        string what();
    private:
        string err_message;
        string extra_info;
};
void error(const string& = "", const string& = "");