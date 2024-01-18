/*
    @title: PPP Ex.11.2
    @author: tjdwill
    @date: 16 January 2024
    @spec: 
        Write a program that given a file name and a word outputs each line
        that contains that word together with the line number.
*/

#include "../../std_lib_facilities.h"

/*
    - User input (file name, word)
    - File analysis
        - Track line number
        - Take punctuation into account
        - Account for casing
    - Output to user

    For the string operations, I chose to pass by value in order to use the
    unmodified string for printing.
*/

string remove_punct(string s){
    // Replaces relevant punctuation marks with whitespace
    // static const vector<char> punctuation{'!',}
    for (char& c: s){
        if (!(isalpha(c) && c != '-' && c!= '\''))
            c = ' ';
    }
    return s;
}


string tolower(string s){
    for (char& c: s)
        c = tolower(c);
    return s;
}


bool found_word(
    istringstream& is,
    const string& line,
    const string& word
){
    // Search through the string for the desired word
    string curr_word;
    is.str(tolower(remove_punct(line)));
    // cout << "<found_word> Processing Check: " << is.str() << '\n';
    while (is >> curr_word){
        // cout << curr_word << '\n';
        if (curr_word == word) return true;
    }
    is.clear(); // allow subsequent operations
    return false;
}

//----------------------------------------------------------------------------
int main()
try{
    string filename {};
    string search_word {};
    int line_num {1};
    cout << "File Name:\n";
    cin >> filename;
    cout << "Desired word:\n";
    cin >> search_word;
    string word = tolower(search_word);

    // Manipulation part
    ifstream infile {filename};
    if (!infile) error("Could not open file.\n");
    /*
        Go line by line.
        - For a given line, modify a copy to lower-case every word AND remove
        non-word associated punctuations.
        - Pass modified line to stream.
        - For the given stream, search for the search word. Output line and
          line number if found
    */
    istringstream word_check;
    string curr_line {};
    while (infile){
        getline(infile, curr_line);
        if (found_word(word_check, curr_line, search_word)){
            cout << line_num << ": " << curr_line << '\n';
        }
        ++line_num;
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
