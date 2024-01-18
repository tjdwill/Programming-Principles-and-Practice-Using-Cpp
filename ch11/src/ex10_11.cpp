/*
    @title: PPP Ex.11.10, 11
    @author: tjdwill
    @date: 18 January 2024
    @spec: 
        Write a program splits strings
*/

#include "../../std_lib_facilities.h"

string filter(string s, const string& w=""){
    for (char& ch: s)
        for (char ws: w)
            if (ch == ws) ch = ' ';
    return s;
}

vector<string> split(const string& s){
    // Returns a vector of whitespace-separated sub-strings from string s.
    istringstream is {s};
    vector<string> output {};

    for (string ss; is >> ss;)
        output.push_back(ss);

    return output;
}

vector<string> split(const string& s, const string& w){
    return split(filter(s, w));
}


void print_ss(vector<string> ss){
    for (string s: ss)
        cout << s << " ";
    cout << '\n';
}

int main()
try {
    const string stop {"q"};
    string ws {};
    cout << "Insert whitespace string: ";
    cin >> noskipws >> ws;
    if (!cin) cin.clear();

    cout << "\nInsert lines (Enter '" << stop << "' to exit.):\n";
    vector<string> substrs{};
    string line;
    while (cin){
        getline(cin, line);
        if (line == stop) break;
        substrs = split(line, ws);
        print_ss(substrs);
    }
}
catch(runtime_error& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
} 
catch(...) {
    cerr << "Unanticipated error.\n";
    return 2;
}
