// My attempt at implementing the exception handling components used thus far
// in Programming: Principles and Practice Using c++ (2nd ed.) by
// Bjarne Stroustrup
#include "err.hpp"

// ---------------------------------------------------------------------------
// Constructors
runtime_error::runtime_error() {}
runtime_error::runtime_error(const string& message)
    :err_message(message) {}
runtime_error::runtime_error(const string& message, const string& extra)
    :err_message(message), extra_info(extra) {}

// ---------------------------------------------------------------------------
// Methods
string runtime_error::what(){
    return err_message + extra_info;
}

// ---------------------------------------------------------------------------
// Utility Functions
void error(const string& a, const string& b){
    throw runtime_error(a, b);
}