/*
*    @author: tjdwill
*    @date: 6 February 2024
*    @title: Custom String Immplementation
*        Trying to program my own version of a string class. Non-C-style. I'll have to refactor to make it better organized.
*/


#include <iostream>
#include <string>

// constexpr unsigned int MAX_INT {4294967295};
constexpr unsigned int MAX_INT {10000000};
class string{
    unsigned int sz {};
    char* str {}; // nullptr

    public:
        // Constructors
        string(){}

        string(unsigned int sz0, char* s)
            :sz{sz0}
        {
            str = new char[sz];
            for (unsigned int i{}; i<sz; ++i)
                str[i] = s[i];
        }

        string(const string& s)
            : sz(s.len())
        {
            if (s.str)
            {
                str = new char[sz];
                for(unsigned int i{}; i<sz; ++i)
                    str[i] = s.str[i];
            }
            // how can I make the empty string one unique object?
        }

        string(const string& s0, const string& s1)
            :sz{s0.len() + s1.len()}
        {
            str = new char[sz];
            // fill the string with the two strings
            unsigned int sz0 = s0.len();
            for (unsigned int i{}; i<sz0; ++i)
                str[i] = s0.str[i];                    
            for (unsigned int j {sz0}; j<sz; ++j)
                str[j] = s1.str[j - sz0];
        }
        
        string& operator=(const string& s){
            string copy = string(s);
            string& ref = copy;
            return ref;
        }

        // Destructor
        ~string(){delete[] str;}

        // Methods
        unsigned int len() const {return sz;}
        const char* view_copy() const {return str;}
};

string exp_append(const string& s, unsigned int times){
    // exponential appends
    if (times == 0) return string(s);
    return exp_append(string(s, s), times-1);
}

string multi_append_iter(const string& add_token,const string& curr, unsigned int times){
    // multiple appends of string s.
    if (times == 0) return string(curr);
    return multi_append_iter(add_token, string(curr, add_token), times-1);
}

string multi_append(const string& s, unsigned int times){
    //return multi_append_iter(s, string(), times);
    return multi_append_iter(s, s, times);
}

std::ostream& operator<< (std::ostream& os, const string& s)
{
    const char* cpy {s.view_copy()};
    for (unsigned int i{}; i<s.len(); ++i)
        os << cpy[i];
    return os;
}

void print_str(const string& s)
{
    using std::cout;
    cout << s << '\n';
}


int main()
{

    char s[] = {'h', 'o', 'u', 'r'};
    string test(4, s);
    string t2 = string(test, test);
    string t3 = string(string(), string());
    print_str(test);
    print_str(t2);
    print_str(t3);
    print_str(multi_append(t2, 10));
    print_str(exp_append(test, 3));
    // Test multiple allocations
    unsigned int count {};
    while (count < MAX_INT)
    {
        string();
        ++count;        
    }
    std::cout << "Num String allocs: " << count << '\n';
    return 0;
}
