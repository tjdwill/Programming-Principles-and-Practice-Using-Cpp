#include "../headers/name_pairs.hpp"

namespace ex02{

const string stop {"STOP"};
/* 
I was going to make the default constructor call `update`, but I'm not sure
that's the desirable behavior from the standpoint of a user. I'll just leave
the initalization to a blank state.
*/
NamePairs::NamePairs(){};

NamePairs::NamePairs(const vector<string>& name_list, const vector<int>& age_list)
    : names(name_list), ages(age_list), idx(name_list.size() - 1)
{
    if (name_list.size() != age_list.size()) 
        throw InitError{"Names and ages vectors must be same size.\n"};
    
    check_valid(name_list);
        
    if (!is_valid(age_list))
        throw InitError("All ages must be non-negative.\n");
}

string NamePairs::InitError::what(){
    return err_msg;
}
//----------------------------------------------------------------------------
bool is_valid(const vector<int>& ages){
    for (int age: ages)
        if (age < 0) return false;
    return true;
}

void check_valid(const vector<string>& name_list){
    for (string name: name_list)
        if (name == stop) 
        throw NamePairs::InitError("Cannot have terminating string in list of names.\n");
    
    if (!is_unique(name_list))
        throw NamePairs::InitError("All names must be unique.\n");
}

bool is_unique(vector<string> strs){
    // Determine if every element of the given vector is unique.
    const int sz = strs.size();
    if (sz == 0 || sz == 1)
        return true;
    
    sort(strs);  // any duplicate will be immediately adjacent w/in the vector.
    string str {strs[0]};
    for (int i{}; i < sz - 1; ++i){
        if (str == strs[i+1])
            return false;
        str = strs[i+1];
    }
    return true;
}
};