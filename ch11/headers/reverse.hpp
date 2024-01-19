#ifndef CH11_REVERSE_HPP_INCLUDED
#define CH11_REVERSE_HPP_INCLUDED

#include "../../std_lib_facilities.h"

void reverse_str_vec(vector<string>&);
string reverse_str(const string&);
string reverse_line(const string& line, bool rev_words);
vector<string> load_rev_lines(ifstream& is, bool rev_words=false);

#endif /* CH11_REVERSE_HPP_INCLUDED */