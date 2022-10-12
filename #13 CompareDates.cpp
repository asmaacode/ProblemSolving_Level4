#include<iostream>
#include"myLibrary.h"
using namespace std;
using namespace myLibrary;

bool compareDates(calendar::sDate date1, calendar::sDate date2) {
	if (date1.year > date2.year) return true;
	if (date1.month > date2.month) return true;
	if (date1.day > date2.day) return true;

	return false;
}
int main() {
	cout << "Date1: \n";
	calendar::sDate date1= read::readDate();
	cout << "Date2: \n";
	calendar::sDate date2= read::readDate();
	
	if (compareDates(date1, date2))
		cout << "No, Date1 is greater than Date2";
	else
		cout << "Yes, Date1 is less than Date2";


	return 0;
}
