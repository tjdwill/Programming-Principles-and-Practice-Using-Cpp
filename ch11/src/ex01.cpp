/*
    @title: PPP Ex.11.1
    @author: tjdwill
    @date: 16 January 2024
    @spec: 
        Write a program that reads a text file and converts its input to all lower case, producing a new file.
*/

#include "../../std_lib_facilities.h"

/*
    - Get file name
    - Open file for reading
    - Open new file for writing
    - Read each word. Convert each char to lower case.
    - Write each word to the new file.
    - Clean-up/error handling.
*/

string tolower(string s){
    for (char& x: s)
        x = tolower(x);
    return s;
}

string strip_extension(string s){
    // Can I write a version that begins from the end of the string?
    istringstream in(s);
    ostringstream stripped;
    char curr {};
    while (in >> curr){
        if (curr == '.') break;
        stripped << curr;
    }
    return stripped.str();
}



int main()
try{
    // File setup
    string filename {};

    cout << "Enter file name:\n";
    cin >> filename;

    string lowered_file {strip_extension(filename)+"_lowered.txt"};
    ifstream infile {filename};
    if (!infile) error("Could not open ", filename);
    ofstream outfile {lowered_file};  
    if (!outfile) error("Could not open ", lowered_file);

    // Iterate through the file by line, lower-casing each string
    // Iteration by line was chosen to buffer the amount of writes in a
    // reasonable way.

    // When is the best time to use stringstreams? Do they now replace direct
    // iteration?

    string line {};
    while (true){
        getline(infile, line);
        if (infile.eof()) break;
        else if (!infile) error("File Read Error.\n");

        outfile << tolower(line) << '\n';
    }
}
catch(runtime_error& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...){
    cerr << "Unanticipated error.\n";
    return 2;
}
