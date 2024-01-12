// PPP Exercise 8.7

/* 
    For this problem, I was originally going to use a nested `for` loop to
    match each string in the sorted vector to its twin in the unsorted vector
    and find the age based on the match index. However, this is ineffective or
    rather incomplete because two names with differing ages will not have those
    differing ages reflected in the output. For example, "John" 46 and "John"
    23, when sorted, would output "John" 46 both times because 46 comes first
    when "John" is matched in the unsorted vector.

    Therefore, since BjS suggests copying the string vector anyway (meaning
    using additional memory), why not just store a vector of strings with the
    names and ages appended together? This way, the ages and names are kept
    together, and they will still be sorted properly. Downside is that now the
    data is technically sorted by name and age.

    UPDATE: Looking at the solution, I did not need to account for non-unique
    names, nor did the solution require `doubles`; it was implemented using
    `ints`. Sounds good.
*/


#include "../std_lib_facilities.h"
//----------------------------------------------------------------------------
// Declarations
std::string int_to_str(int);
vector<string> assoc_ages(const vector<string>&, const vector<int>&);

void work(vector<string>&);
void print(const vector<string>&, const string&);
//----------------------------------------------------------------------------
int main()
try{
    vector<string> names {};
    vector<int> ages {};
    const string stop = "STOP";
    string name {};
    int age;

    while (cin){
        cin >> name;
        if (name == stop)
            break;
        cin >> age;
        names.push_back(name);
        ages.push_back(age);
    }

    vector<string> pairs = assoc_ages(names, ages);
    work(pairs);

}
catch(exception& e){
    cerr << "RuntimeError: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}


//----------------------------------------------------------------------------
// Implementations
std::string int_to_str(int x)
{
    // represent an integer as a string
    bool is_neg {false};
    if (x < 0){
        is_neg = true;
        x *= -1;
    }

    std::string output {};
    const int char2int = '0';
    
    int tmp {-1};
    char digit {};
    int curr {x};
    
    // use integer division and narrowing to my advantage.
    while (true){
        tmp = curr / 10;
        if (tmp == 0){
            digit = char2int + curr;
            output = digit + output;
            break;
        }
        digit = char2int + (curr - tmp*10);
        output = digit + output;
        curr = tmp;
    }
        
    if (is_neg)
        output = "-" + output;
    return output;
}


vector<string> assoc_ages(const vector<string>& names, const vector<int>& ages)
{
    // Concatenate names and ages in the following format:
    // "<name> <age>"
    // Use the whitespace to signal the switch to digits during printing.
    // My thinking is that the sorting should still sort the names as expected
    if (names.size() != ages.size())
        error("Vector sizes must be equivalent.\n");
    vector<string> concat {};
    for (int i{0}; i < names.size(); ++i)
        concat.push_back(names[i] + ' ' + int_to_str(ages[i]));
    
    return concat;
}

void work(vector<string>& name_ages)
{
    /*
        Oh wait, the string itself is already pair due to the whitespace
        separation. I can just print the strings themselves.
    */

    print(name_ages, "Received:");
    sort(name_ages.begin(), name_ages.end());
    print(name_ages, "Sorted:");
}

void print(const vector <string>& strs, const string& label){
    // prints vector of strings
    cout << '\n' << label << '\n';
    for (string s: strs)
        cout << s << '\n';
}
//----------------------------------------------------------------------------
/*
❯ ./exec/ex07
Bob 17 Julie 24 Stephan 39 Josephine 48 STOP

Received:
Bob 17
Julie 24
Stephan 39
Josephine 48

Sorted:
Bob 17
Josephine 48
Julie 24
Stephan 39
❯ ./exec/ex07
Jesse 50 Jesse 20 Jesse 35 Jesse 15 STOP

Received:
Jesse 50
Jesse 20
Jesse 35
Jesse 15

Sorted:
Jesse 15
Jesse 20
Jesse 35
Jesse 50

*/