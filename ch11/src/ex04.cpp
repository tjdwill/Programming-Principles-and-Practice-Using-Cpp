/*
    @title: PPP Ex.11.4
    @author: tjdwill
    @date: 16 January 2024
    @spec: 
        Play with inputting hexadecimal values.
*/

#include "../../std_lib_facilities.h"

constexpr int dec_code = 0;
constexpr int oct_code = 1;
constexpr int hex_code = 2;
constexpr int fail_code = -1;

vector<int> classify_int(const string& num){
    // Outputs the base system of the number.
    constexpr int min_size {2};
    int test_num{};
    int out_code {fail_code};
    istringstream num_stream;
    
    // allow all integer formats
    num_stream.unsetf(ios::dec);
    num_stream.unsetf(ios::oct);
    num_stream.unsetf(ios::hex);
    num_stream.str(num);

    if (num_stream >> test_num)
    {
        out_code = dec_code;  // Decimal by default
        if (num.size() >= min_size && num[0] == '0')
        {
            out_code = oct_code;
            if (tolower(num[1]) == 'x') out_code = hex_code;
        }
    }
    else num_stream.clear();
    return vector<int> {out_code, test_num};
}

void print_num(const string& str){
    // I can print the string directly regardless of integer format.
    constexpr int default_space {4};
    const int base_space = string {"hexadecimal"}.size();
    cout << setw(default_space);

    vector<int> classified_num = classify_int(str);
    switch(classified_num[0])
    {
        case dec_code:
            cout << str << ' ' << setw(base_space) 
                << "decimal" << " converts to "
                << classified_num[1] << " decimal\n";
            break;

        case oct_code:
            cout << str << ' ' << setw(base_space) 
                    << "octal" << " converts to "
                    << classified_num[1] << " decimal\n";
            break;

        case hex_code:
            cout  << str << ' ' << setw(base_space) 
                    << "hexadecimal" << " converts to "
                    << classified_num[1] << " decimal\n";
            break;

        default:
            break;
    }
}
//----------------------------------------------------------------------------
int main()
try{
    const string stop {"STOP"};
    int num;
    string num_str{};
    istringstream num_stream;

    cout << "Enter '" << stop << "' to exit.\n";
    cout << "Insert numbers (hex, dec, or oct):\n";
    
    while (cin >> num_str){
        if (num_str == stop) break;
        print_num(num_str);
    }
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

/*
//=============
// Program Run
//=============

Enter 'STOP' to exit.
Insert numbers (hex, dec, or oct):
0x43 0123 65 test 7543 STOP
0x43 hexadecimal converts to 67 decimal
0123       octal converts to 83 decimal
  65     decimal converts to 65 decimal
7543     decimal converts to 7543 decimal

*/