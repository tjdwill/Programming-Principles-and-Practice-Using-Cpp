default_yr = 1970

def get_leaps(y, y1=default_yr):
    """Get leaps years between start yr and end yr"""
    # Constants
    leaps_per_greg = 97
    leaps_per_cent = 24  # For non-new cycle centuries
    leaps_per_cycle = 1
    
    leaps = 0
    adjusts = 0
    remaining = y - y1
    if y < y1:
        y, y1 = y1, y
    yr = y1
    
    full_greg = (remaining)//400
    leaps += full_greg * leaps_per_greg
    remaining -= full_greg * 400
    yr += full_greg * 400
    
    # Account for position in greg cycle
    partial_greg = remaining // 100
    till_new = 400 - (yr % 400)
    # IF we pass a new greg cycle, count the leap year.
    # print("Yr:", yr)
    if (
        partial_greg*100 > till_new or
        (is_new_greg(yr) and partial_greg > 0)
    ):
        # print("Passed new Greg cycle.")
        leaps += 1
        adjusts += 1
    
    leaps += partial_greg*leaps_per_cent
    remaining -= partial_greg * 100
    yr += partial_greg * 100
    
    """Normal leap year cycles."""
    # print("Begin normal check: ", yr, remaining)
    full_leaps = remaining // 4
    leaps += full_leaps
    # Check if we touch or cross a centennial.
    next_cent = (yr + full_leaps*4)//100
    this_cent = yr // 100
    if (
        (full_leaps and is_centennial(yr)) or
        (
            next_cent > this_cent and
            is_centennial(next_cent * 100) and
            remaining - full_leaps*4 > 0
        )
    ):
        leaps -= 1
        # print("Leaps Adjust")
        
        
    yr += full_leaps * 4
    remaining -= full_leaps * 4

    # Check where we are in the small leap cycle
    partial_leaps = 0
    till_next_leap = (4 - yr % 4)
    if (
        (remaining > till_next_leap and is_leap(yr+till_next_leap)) or
        (is_leap(yr) and remaining > 0)
    ):
        leaps += 1
        partial_leaps += 1
        adjusts += 1

    remaining -= remaining % 4

    assert remaining == 0
    
    return (
        y1, y, leaps,
        full_greg, partial_greg,
        full_leaps, partial_leaps, adjusts
    )

def is_leap(yr: int) -> bool:
    return not (yr % 4 or (yr % 100 == 0 and yr % 400))

def is_centennial(yr: int) -> bool:
    # Ex. 2100, 2200,
    # non-Ex. 2400
    return (not is_leap(yr)) and yr % 100 == 0

def is_new_greg(yr: int) -> bool:
    return (is_leap(yr) and yr % 400 == 0)

def yrs_to_days(y: int, y1: int = default_yr) -> int:
    if y < y1:
        y, y1 = y1, y
    days = 0
    leaps = get_leaps(y, y1)[2]
    elapsed = y - y1
    # print(elapsed, leaps)
    days += leaps * 366
    elapsed -= leaps
    days += elapsed * 365
    
    return days

def transform_days_date(days: int, start_yr:int = default_yr):
    # Constants
    years_per_greg_cycle = 400
    days_per_greg_cycle = 146097
    days_per_cent = 24*366 + 365*76  # 36524
    days_per_leap = 365*3 + 366  # 1461
    days_per_year = 365
    
    #==================
    # Handle the years
    #==================
    
    yr = start_yr
    remaining = days

    #==================
    # Gregorian Cycles
    #==================
    full_gregs = remaining // days_per_greg_cycle
    remaining -= full_gregs * days_per_greg_cycle
    yr += full_gregs * years_per_greg_cycle

    """
    At this point, we need to do the adjustment for *where* we are in the leap
    cycle. For example, if we land on Y2770 and the target year is 3000, at
    some point, we pass Y2800, the beginning of a new Gregorian cycle and a
    valid leap year.

    We check to see if we pass such a time by calculating where we are within
    the cycle before the centennial checks. We then subtract this value from
    the total num of years in the Greg cycle to determine how many years
    remain. Then, we perform a check to see if we have enough days to pass
    this point. If we do, then we know we have begun a new cycle and must
    adjust accordingly.
    """
    print('')

    till_new = 400 - (yr % 400)
    print(f"Remaining: {remaining}\tend_of_cycle: {till_new}")
    partial_gregs = remaining // days_per_cent
    # check if we touch or pass a new Greg cycle.
    if (
        partial_gregs*100 > till_new or
        (is_new_greg(yr) and partial_gregs)
    ):
        # consume extra day for Leap.
        remaining -= 1
    yr += partial_gregs * 100    
    remaining -= partial_gregs * days_per_cent

    #====================
    # Normal Leap Cycles
    #====================

    # Be sure to account for the current year being a centennial.
    full_leaps = remaining // days_per_leap
    next_cent = (yr + full_leaps*4)//100
    this_cent = yr // 100
    if (
        (full_leaps and is_centennial(yr)) or
        (
            next_cent > this_cent and
            is_centennial(next_cent * 100) and
            remaining - (full_leaps*days_per_leap) >= days_per_year
        )
    ):
        remaining += 1
    yr += full_leaps * 4
    remaining -= full_leaps * days_per_leap
    print("Remaining Check: ", remaining)

    # account for partial leaps
    # Do we cross a leap year within the remaining days?
    
    norm_yrs = remaining // days_per_year

    till_next_leap = (4 - yr % 4)  # Could land on a centennial though, so we check
    days_till_leap = till_next_leap * days_per_year
    
    if (
        (is_leap(yr) and norm_yrs > 0) or
        (is_leap(yr + till_next_leap) and norm_yrs > till_next_leap)
        #(is_leap(yr + till_next_leap) and remaining > days_next_leap + days_per_year)
    ):
        print("Decrement Trigger")
        remaining -= 1
    
    yr += norm_yrs
    remaining -= norm_yrs * days_per_year


    #===================
    # Handle the months
    #===================
    # Pause for now.
    return (start_yr, yr, remaining, days,
        full_gregs, partial_gregs, full_leaps, norm_yrs)
    

# aliases
y2d = yrs_to_days
t2d = transform_days_date

#=======
# Tests
#=======

# Years to Days conversions
# timeanddate.com/date/duration.html
"""
print("\nNumber of days tests.")

print(yrs_to_days(2001))
print(transform_days_date(yrs_to_days(2500)))
for i in range(default_yr+51, default_yr+101):
    print(transform_days_date(yrs_to_days(i)))

print(transform_days_date(yrs_to_days(2400)))
print(transform_days_date(yrs_to_days(2100)))
print(transform_days_date(yrs_to_days(2023)))
print(transform_days_date(yrs_to_days(2000)))
print(transform_days_date(yrs_to_days(1999)))
print(transform_days_date(yrs_to_days(1998)))
print(transform_days_date(yrs_to_days(1971)))
print(transform_days_date(yrs_to_days(29700)))
for i in range(20, 34):
    print(transform_days_date(yrs_to_days(i*100)))
for i in range(default_yr+1, default_yr+51):
    print(transform_days_date(yrs_to_days(i)))

print(transform_days_date(8035,2001))
print(transform_days_date(8035,2000))
print(transform_days_date(8755,2000))
print(transform_days_date(19712))
"""

assert t2d(y2d(2600, 1972), 1972)[2] == 0
assert t2d(y2d(2600, 1972), 1972)[2] == 0
assert t2d(y2d(1905, 1902), 1902)[2] == 0
assert t2d(y2d(1915, 1902), 1902)[2] == 0
assert t2d(y2d(2002, 1902), 1902)[2] == 0
assert t2d(y2d(2005, 1902), 1902)[2] == 0
assert t2d(y2d(2015, 1902), 1902)[2] == 0
assert t2d(y2d(20015, 1902), 1902)[2] == 0
assert t2d(y2d(2415, 1902), 1902)[2] == 0
assert t2d(y2d(1905, 1902), 1902)[2] == 0
assert t2d(y2d(1901, 1899), 1899)[2] == 0
assert t2d(y2d(1900, 1899), 1899)[2] == 0
assert t2d(y2d(2023, 1970), 1970)[2] == 0
assert t2d(y2d(2000, 1970), 1970)[2] == 0
assert t2d(y2d(2004, 1970), 1970)[2] == 0
assert t2d(y2d(2001, 1970), 1970)[2] == 0
assert t2d(y2d(2370, 1970), 1970)[2] == 0
assert t2d(y2d(2371, 1970), 1970)[2] == 0
assert t2d(y2d(2374, 1970), 1970)[2] == 0
assert t2d(y2d(2474, 1970), 1970)[2] == 0
assert t2d(y2d(2470, 1970), 1970)[2] == 0
assert t2d(y2d(2800, 1970), 1970)[2] == 0


