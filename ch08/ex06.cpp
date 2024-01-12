#include "ex.hpp"

/*
int main()
try{
    vector<string> test {"Hello", "Hi", "Hey"};
    print(test, "Forward");
    print(reverse_str(test), "Reverse");
    reversed(test);
    print(test, "In-place Reverse");
}
catch(runtime_error& e){
    cerr << "RuntimeError: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}
*/
//-----------------------------------------------------------------------------
void swap(string& a, string& b)
{
    string temp {a};
    a = b;
    b = temp;
}

void reversed(vector<string>& v)
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

vector<string> reverse_str(const vector<string>& v)
{
    vector<string> rev (v.size());

    int indx = v.size() - 1;
    for (int i = indx; i >= 0; --i)
        rev[indx - i] = v[i];
    return rev;
}

//-----------------------------------------------------------------------------
/*
    Forward
    Hello
    Hi
    Hey

    Reverse
    Hey
    Hi
    Hello

    In-place Reverse
    Hey
    Hi
    Hello
*/