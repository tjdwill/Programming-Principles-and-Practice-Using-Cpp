#include "ex.hpp"

//----------------------------------------------------------------------------
int main()
try{
    vector<int> test {1, 2, 3, 4, 5};
    print(test, "Forward");
    print(reverse(test), "Reverse");
    reversed(test);
    print(test, "In-place Reverse");
}
catch(runtime_error& e){
    cerr << "RuntimeError: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}

//----------------------------------------------------------------------------
void swap(int& a, int& b)
{
    int temp {a};
    a = b;
    b = temp;
}

void reversed(vector<int>& v)
{
    const int size = v.size();
    const int times = size / 2;
    int j {size - 1};
    for (int i {0}; i < times; ++i)
    {
        swap(v[i], v[j]);
        --j;
    }
}

vector<int> reverse(const vector<int>& v)
{
    vector<int> rev (v.size());

    int indx = v.size() - 1;
    for (int i = indx; i >= 0; --i)
        rev[indx - i] = v[i];
    return rev;
}

/*
Forward
1
2
3
4
5

Reverse
5
4
3
2
1

In-place Reverse
5
4
3
2
1

*/