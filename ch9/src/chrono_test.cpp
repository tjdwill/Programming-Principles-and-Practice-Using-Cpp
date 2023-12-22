#include "../headers/chrono.hpp"

int main()
try{

    cout << "\nDate to days conversion checks.\n"; // Verified using <timeanddate.com>'s duration calculator
    cout << Chrono::date_in_days(1, Chrono::Month::jan, 400, 0) << '\n';  // 146097
    cout << Chrono::date_in_days(21, Chrono::Month::dec, 2023) << '\n';  // 19712
    cout << Chrono::date_in_days(1, Chrono::Month::jan, 2023) << '\n';  // 19358
    cout << Chrono::date_in_days(1, Chrono::Month::jan, 2970) << '\n';  // 365243
    cout << Chrono::date_in_days(1, Chrono::Month::jan, 3000) << '\n';  // 376200
}
catch(...){
    cerr << "Unanticipated Error.\n";
}