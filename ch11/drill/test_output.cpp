/*
    @title: PPP Ch.11 Drill
    @author: tjdwill
    @date: 16 January 2024
*/
#include "../../std_lib_facilities.h"

void cycle_outputs(int j, ostream& os = cout){
    os << showbase
        << j << "\t(decimal)" << '\n'
        << oct << j << "\t(octal)" << '\n'
        << hex << j << "\t(hexadecimal)" << '\n'
        << dec;
}

void cycle_outputs(double j, ostream& os = cout){
    os << '\n'
        << j << "\t(defaultfloat)" << '\n'
        << fixed << j << "\t(fixed)" << '\n'
        << scientific << j << "\t(scientific)" << '\n'
        << defaultfloat;
}

class DataEntry{
    public:
        DataEntry(string last, string first)
            : surname{last}, first_name{first} {}
        DataEntry(string last, string first, string phone, string email)
            : surname{last}, first_name{first}, phone{phone}, email{email} {}

        string get_surname() const {return surname;}
        string get_first_name() const {return first_name;}
        string get_phone() const {return phone;}
        string get_email() const {return email;}
    private:
        string surname;
        string first_name;
        string phone {"+1-555-555-5555"};
        string email {"default_email@some_domain.com"};
};

ostream& operator << (ostream& os, const DataEntry& person){
    constexpr int general_spacing {15};
    constexpr int bar_space {2};
    setw(general_spacing);
    os << person.get_surname() << setw(bar_space) << '|' 
        << person.get_first_name() << setw(bar_space) << '|'
        << person.get_phone() << setw(bar_space) << '|'
        << person.get_email() << setw(bar_space) << '|'
        <<'\n';

    return os;
}

void print_table(const vector<DataEntry>& v, ostream& os=cout){
    for (DataEntry d: v)
        os << d;
}


int main(){
    int birth_year {1979};
    cout << "Representations:\n";
    cycle_outputs(birth_year);

    cout << "\nAge:\n";
    int age {2024-birth_year};
    cycle_outputs(age);

    int a, b, c, d;
    cin >> a >> oct >> b >> hex >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
    

    double test {1234567.89};
    cycle_outputs(test);

    vector<DataEntry> entries{
        DataEntry("Stroustrup", "Bjarne"),
        DataEntry("Knuth", "Donald"),
        DataEntry("Van Rossum", "Guido"),
        DataEntry("DWill", "Tj", "+1-999-546-2517", "fake_email@github.com"),
        DataEntry("Bryant", "Kobe"),
        DataEntry("O'Neal", "Patrice"),
    };
    
    cout << '\n';
    print_table(entries);
}
