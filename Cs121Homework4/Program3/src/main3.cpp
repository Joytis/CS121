#include <iostream>
#include <vector>
#include <string>

using namespace std;

unsigned int leap(unsigned int year);
unsigned int days_in_month(unsigned int month, unsigned int year);
bool valiDATE(unsigned int month, unsigned int day, unsigned int year);

int main() {
	uint32_t month;
	uint32_t day;
	uint32_t year;

	cout << "Please enter date of year (MM DD YYYY): ";
	cin >> month >> day >> year;

	while (!valiDATE(month, day, year)) {
		cout << "Please enter the month, day and year like MM DD YYYY." << endl;
		cin >> month >> day >> year;
	};

	for(unsigned int i = 1; i < month; i++) {
		day += days_in_month(i, year); 
	}

	cout << "Julian date: " << day << '.' << year << endl;

}

unsigned int leap(unsigned int year)
{
	if (year % 400 == 0)
		return 1;
	else if(year % 100 != 0 && year % 4 == 0)
		return 1;
	else 
		return 0;
}

unsigned int days_in_month(unsigned int month, unsigned int year){
	
	unsigned int days = 0;
	
	if (month == 2) {
		days = 28 + leap(year);  // function leap returns 1 for leap years
	}
	else if ( month == 4 || month == 6 || month == 9 || month == 11) {
		days = 30;
	}
	else {
		days = 31;
	}

	return days;
}

bool valiDATE(unsigned int month, unsigned int day, unsigned int year) {
	unsigned int days = 0;

	// Validate the month first

	if (month < 1 || month > 12) {
		cout << "Value for month (MM) is out of range." << endl;
		return false;
	}

	// Validate the day of month

	days = days_in_month(month, year);

	if ( day < 1 || day > days) {
		cout << "Value for day (DD) is out of range." << endl;
		return false;
	}

	// Validate the year

		if (year < 1990 || year > 2020) {
		cout << "Value for year (YYYY) is out of range." << endl;
		return false;
	}

	return true;

} 




