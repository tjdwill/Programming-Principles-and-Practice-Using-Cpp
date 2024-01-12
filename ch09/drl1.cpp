// Drill for Ch.9
// I am tasked with getting each version of "Date" to work.
// I think I'll do so in isolated files rather than doing the 
// header->implementation organization.

#include "../std_lib_facilities.h"


constexpr int jan = 1;
constexpr int feb = 2;
constexpr int december = 12;

struct Date {
	int y;  // year
	int m;  // month in year
	int d;  // day of month
};

Date today;  // uninitialized Date object.
Date tomorrow;
/*
bool is_leapyear(int y){
	if (y < 0) return false;
	return y % 4 == 0;  // leap years are every four years (2000 was a leap year);
}
*/

bool valid_date(int y, int m, int d){
	if (
		(y < 0) ||
		(m < jan || m > december) ||
		(d < 1 || d > 31)
	) 
		return false;
	else 
		return true;
}

void init_day(Date& dd, int y, int m, int d){
	if (!valid_date(y, m, d)) error("Invalid Date.\n");

	dd.y = y;
	dd.m = m;
	dd.d = d;
}


void add_day(Date& dd){
	// No leap year check
	int max_day {31};
	// Rogue constants are fine for this problem.

	switch(dd.m){
	
	case feb:
		max_day = 28;
		break;
	case 4: case 6: case 9: case 11:
		max_day = 30;
		break;
	} // end switch block

	if (dd.d == max_day){
		if (dd.m == december){
			dd.m = jan;
			++dd.y;
		}
		else ++dd.m;
		dd.d = 1;
	}
	else ++dd.d;
}

ostream& operator<<(ostream& os, const Date& dd){
	return os << '(' << dd.y
				<< ',' << dd.m
				<< ',' << dd.d << ')';
}

void f(){
	init_day(today, 1978, 12, 31);
	tomorrow = today;
	add_day(tomorrow);

	cout << "Today: " << today << "\nTomorrow: " << tomorrow << '\n';
}

int main()
try{
	f();
}
catch(exception& e){
	cerr << "Error: " << e.what() << '\n';
}
catch(...){
	cerr << "Unknown Error.\n";
}
