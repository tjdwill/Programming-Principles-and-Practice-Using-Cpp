// Type your code here, or load an example.
#include <iostream>
#include <vector>

// Find the size of types `int`, `double`, and `bool` without using `sizeof`

int main()
{
    unsigned int ARR_SIZE {2};
    using std::cout;
    // int
    int arr_int[ARR_SIZE] {};
    cout << std::dec << "Int size: " << &arr_int[1] << " - " << arr_int << '\n';
    // double
    double arr_double[ARR_SIZE] {};
    cout << std::dec << "Double size: " << &arr_double[1] << " - " << arr_double << '\n';
    // char
    bool arr_bool[ARR_SIZE] {};
    cout << "Bool size: " << &arr_bool[1] << " - " << arr_bool  << '\n';

    // Better method
    unsigned long long int sz_int { (unsigned long long int) &arr_int[1] - (unsigned long long int) arr_int };
    unsigned long long int sz_double { (unsigned long long int) &arr_double[1] - (unsigned long long int) arr_double };
    unsigned long long int sz_bool { (unsigned long long int) &arr_bool[1] - (unsigned long long int) arr_bool };

    cout << "\nCorrect `int` size:\t" << sz_int;
    cout << "\nCorrect `double` size:\t" << sz_double;
    cout << "\nCorrect `bool` size:\t" << sz_bool << '\n';

    cout << "\n`sizeof` Comparisons\n";
    cout << "int:\t" << sizeof(int) << '\n';
    cout << "double:\t" << sizeof(double) << '\n';
    cout << "bool:\t" << sizeof(bool) << '\n';

}

/*

Since we can't use `sizeof` except for verification, I went another route by finding the difference in address value between 
two adjacent elements in an array of the desired type. Initially, I printed the difference in addresses directly, but
the value was 1 for any type used. This leads me to believe I encountered pointer arithmetic. To get around this problem
and express the answer in terms of bytes, I casted the addresses to `unsigned long long int`s to ensure the type is large
enough to contain the address value and took the difference between the casted values. I received the expected values.
*/
