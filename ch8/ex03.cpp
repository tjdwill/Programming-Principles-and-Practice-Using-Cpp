#include "ex.hpp"

void fibonacci(int, int, vector<int>&, int);

int main()
try{
    vector<int> nums {};
    int first {};
    int second {};
    int amount {};

    cout << "Insert Number of Terms: ";
    cin >> amount;
    cout << '\n' << "Starting Term: ";
    cin >> first;
    cout << "\nSecond Term: ";
    cin >> second;

    fibonacci(first, second, nums, amount);
    print(nums, "Fibonacci Output");
}
catch(runtime_error& e){
    cerr << "Runtime Error: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Error.\n";
}
//----------------------------------------------------------------------------
void fibonacci(int x, int y, vector<int>& v, int n)
{
/*
    Based on the problem specification, it appears BjS would like the input
    vector to be modified. It also sounds like he wants to support a
    Fibonacci-*like* sequence in that each successive number is the sum of the
    previous two beginning with 'x' and 'y'.

    If we want to only use empty vectors, why include the option to pass a
    vector at all? Why not just make the function return a vector of integers?
    I think I may be missing something on that point, but I'll do what BjS asks
    in the spec.
*/
    if (n < 0)
        error("<fibonacci>: Non-negative number iterations only.\n");
    if (v.size() != 0)
        error("<fibonacci>: Input vector must be empty.\n");
    // Modify the vector
    switch (n){
        case 0:
            break;
        case 1:
            v.push_back(x);
            break;
        case 2:
            v.push_back(x);
            v.push_back(y);
            break;
        default:
        {
            v.push_back(x);
            v.push_back(y);
            n -= 2;
            // Append the rest
            int last {x};
            int current {y};
            int temp {last + current};

            for (int i {0}; i < n; ++i)
            {
                v.push_back(temp);
                last = current;
                current = temp;
                temp = last + current;
            }
            break;
        }
    }
}

/*
Insert Number of Terms: 10

Starting Term: 1

Second Term: 2

Fibonacci Output
1
2
3
5
8
13
21
34
55
89
*/