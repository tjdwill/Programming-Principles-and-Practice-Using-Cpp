#include "../headers/name_pairs.hpp"

namespace ex02{

const string stop {"STOP"};
constexpr int min_age {0};
// constexpr int max_age {}; // if needed in future.
// Constructors
/* 
I was going to make the default constructor call `update`, but I'm not sure
that's the desirable behavior from the standpoint of a user. I'll just leave
the initalization to a blank state.
*/
NamePairs::NamePairs(){};

NamePairs::NamePairs(const vector<string>& name_list, const vector<int>& age_list)
    : names(name_list), ages(age_list)
{
    if (name_list.size() != age_list.size()) 
        throw InitError{"Names and ages vectors must be same size.\n"};
    
    check_valid(name_list);
        
    if (!is_valid(age_list))
        throw InitError("All ages must be non-negative.\n");
}
//----------------------------------------------------------------------------
// Methods
string NamePairs::InitError::what(){
    return err_msg;
}

void NamePairs::update(){

    try{
        read_names();
        read_ages();
    }
    catch(InitError& e){
        // Handle here if need be and/or propagate forward.
        throw e;
    }
}

void NamePairs::read_names(){
    // Add names from user input
    cout << "Input names (Enter '" << stop << "' to submit):\n";
    
    vector<string> buffer;
    string name {};
    while (cin >> name && name != stop){
        if (can_insert(name, names) && can_insert(name, buffer))
            buffer.push_back(name);
        else
            throw InitError("No duplicate names. Name container unchanged\n");
    }

    // only modify object vector if all inserted names are valid.
    for (string x: buffer){
        names.push_back(x);
    }
    cout << "Updated.\n";
}

void NamePairs::read_ages(){
    // This method only runs if read_names was successful
    vector<int> buffer {};
    cout << "Enter the ages of the newly-added names.\n";
    int age {};
    // Begin at first newly-added name
    for (int i = ages.size(); i < names.size(); ++i){
        cout << names[i] << ": ";
        cin >> age;
        if (!is_valid(age)) throw InitError("Invalid age.\n");
        buffer.push_back(age);
    }
    for (int x: buffer)
        ages.push_back(x);

    // For Testing
    if (ages.size() != names.size())
        throw InitError("Something went wrong adding ages. Sizes mismatched.\n");
}

void NamePairs::print(){
    cout << "\nName Pairs\n";
    for (int i {}; i < names.size(); ++i){
        cout << '(' << names[i] << ", " << ages[i] << ")\n";
    }
}

void NamePairs::sort(){
    vector<string> unsorted_names = names;
    vector<int> ages_copy = ages;
    std::sort(names.begin(), names.end());  // overcome naming collision
    
    string name {};
    for (int i {}; i < names.size(); ++i){
        name = names[i];
        for (int j {}; j < unsorted_names.size(); ++j){
            if (name == unsorted_names[j]){
                ages[i] = ages_copy[j];
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------
// Helpers

bool is_valid(const int& age){
    return age >= min_age;
}

bool is_valid(const vector<int>& ages){
    for (int age: ages)
        if (!is_valid(age)) return false;
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

bool can_insert(const string& str, const vector<string>& strs){
    for (string x: strs){
        if (x == str)
            return false;
    }
    return true;
}

};  // namespace `ex02`