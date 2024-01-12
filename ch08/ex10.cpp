#include "../std_lib_facilities.h"


double maxv(vector<double>& v)
{
    // Assuming BjS wants a double.
    sort(v.begin(), v.end());
    return v[v.size() - 1];
}

int main()
try{
    vector<double> input {0., 3.3, 5.678, 2.71828, 1.9475, -9.4};
    cout << "In Vector:\n";
    for (double x: input)
        cout << x << ", ";
    cout << '\n' << "Max Value: " << maxv(input) << '\n';

}
catch(exception& e){
    cerr << "RuntimeError: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}

/*
In Vector:
0, 3.3, 5.678, 2.71828, 1.9475, -9.4, 
Max Value: 5.678
*/