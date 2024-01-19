#include "../headers/reverse.hpp"
#include "../../std_lib_facilities.h"

int main()
try{
    // Get file info
    cout << "Enter file name: ";
    string filename {};
    cin >> filename;
    ifstream infile {filename};
    
    cout << "Reversed file name: " << reverse_str(filename) << '\n';

    vector<string> rev_lines {load_rev_lines(infile, false)};
    reverse_str_vec(rev_lines);
    cout << '\n';
    for (string s: rev_lines)
        cout << s << '\n';
}
catch(runtime_error& e){
    cerr << "Error: " << e.what() << '\n';
    return 1;
} 
catch(...){
    cerr << "Unanticipated error.\n";
    return 2;
}