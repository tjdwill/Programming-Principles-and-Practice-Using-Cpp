/*
    @title: PPP Ch11.12
    @author: tjdwill
    @date: 19 January 2024
    @spec:
        Reverse the order of characters in a text file.
*/
#include "../headers/reverse.hpp"
#include "../../std_lib_facilities.h"

//----------------------------------------------------------------------------
string strip_extension(string s){
    istringstream in(s);
    ostringstream stripped;
    char curr {};
    while (in >> curr){
        if (curr == '.') break;
        stripped << curr;
    }
    return stripped.str();
}
//----------------------------------------------------------------------------
int main()
try{
    // Get file info
    cout << "Enter file name: ";
    string filename {};
    cin >> filename;
    ifstream infile {filename};
    if (!infile) error("Could not open file ", filename);
    string outfile {strip_extension(filename) + "_fullrev.txt"};
    ofstream of {outfile};
    if (!of) error("Could not open file ", outfile);

    // Operate on file
    vector<string> rev_lines {load_rev_lines(infile, true)};
    reverse_str_vec(rev_lines);

    for (string s:rev_lines)
        of << s << '\n';

    cout << "Done.\n";
}
catch(runtime_error& e){
    cerr << "Error: " << e.what() << '\n';
    return 1;
} 
catch(...){
    cerr << "Unanticipated error.\n";
    return 2;
}
