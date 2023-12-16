#include "../std_lib_facilities.h"


struct Stats{
    double min {};
    double max {};
    double mean {};
    double median {};
};

bool is_even(int x) {return x % 2 == 0;}

double get_median(const vector<double>& v){
    // Assumes input vector is sorted.
    // Since I'm already passing the vector
    // by value in `get_stats` which calls this function, 
    // I don't want to copy the input vector twice.

    int sz = v.size();
    if (sz == 0)
        error("<get_median>: Vector is empty!\n");
    
    int median_indx = sz/2;
    double med {};

    if (is_even(sz))
        med = (v[median_indx] + v[median_indx - 1]) / 2;
    else
        med = v[median_indx];  // ex. 5/2 -> 2; v[2] == 3rd element

    return med;    
}

Stats get_stats(vector<double> v){
    // using copu of the vector to allow mutation

    int sz = v.size();
    if (sz == 0)
        error("<get_stats>: Vector is empty!\n");

    Stats data {};
    sort(v.begin(), v.end());
    data.min = v[0];
    data.max = v[sz - 1];
    data.median = get_median(v);
    double mean {};

    for (double x: v){
        mean += x;
    }
    mean /= sz;
    data.mean = mean;

    return data;
}
void print_stats(const vector<double>& v){
    cout << "In Vector:\n";
    for (double x: v)
        cout << x << ", ";
    cout << '\n';
    Stats stats = get_stats(v);
    cout
        << "Min:\t" << stats.min << '\n'
        << "Max:\t" << stats.max << '\n'
        << "Mean:\t" << stats.mean << '\n'
        << "Median:\t" << stats.median << '\n'
        << '\n';
}

int main()
try{
    vector<double> even {0., 3.3, 5.678, 2.71828, 1.9475, -9.4};
    vector<double> odd {1., 2., 3., 4., 5., 6., 7.};
    print_stats(even);
    print_stats(odd);
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
Min:	-9.4
Max:	5.678
Mean:	0.707297
Median:	2.33289

In Vector:
1, 2, 3, 4, 5, 6, 7, 
Min:	1
Max:	7
Mean:	4
Median:	4

*/