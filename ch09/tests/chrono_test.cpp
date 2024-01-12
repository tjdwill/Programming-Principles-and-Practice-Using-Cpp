#include "../headers/chrono.hpp"


void conversion_test(int yr, Chrono::Month m, int d){
    long int days {Chrono::date_in_days(yr, m, d)};
    
    cout << "Days: " << days << '\t';
    cout << "Date (Y, M, D): " << Chrono::Date(days);
}

int main()
try{

    cout << "\nDate to days conversion checks.\n"; // Verified using <timeanddate.com>'s duration calculator
/*
    cout << Chrono::date_in_days(400, Chrono::Month::jan, 1, 0) << '\n';  // 146097
    cout << Chrono::date_in_days(2023, Chrono::Month::dec, 21) << '\n';  // 19712
    cout << Chrono::date_in_days(2023, Chrono::Month::jan, 1) << '\n';  // 19358
    cout << Chrono::date_in_days(2970, Chrono::Month::jan, 1) << '\n';  // 365243
    cout << Chrono::date_in_days(3000, Chrono::Month::jan, 1) << '\n';  // 376200
    cout << Chrono::Date();
*/
    conversion_test(1978, Chrono::Month::apr, 22);
    conversion_test(2970, Chrono::Month::jul, 15);
    conversion_test(2024, Chrono::Month::feb, 29);
    conversion_test(2024, Chrono::Month::dec, 31);
    conversion_test(2000, Chrono::Month::jan, 7);
    conversion_test(1988, Chrono::Month::aug, 12);
    conversion_test(2024, Chrono::Month::mar, 1);
    conversion_test(2023, Chrono::Month::mar, 1);
    /*
        OUTPUT
        Days: 3033	    Date (Y, M, D): (1978, 4, 22)
        Days: 365438	Date (Y, M, D): (2970, 7, 15)
        Days: 19782	    Date (Y, M, D): (2024, 2, 29)
        Days: 20088	    Date (Y, M, D): (2024, 12, 31)
        Days: 10963	    Date (Y, M, D): (2000, 1, 7)
        Days: 6798	    Date (Y, M, D): (1988, 8, 12)
        Days: 19783	    Date (Y, M, D): (2024, 3, 1)
        Days: 19417	    Date (Y, M, D): (2023, 3, 1)
    */

    Chrono::Date input;
    cout << "Insert a Date '(yyyy, m, d)': ";
    cin >> input;

    cout << '\n';
    cout << "Received: " << input << '\n';
    cout << "\nModifications\n";
    input.add_day(3);
    cout << input;

    input.add_month(13);
    cout << input;
    input.add_year(30);
    cout << input;

    /*
        OUTPUT
        Insert a Date '(yyyy, m, d)': (2000, 1, 26)           

        Received: (2000, 1, 26)


        Modifications
        (2000, 1, 29)  // +3 days
        (2001, 3, 1)  // +13 months
        (2031, 3, 1)  // +30 years
        ----
        Insert a Date '(yyyy, m, d)': (2000, 1, 26)           

        Received: (2000, 1, 26)


        Modifications
        (2000, 1, 29)  // +3 days
        (2001, 3, 1)   // +13 months
        (2031, 3, 1)   // +30 years
    */

}
catch(Chrono::Date::DateError& e){
    cerr << e.what() << '\n';
}
catch(...){
    cerr << "Unanticipated Error.\n";
}
