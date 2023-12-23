#include "../headers/chrono.hpp"


void conversion_test(int yr, Chrono::Month m, int d){
    long int days {Chrono::date_in_days(yr, m, d)};
    vector<int> date = Chrono::get_date(days);
    cout << "Days: " << days << '\t';
    cout << "Date (Y, M, D): (";
    for (int x: date)
        cout << x << ",";
    cout << ")\n";
}

int main()
try{

    cout << "\nDate to days conversion checks.\n"; // Verified using <timeanddate.com>'s duration calculator
    cout << Chrono::date_in_days(400, Chrono::Month::jan, 1, 0) << '\n';  // 146097
    cout << Chrono::date_in_days(2023, Chrono::Month::dec, 21) << '\n';  // 19712
    cout << Chrono::date_in_days(2023, Chrono::Month::jan, 1) << '\n';  // 19358
    cout << Chrono::date_in_days(2970, Chrono::Month::jan, 1) << '\n';  // 365243
    cout << Chrono::date_in_days(3000, Chrono::Month::jan, 1) << '\n';  // 376200

    conversion_test(1978, Chrono::Month::apr, 22);
    conversion_test(2970, Chrono::Month::jul, 15);
    conversion_test(2024, Chrono::Month::feb, 29);
    conversion_test(2024, Chrono::Month::dec, 31);
    conversion_test(2000, Chrono::Month::jan, 7);
    conversion_test(1988, Chrono::Month::aug, 12);

    /*
        Days: 3033	Date (Y, M, D): (1978,4,22,)
        Days: 365438	Date (Y, M, D): (2970,7,15,)
        Days: 19782	Date (Y, M, D): (2024,2,29,)
        Days: 20088	Date (Y, M, D): (2024,12,31,)
        Days: 10963	Date (Y, M, D): (2000,1,7,)
        Days: 6798	Date (Y, M, D): (1988,8,12,)
    */
}
catch(...){
    cerr << "Unanticipated Error.\n";
}