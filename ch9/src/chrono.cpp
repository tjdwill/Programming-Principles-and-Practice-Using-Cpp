#include "../headers/chrono.hpp"

int abs(int x) {return (x < 0) ? -x:x;}

namespace Chrono{

bool is_leap(const int yr){
    /*
        Leap year every four years except years divisible by 100 but not 400.
    */ 
    return !(yr % 4 || (yr % 100 == 0 && yr % 400));
}
bool is_leap(const Date& dd) {return is_leap(dd.get_year());}

int yrs_to_days(const int yr){
    // Given a year `yr`, calculate number of days from 1 Jan <default year>
    // to 1 Jan <yr>
    // Assumes yr >= default
    int days {};
    
    int yrs_remaining {abs(dft_yr - yr)};
    int num_leaps = yrs_remaining / yrs_per_leap;
    days += num_leaps * days_per_julian_cycle;
    yrs_remaining -= num_leaps * yrs_per_leap;


}

int num_leaps(int yr, int start_yr = dft_yr){
    // Returns number of leap years that have elapsed
    // between 1 Jan <start> and 1 Jan <yr>
    if (yr < start_yr){
        int temp {yr};
        yr = start_yr;
        start_yr = temp;
    }

    int leaps = ((yr)/4 - start_yr/4) - get_correction_offset(yr, start_yr);
    /*
        Correct leapyear cases; For example, if yr == 1972, the leap year has not
        elapsed yet, so we can't count it.

        On the other end, if the start_yr *is* a leap year, we want to count it as 
        such. We can see if both start and current are leaps, and start == current, 
        the offset becomes 0.
    */
    if (is_leap(yr)) --leaps;
    if (is_leap(start_yr)) ++leaps;
    return leaps;
}

int get_correction_offset(const int yr, const int start_yr){
    // Get number of leap years to correct the calculation
    // NOTE: every 100 years skips a leap year unless the year is divisible by 400.
    /*
    Example:
        Year: 1970
        Where in the leap-cycle?
        (% 1970 400) -> 370
        
        Corrections?
        (// 370 100) -> 3
        (% 3 4) -> 3
        Subtract 3 years from the number of calculated leap_years
        (// 370 4) -> 92
        (- 92 3) -> 89 

        89 leap years have passed *since (but not including) the start of the cycle*
        Year 1600 (meaning we are at a total of 90 when you include 1600)

        There are 30 more years until the end of the cycle (so 7 more leap years).
        (+ 90 7) -> 97 == leap years in a Gregorian cycle.
    */
    constexpr int skip = 100; // skip one leap year after so many years
    int elapsed = yr - start_yr;
    int full_cycles = elapsed / one_greg_cycle;
    int partial = (elapsed % one_greg_cycle) / skip;
    return full_cycles*gregorian_correction + partial;
}

int greg_cycle_yr(int yr) {return yr % one_greg_cycle;}

} // namespace Chrono