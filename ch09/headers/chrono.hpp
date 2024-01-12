/* 
    This file documents the architecture of the Chrono namespace
    as mentioned in PPP Ch.9. 

    Honestly, there are way too many subtleties for getting dates correct in
    terms of dealing with leap years that I would spend way too much time
    trying to understand how to handle. Couple that with the fact that the
    default year is an offset (non-leap-year), that it's untenable; I'm going
    to do my best with an approximation. 

    Simplifying assumption(s):

    - Instead of the 400-year leap-year cycle, I'm going to use a 4-year cycle
    such that 
            num_of_days_per_cycle = (365*3) + 366
*/

#include "../../std_lib_facilities.h"

namespace Chrono{

enum class Month{
    jan, feb, mar, apr, may, jun, jul, aug, sept, oct, nov, dec
};

enum class WeekDay{
    sun, mon, tues, wed, thur, fri, sat
};

const vector<int> days_in_month {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const vector<int> leap_cycle {366, 365, 365, 365};
constexpr int dft_yr {1970};
const Month dft_m = Month::jan;
constexpr int dft_d {1};
constexpr int gregorian_correction {3}; // 3 days every 400 yrs
constexpr int days_per_julian_cycle {365*3 + 366};
constexpr int days_per_gregorian_cycle = days_per_julian_cycle*100 - gregorian_correction;  // 146_097
constexpr int days_per_cent {24 * 366 + 76*365};
constexpr int days_per_year {365};
constexpr int yrs_per_leap {4};

constexpr int one_greg_cycle {400};

//----------------------------------------------------------------------------
class Date{
    public:
        // Exceptions
        class DateError{
            public: 
                DateError(const string&);
                const string& what();
            private:
                string err_msg;
         };
        // Constructors
        Date();
        Date(int n);
        Date(int y, Month m, int d);
        
        // Methods
        vector<int> today() const;
        Month get_month() const;
        int get_year() const;
        int get_day() const;
        long int since_default() const;
        void add_day(int);
        void add_month(int);
        void add_year(int);
    private:
        long int date; // days since default date
};

//----------------------------------------------------------------------------
// Helpers
bool is_leap(const Date&);
bool is_leap(const int);
bool is_centennial(const int);
bool is_new_greg(const int);
void validate_date(int y, Month m, int d);
long int date_in_days(const int y, const Month m, const int d, const int start_yr=dft_yr);
long int yr_to_days(const int yr, const int start_yr=dft_yr);
int months_to_days(const Month, const Month);
int greg_cycle_yr (const int yr);
int num_leaps(int yr, int start_yr = dft_yr);
int month_as_int(const Month&);
Month int_as_month(int);
vector<int> yr_from_days(long int days, int start_yr=dft_yr);
vector<int> month_from_days(int days, int yr);
vector<int> get_date(long int days, int start_yr=dft_yr);
WeekDay next_workday(const WeekDay&);

// Overloads
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
ostream& operator<<(ostream& os, const Date& dd);
istream& operator>>(istream& is, Date& dd);
} // namespace Chrono