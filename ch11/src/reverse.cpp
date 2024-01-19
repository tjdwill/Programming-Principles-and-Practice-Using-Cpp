/*
    @title: Reverse Functions
    @author: tjdwill
    @date: 19 January 2024
    @description:
        Define herein is a small set of functions that assist with reversing a file.
*/
#include "../headers/reverse.hpp"
#include "../../std_lib_facilities.h"


void reverse_str_vec(vector<string>& v){
    // symmetrically swap element positions
    int size = v.size() / 2;
    int back {};
    string swap_space{};
    for (int i {}; i < size; ++i){
        back = v.size() - i - 1;
        swap_space = v[i];
        v[i] = v[back];
        v[back] = swap_space;
        // swap_space = ""; // For reasoning purposes.
    }
}

string reverse_str(const string& s){
    ostringstream os;
    for (int i = s.size()-1; i >= 0; --i)
        os << s[i];
    return os.str();
}

string reverse_line(const string& line, bool rev_words){
    // load a line into a vector of strings
    vector<string> rev_line{};
    istringstream is {line};
    int count{};
    for (string s; is >> s;){
        if (rev_words) s = reverse_str(s);
        rev_line.push_back(s);
    }

    reverse_str_vec(rev_line);
    
    ostringstream os;
    for (string s: rev_line) os << s << ' ';  // extra ' ' at the end, but I'll take it.
    
    return os.str();
}

vector<string> load_rev_lines(ifstream& is, bool rev_words){
    // loads file in line order, but the each line is reversed.
    if(!is) error("<load_rev_lines>: Invalid file state.\n");
    string line;
    vector<string> file {};
    while (true){
        getline(is, line);
        // cout << "<load_rev_lines>: " << line << '\n';
        if (!is){
            if (is.eof()) break;
            else error("File read error.\n");
        }
        file.push_back(reverse_line(line, rev_words));
    }
    return file;
}
