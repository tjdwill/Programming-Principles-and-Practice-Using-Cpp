#include "../headers/chrono.hpp"

int abs(int x) {return (x < 0) ? -x:x;}

namespace Chrono{

// Constructors
Date::Date()
    : date(0) {}
Date::Date(long int n)
    : date(n)
{
    if (n < 0) throw DateError("Can't have negative date.\n");
}
Date::Date(int y, Month m, int d){
    try{
        validate_date(y, m, d);
    }
    catch(DateError& e){
        throw e;
    }
    date = date_in_days(y, m, d);
}

// Methods
vector<int> Date::today() const{
    return get_date(date);
}

int Date::get_year() const {return today()[0];}

Month Date::get_month() const {
    int month {today()[1]};
    month += int(Month::jan) - 1;
    return Month(month);
}

int Date::get_day() const {return today()[2];}

long int Date::since_default() const {return date;}

void Date::add_day(int n){
    if (n < 0) throw DateError("Only non-negative values supported.\n");
    date += n;
}

void Date::add_month(int n){
    if (n < 0) throw DateError("Only non-negative values supported.\n");
    vector<int> curr_date = today();
    int yr = curr_date[0];
    int month = curr_date[1];
    int day = curr_date[2];

    // full years
    int yrs {n/12};
    yr += yrs;
    n -= yrs*12;

    // partial years
    int till_new_year {12-month};  // Months until Jan
    if (n >= till_new_year) {
        ++yr;
        n -= till_new_year;
    }

    // Leap Year Adjust
    month += n;
    if (int_as_month(month)==Month::feb && day==29 && !is_leap(yr)){
        month = month_as_int(Month::mar);
        day = 1;
    }
    date = date_in_days(yr, int_as_month(month), day);
}
void Date::add_year(int n){
    if (n < 0) throw DateError("Only non-negative values supported.\n");{}
    vector<int> curr_date = today();
    int yr = curr_date[0];
    Month month = int_as_month(curr_date[1]);
    int day = curr_date[2];
    if (month == Month::feb && day == 29 && !is_leap(yr+n)){
        month = Month::mar;
        day = 1;
    }
    yr += n;
    date = date_in_days(yr, month, day);
}

// Exceptions
Date::DateError::DateError(const string& msg)
    : err_msg(msg){}

const string& Date::DateError::what(){
    return err_msg;
}

//----------------------------------------------------------------------------
// Helper Function Implementations
// Get the LOGIC correct first; we'll do invariant checks later.

bool is_leap(const int yr){
    /*
        Leap year every four years except years divisible by 100 but not 400.
    */ 
    return !(yr % 4 || (yr % 100 == 0 && yr % 400));
}

// bool is_leap(const Date& dd) {return is_leap(dd.get_year());}

bool is_centennial(const int yr){return !is_leap(yr) && yr % 100 == 0;}

bool is_new_greg(const int yr) {return is_leap(yr) && yr % 400 == 0;}

void validate_date(int y, Month m, int d){
    /*
        Check year
        Check day
        Check leap year case
    */
   int month {month_as_int(m)};
   if (y < dft_yr) throw Date::DateError("Invalid year.\n");
   if (
        d < 1 ||
        (!is_leap(y) && d > days_in_month[month]) ||
        (is_leap(y) && (
            (m == Month::feb && d>days_in_month[month] + 1) ||
            (m != Month::feb && d > days_in_month[month])))
   ){
        throw Date::DateError("Invalid day.\n");
   }
   return;
}

long int date_in_days(const int y, const Month m, const int d, const int start_yr){
    // Assume we begin from 1 Jan. 
    long int elapsed{};
    elapsed += yr_to_days(y, start_yr);
    elapsed += months_to_days(Month::jan, m);
    if (is_leap(y) && m > Month::feb) ++elapsed;
    elapsed += d - 1;  // adjust for the first day (1 Jan).
    return elapsed;
}

int months_to_days(const Month start, const Month end){
    // Returns how many days have elapsed from 1 <Month 1> *to* 1 <Month 2>
    // Assumes normal 365 day calendar year.
    // Assumes all months are within the same year (only forward movement)
    // Ex. March to May (31 + 30) = 61 days have elapsed.
    
    int days {};
    int m = month_as_int(start); //
    for (int i {m}; i < int(end); ++i) days += days_in_month[i];
    return days;
}

long int yr_to_days(const int yr, const int start_yr){
    /* 
        Given a year `yr`, calculate number of days from 
        1 Jan <default year> to 1 Jan <yr> 
        Assumes yr >= start_yr. 
        For example, yrs_to_days(400, 0) should equal 146,097 days
        (a full Gregorian cycle)
    */
    int days {};
    
    int nleaps {num_leaps(yr, start_yr)};
    int remaining {yr - start_yr};
    days += nleaps * 366;
    remaining -= nleaps;
    days += remaining * 365;
    return days;
}

int num_leaps(int yr, int start_yr){
    // Return the number of leap years from `start_yr` to `yr`.
    // Assumes both years begin 1 Jan.
    /*
        This is a very involved function because it works through multiple
        stages:
        0. Full Gregorian Cycles
        1. Partial Gregorian Cycles
        2. Full Leap Cycles
        3. Partial Leap Cycles

        There are many edge cases to consider in order to get the correct
        behavior; they will be shown in the code.
    */

    constexpr int leaps_per_greg {97};
    constexpr int leaps_per_cent {24};
    constexpr int leaps_per_cycle {1};
    int leaps {};
    int remaining {yr - start_yr};
    int adjusts {}; // for debugging
    int elapsed {};
    int current_yr {start_yr};

    //========================
    // Full Gregorian Cycles
    //========================

    int full_gregs {remaining / one_greg_cycle};
    leaps += full_gregs * leaps_per_greg;
    elapsed = full_gregs * one_greg_cycle;
    remaining -= elapsed;
    current_yr += elapsed;

    //==========================
    // Partial Gregorian Cycles
    //==========================

    /*
        Now we get to edge cases. A partial gregorial cycle is one century
        because centuries are used to determine which leap years to skip. For
        centennials (which I use to mean the years that are divisible by 100
        but not 400), we use the normal 365 day calendar year.

        As a result, for a given centennial, there are 24 leap years. However,
        there is the possiblity that we cross over the beginning of a new
        Gregorian cycle which *is* a leap year. Therefore, this must be taken
        into account in the calculation.

        Also note, at this stage there are at most 399 remaining years.
    */

    int partial_gregs {remaining / 100};
    int till_new {one_greg_cycle - greg_cycle_yr(current_yr)};  // yrs until new cycle
    if (
        partial_gregs*100 > till_new ||  // strictly greater because we need the year to actually pass.
        (is_new_greg(current_yr) && partial_gregs > 0)
    ){
        leaps += 1;
        adjusts += 1;
    }

    leaps += partial_gregs * leaps_per_cent;
    elapsed = partial_gregs * 100;
    current_yr += elapsed;
    remaining -= elapsed;


    //===========================
    // Full Leap (Julian) Cycles
    //===========================

    /*
        Here I look for the normal 4-year leap cycles. However, one caveat is
        that I have to search for centennial years. Becuase full leap cycles
        include leap years every four years, without correction we would have
        an extra day. Instead, for cycles that include centennial years, each
        year has 365 days.

        At this point, remaining years [0, 99].
    */

    int full_leaps {remaining / 4};
    leaps += full_leaps;

    int next_cent {(current_yr + full_leaps*4)/ 100};  // century after applying time skip.
    int this_cent {current_yr/ 100};
    if (
        (full_leaps && is_centennial(current_yr)) ||
        (
            next_cent > this_cent && 
            is_centennial(next_cent*100) && 
            remaining - full_leaps*4 > 0  // is there another year after the time skip?
        )
    ){
        leaps -= 1;
        adjusts += 1;
    }

    elapsed = full_leaps * 4;
    current_yr += elapsed;
    remaining -= elapsed;

    //=====================
    // Partial Leap Cycles
    //=====================
    
    /*
        This is the final stage. Here, we expect the normal 365 day year from
        whatever remains. However, there is the possibility that we cross a
        leap year, so that must be accounted for.

        Maximum Remaining Years: 3
    */

    int partial_leaps {};
    int till_next_leap {yrs_per_leap - current_yr % yrs_per_leap};
    if (
        (remaining > till_next_leap && is_leap(current_yr + till_next_leap)) ||
        (is_leap(current_yr) && remaining > 0)
    ){
        leaps += 1;
        partial_leaps += 1;
        adjusts += 1;
    }

    elapsed = remaining;
    current_yr += elapsed;
    remaining -= elapsed; // % 4; // `remaining % 4` is just `remaining`.
    
    return leaps;
}

int greg_cycle_yr(int yr) {return yr % one_greg_cycle;}

int month_as_int(const Month& m){
    // Return month number where January is number 0. Now, the enumeration
    // start point is irrelevant.
    return int(m) - (int(Month::jan));
}

Month int_as_month(int k){
    int lower {month_as_int(Month::jan)};
    int upper {month_as_int(Month::dec)};
    if (k<lower || k>upper) throw Date::DateError("Invalid month number.\n");
    return Month(k + int(Month::jan));
}

vector<int>yr_from_days(long int days, int start_yr){
    // Returns the year and remaining days {Year, Remaining} Because the
    // remaining days will be 0 <= x <= 365 (leap yr), we can just use ints
    vector<int> data (2);
    int current_yr {start_yr};
    long int remaining {days};

    //========================
    // Full Gregorian Cycles
    //========================
    long int full_gregs {remaining / days_per_gregorian_cycle};
    remaining -= full_gregs * days_per_gregorian_cycle;
    current_yr += full_gregs * one_greg_cycle;

    //==========================
    // Partial Gregorian Cycles
    //==========================
    int till_new {one_greg_cycle - current_yr % one_greg_cycle};
    long int partial_gregs {remaining / days_per_cent};
    if (
        partial_gregs*100 > till_new ||
        (is_new_greg(current_yr) && partial_gregs)
    ){
        // Consume extra day for leap year
        --remaining;    
    }
    current_yr += partial_gregs * 100;
    remaining -= partial_gregs * days_per_cent;

    //==================
    // Full Leap Cycles
    //==================

    long int full_leaps {remaining / days_per_julian_cycle};
    long int next_cent {(current_yr + full_leaps*4)/100};
    long int this_cent {current_yr / 100};
    if (
        (full_leaps && is_centennial(current_yr)) ||
        (
            next_cent > this_cent &&
            is_centennial(next_cent * 100) &&
            remaining - (full_leaps * days_per_julian_cycle) >= days_per_year
        )
    ){
        ++remaining; 
    }
    current_yr += full_leaps * 4;
    remaining -= full_leaps * days_per_julian_cycle;

    //=====================
    // Partial Leap Cycles
    //=====================

    /*
        Walk through this step-by-step. If we can reach the next leap-year, do it.
        If we have enough to advance to the next year (from the leap year), do so.
        Finally, account for normal year time.
    */
    int till_next_leap {yrs_per_leap - current_yr % yrs_per_leap};
    long int days_till_leap {till_next_leap * days_per_year};
    if (is_leap(current_yr)) ++days_till_leap;

    if (remaining >= days_till_leap){
        current_yr += till_next_leap;
        remaining -= days_till_leap;
    }

    if (is_leap(current_yr) && remaining > days_per_year){
        ++current_yr;
        remaining -= days_per_year + 1;
    }

    long int norm_yrs {remaining / days_per_year};
    if (is_leap(current_yr) && norm_yrs) --norm_yrs;
    current_yr += norm_yrs;
    remaining -= norm_yrs * days_per_year;

    if (remaining == days_per_year && !is_leap(current_yr))
        error("<yr_from_days>: Processing Error. Can't have 365 days remaining on non-leap year.\n");
    data[0] = current_yr;
    data[1] = int(remaining);

    return data;
}

vector<int> month_from_days(int days, int yr){

    if (days > days_per_year) error("<month_from_days>: Max Days (365) Exceeded.\n");
    int remaining {days};
    int month = month_as_int(Month::jan);
    vector<int> month_days = days_in_month;
    if (is_leap(yr)) ++month_days[month_as_int(Month::feb)];
    for (int i {month}; i < days_in_month.size(); ++i){
        if (remaining >= month_days[i])
        {
            remaining -= month_days[i];
            ++month;
        }
        else break;
    }
    return vector<int> {month, remaining};  
}

vector<int> get_date(long int days, int start_yr){
    // Get an integer vector representing the date {year, month, day}
    if (days < 0 || start_yr < 0)
        error("<Chrono::get_date>: Negative time not supported.\n");

    int yr {}, month {}, day {1};
    vector<int> temp_data = yr_from_days(days, start_yr);
    yr = temp_data[0];
    temp_data = month_from_days(temp_data[1], yr);
    month = temp_data[0];
    day += temp_data[1];

    return vector<int> {yr, month, day};
}

WeekDay next_workday(const WeekDay& day){
    switch(day){
        case WeekDay::fri: case WeekDay::sat:
            return WeekDay::mon;
        default:
            return WeekDay(int(day) + 1);
    }
}

/*
    TODO: Weekday operations
    https://artofmemory.com/blog/how-to-calculate-the-day-of-the-week/
*/

// Overloads
bool operator==(const Date& a, const Date& b){
    return a.since_default() == b.since_default();
}

bool operator!=(const Date& a, const Date& b){
    return !(a==b);
}

ostream& operator<<(ostream& os, const Date& dd){
    vector<int> date = dd.today();  // {yr, month, day}
    os << '(' 
        << date[0] << ", "
        << date[1]+1 << ", "
        << date[2] << ')'
        << '\n';
    return os;
}

istream& operator>>(istream& is, Date& dd){
    // PPP Ch9.8
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!= '(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
        is.clear(ios_base::failbit);                    // set the fail bit
        return is;
    }
    dd = Date(y, int_as_month(m-1), d);
    // update dd
    return is;
}
} // namespace Chrono
