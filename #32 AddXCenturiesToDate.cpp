#include<iostream>
#include"myLibrary.h"
using namespace std;
using namespace myLibrary;


calendar::sDate increaseDateByXCentury(calendar::sDate date, short centuries)
{
	date.year += (100 * centuries);
	return date;
}

int main() {
	calendar::sDate date;
	date = read::readDate();
	short centuries = read::readPositiveNumberMsg("Enter the number of centuries to add :");
	date = increaseDateByXCentury(date, centuries);
	cout << "\n\nThe date after " << centuries << " centuries " << date.day << "/" << date.month << "/" << date.year << "\n\n";
	return 0;
}
