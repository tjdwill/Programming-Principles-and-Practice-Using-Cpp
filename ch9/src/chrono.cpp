#include "../headers/chrono.hpp"

int abs(int x) {return (x < 0) ? -x:x;}

namespace Chrono{


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

long int date_in_days(const int d, const Month m, const int y, const int start_yr){
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
    for (int i = int(start); i < int(end); ++i) days += days_in_month[i];
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
    */;

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

    int full_greg {remaining / one_greg_cycle};
    leaps += full_greg * leaps_per_greg;
    elapsed = full_greg * one_greg_cycle;
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

    int partial_greg {remaining / 100};
    int till_new {one_greg_cycle - greg_cycle_yr(current_yr)};  // yrs until new cycle
    if (
        partial_greg*100 > till_new ||  // strictly greater because we need the year to actually pass.
        (is_new_greg(current_yr) && partial_greg > 0)
    ){
        leaps += 1;
        adjusts += 1;
    }

    leaps += partial_greg * leaps_per_cent;
    elapsed = partial_greg * 100;
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

} // namespace Chrono