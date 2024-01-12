#include "../std_lib_facilities.h"

double get_index(
    const vector<double>& price, 
    const vector<double>& weight
){
    if (price.size() != weight.size())
        error("<get_index>: Vectors must be equal in size.\n");
    
    double sum {};
    for (int i {}; i < price.size(); ++i){
        sum += price[i] * weight[i];
    }
    return sum;
}

//----------------------------------------------------------------------------
int main()
try{
    
}
catch(exception& e){
    cerr << "RuntimeError: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}