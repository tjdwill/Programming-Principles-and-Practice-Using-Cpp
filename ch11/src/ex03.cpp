/*
    @title: PPP Ex.11.3
    @author: tjdwill
    @date: 17 January 2024
    @spec: 
        Write a program that removes all vowels from a file ("disemvowels").
        For example, `Once upon a time!` becomes `nc pn tm!`
*/

#include "../../std_lib_facilities.h"

bool is_vowel(char ch){
    ch = tolower(ch);
    string vowels {"aeiou"};
    for (char x: vowels)
        if (ch == x) return true;
    return false;
}

int main()
try{
    string filename {};
    cout << "File Name:\n";
    cin >> filename;
    ifstream infile {filename};
    if (!infile) error("Couldn't open file ", filename);

    char c {};
    infile >> noskipws;
    while (infile >> c){
        if (!is_vowel(c)) cout << c;
    }
    infile.clear();
}
catch(runtime_error& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...){
    cerr << "Unanticipated error.\n";
    return 2;
}
