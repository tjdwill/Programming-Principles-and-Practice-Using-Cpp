#include <iostream>

/*
    @author: tjdwill
    @date: 16 February 2024
    @title: PPP Exercise 17.05
        Write a function that finds C-style sub-strings
*/

unsigned int len_str(const char* s)
{
    // Get the length of a C-style string (inc. terminator)
    unsigned int length {};
    if (!s) return length;

    while(*s){
        ++length;
        ++s;
    }
   ++length;  //include terminator
    return length;  
}

char* fs_strdup(const char* s)  // 'fs' prefix to remind myself that the output is on the free store and must be deleted.
{
    // Copies C-style strings
    if (!s) return nullptr;

    unsigned int sz {len_str(s)};
    char* cpy = new char[sz] {};
    for (unsigned int i{}; i < sz; ++i)
    {
        cpy[i] = s[i];
    }

    return cpy;
}


bool is_substring(const char* ss, const char* str)
{
    // Checks to see if the given string ss is a substring of str.
    // This is more of an inner function for the findx function.
    constexpr char TERM_CHAR {'\0'};
    if (!ss || ! str) return false;

    while(*str != TERM_CHAR && *ss != TERM_CHAR)
    {
        if (*str != *ss) return false;
        ++str;
        ++ss;
    }
    // exhaustion: check which condition broke the loop
    if (*str == TERM_CHAR && *ss != TERM_CHAR) return false; // not enough of larger string remaining
    
    return true;  
}

char* findx(const char* parent, const char* ss)
{
    // Find the first occurence of the 'ss' in 'parent'
    unsigned int sz_par {len_str(parent)};
    unsigned int sz_ss {len_str(ss)};
    if ((!parent || !ss) || (sz_ss > sz_par)) 
        return nullptr;

    bool ss_found {false};
    for (unsigned int i {}; i < sz_par; ++i)
    {
        if (is_substring(ss, &parent[i]))
        {
            char* remaining {fs_strdup(&parent[i])};
            return remaining;
        }
            
    }
    return nullptr;
}

int main()
{
    using std::cout;
    char old[] = "Hi, I'm testing my program for copying strings.\n";
    char ss[] = "testing";
    cout << old;
    cout << "Base string length:\t" << len_str(old) << '\n';
    cout << "Desired substring:\t" << ss << '\n';
    // cout << len_str(nullptr) << '\n';

    char* ss_head {findx(old, ss)};
    if (ss_head)
    {
        cout << "\nHere's where we found the sub-string:\n\t";
        cout << ss_head << '\n';
        cout << "Length of reamaining base string:\t" << len_str(ss_head) << '\n';
        delete[] ss_head;
    }
}
    
