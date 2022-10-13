#include<iostream>
#include"myLibrary.h"
using namespace std;
using namespace myLibrary;

int getDiffrenceDays(calendar::sDate  date1,calendar::sDate date2,bool includingEndDay=false) {

	int counter = (includingEndDay ? 1 : 0);
	while (calendar::isDate1LessThanDate2(date1, date2)) {
		counter++;
		date1 = calendar::addOneDayToDate(date1);
	}

	return counter;
} 

int main() {
	cout << "Date1 :\n";
	calendar::sDate date1 = read::readDate();
	cout << "Date2 :\n";
	calendar::sDate date2 = read::readDate();

	cout << "Diffrence is " << getDiffrenceDays(date1,date2) << " Day(s).";
	cout << "\n\n";
	cout << "Diffrence is (Including End Day) " << getDiffrenceDays(date1,date2,true)<<" Day(s).";
	cout << "\n\n";
	return 0;
}
