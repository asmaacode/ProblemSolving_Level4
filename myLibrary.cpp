#pragma once
#pragma warning(disable : 4996) 
#include<ctime> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
namespace myLibrary {
	void swap(int& A, int& B) {
		int temp = A;
		A = B;
		B = temp;
	}
	void swap(int* A, int* B) {
		int temp = *A;
		*A = *B;
		*B = temp;
	}
	bool doYouQuestion(string msg) {
		char answer = 'N';
		cout << msg << "[Y / N]";
		cin >> answer;
		return ((answer == 'Y' || answer == 'y') ? true : false);
	}
	namespace calendar {
		struct sDate { short year;short month;short day; };
		short getThisYear() {
			time_t t = time(0);
			tm* now = localtime(&t);
			return now->tm_year + 1900;
		}
		short getThisMonth() {
			time_t t = time(0);
			tm* now = localtime(&t);
			return now->tm_mon + 1;
		}
		short getThisDay() {
			time_t t = time(0);   //
			tm* now = localtime(&t);
			return  now->tm_mday;
		}
		short getThisHour() {
			time_t t = time(0);   //
			tm* now = localtime(&t);
			return now->tm_hour;
		}
		sDate getSystemDate() {
			sDate today;
			today.day = getThisDay();
			today.month = getThisMonth();
			today.year = getThisYear();
			return today;
		}
		
		bool isLeapYear(short year) {
			return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
		}
		short countDaysInYear(short year) {
			return (isLeapYear(year)) ? 366 : 365;
		}
		short countHoursInYear(short year) {
			return countDaysInYear(year) * 24;
		}
		int countMinutesInYear(short year) {
			return countDaysInYear(year) * 60;
		}
		int countSecondsInYear(short year) {
			return countDaysInYear(year) * 60;
		}
		short countDaysInMonth(short year, short month) {
			if (month < 1 || month > 12) return 0;
			short days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
			return (month == 2) ? (isLeapYear(year) ? 29 : 28) : days[month];
		}
		short countHoursInMonth(short year, short month) {
			return countDaysInMonth(year, month) * 24;
		}
		int countMinutesInMonth(short year, short month) {
			return countHoursInMonth(year, month) * 60;
		}
		int countSecondsInMonth(short year, short month) {
			return countMinutesInMonth(year, month) * 60;
		}

		string getWeekDayName(short dayOrder) {
			string weekDays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
			return weekDays[dayOrder];
		}
		string getMonthName(short& month) {
			string monthsNames[] = { "","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
			return monthsNames[month];
		}

		short getOrderWeekDayOfDate(short day, short month, short year) {
			short a = floor((14 - month) / 12);
			short y = year - a;
			short m = month + 12 * a - 2;
			short d = day + y + floor(y / 4) - floor(y / 100) + floor(y / 400) + floor(31 * m / 12);
			//short d = 5 + day + y + floor(y / 4) + floor(31 * m / 12);
			d = d % 7;
			return d;
		}
		short getOrderWeekDayOfDate(sDate date) {
			return getOrderWeekDayOfDate(date.day,date.month,date.year);
		}

		short countDaysFromBeginingOfYear(short& year, short& month, short day) {
			for (short i = 1;i < month;i++) {
				day += countDaysInMonth(year, i);
			}
			return day;
		}
		short countDaysFromBeginingOfYear(sDate date) {
			for (short i = 1;i < date.month;i++) {
				date.day += countDaysInMonth(date.year, i);
			}
			return date.day;
		}

		bool isDate1LessThanDate2(sDate date1, sDate date2) {
			return (date1.year < date2.year) ? true :
				(date1.year == date2.year) ? (date1.month < date2.month) ? true :
				(date1.month == date2.month) ? (date1.day < date2.day) : false : false;
		}
		bool isDate1EqualDate2(sDate date1, sDate date2) {
			return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day;
		}
		bool isLastDayInMonth(sDate date) {
			return date.day == countDaysInMonth(date.year, date.month);
		}
		bool isLastMonthInYear(short month) {
			return month == 12;
		}

		sDate increaseDateByOneDay(sDate date) {
			if (isLastDayInMonth(date)) {
				if (isLastMonthInYear(date.month)) {
					date.year++;
					date.month = 1;
				}
				else {
					date.month++;
				}
				date.day = 1;
			}
			else {
				date.day++;
			}
			return date;
		}
		void swapDates(sDate& date1, sDate& date2) {
			sDate Temp = date1;
			date1 = date2;
			date2 = Temp;
		}
		int getDifferenceDays(sDate  date1, sDate date2, bool includingEndDay = false) {

			int counter = (includingEndDay ? 1 : 0);
			short swapFlag = 1;
			if (!isDate1LessThanDate2(date1, date2)) {
				swapFlag = -1;
				swapDates(date1, date2);
			}

			while (isDate1LessThanDate2(date1, date2)) {
				counter++;
				date1 = increaseDateByOneDay(date1);
			}

			return counter * swapFlag;
		}

		sDate addDays(sDate date, short days) {
			short remainingDays = days + countDaysFromBeginingOfYear(date.year, date.month, date.day);
			date.month = 1;
			short monthDays;
			while (true) {
				monthDays = countDaysInMonth(date.year, date.month);

				if (remainingDays > monthDays) {
					remainingDays = remainingDays - monthDays;
					date.month++;
					if (date.month > 12) {
						date.month = 1;
						date.year++;
					}
				}
				else {
					date.day = remainingDays;
					break;
				}

			}
			return date;
		}
		sDate increaseDateByXDay(sDate date, short days) {
			for (short i = 1;i <= days;i++) {
				date = increaseDateByOneDay(date);
			}
			return date;
		}
		sDate increaseDateByOneWeek(sDate date)
		{
			for (short i = 1;i <= 7;i++) {
				date = increaseDateByOneDay(date);
			}
			return date;
		}
		sDate increaseDateByXWeek(sDate date, short weeks)
		{
			for (short i = 1;i <= weeks;i++) {
				date = increaseDateByOneWeek(date);
			}
			return date;
		}
		sDate increaseDateByOneMonth(sDate date)
		{
			if (date.month >= 12)
			{
				date.month = 1;
				date.year++;
			}
			else {
				date.month++;
			}

			short days = countDaysInMonth(date.year, date.month);
			if (days < date.day) {
				date.day = days;
			}
			return date;
		}
		sDate increaseDateByXMonth(sDate date, short months)
		{
			for (int i = 1; i <= months;i++) {
				date = increaseDateByOneMonth(date);
			}
			return date;
		}
		sDate increaseDateByOneYear(sDate date)
		{
			date.year++;
			return date;
		}
		sDate increaseDateByXYear(sDate date, short years)
		{
			date.year += years;
			return date;
		}
		sDate increaseDateByOneDecade(sDate date)
		{
			date.year += 10;
			return date;
		}
		sDate increaseDateByXDecade(sDate date, short decades)
		{
			date.year += (10 * decades);
			return date;
		}
		sDate increaseDateByOneCentury(sDate date)
		{
			date.year += 100;
			return date;
		}
		sDate increaseDateByOneMillennium(sDate date)
		{
			date.year += 1000;
			return date;
		}

		sDate decreaseDateByOneDay(sDate date) {
			if (date.day == 1) {
				if (date.month == 1) {
					date.year--;
					date.day = 31;
					date.month = 12;
				}
				else {
					date.month--;
					date.day = countDaysInMonth(date.year, date.month);
				}
			}
			else {
				date.day--;
			}
			return date;
		}
		sDate decreaseDateByXDay(sDate date, short days) {
			for (short i = 1;i <= days;i++) {
				date = decreaseDateByOneDay(date);
			}
			return date;
		}
		sDate decreaseDateByOneWeek(sDate date)
		{
			for (short i = 1;i <= 7;i++) {
				date = decreaseDateByOneDay(date);
			}
			return date;
		}
		sDate decreaseDateByXWeek(sDate date, short weeks)
		{
			for (short i = 1;i <= weeks;i++) {
				date = decreaseDateByOneWeek(date);
			}
			return date;
		}
		sDate decreaseDateByOneMonth(sDate date)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.year--;
			}
			else {
				date.month--;
			}

			short days = countDaysInMonth(date.year, date.month);
			if (days < date.day) {
				date.day = days;
			}
			return date;
		}
		sDate decreaseDateByXMonth(sDate date, short months)
		{
			for (int i = 1; i <= months;i++) {
				date = decreaseDateByOneMonth(date);
			}
			return date;
		}
		sDate decreaseDateByOneYear(sDate date)
		{
			date.year--;
			return date;
		}
		sDate decreaseDateByXYear(sDate date, short years)
		{
			date.year -= years;
			return date;
		}
		sDate decreaseDateByOneDecade(sDate date)
		{
			date.year -= 10;
			return date;
		}
		sDate decreaseDateByXDecade(sDate date, short decades)
		{
			date.year -= (10 * decades);
			return date;
		}
		sDate decreaseDateByOneCentury(sDate date)
		{
			date.year -= 100;
			return date;
		}
		sDate decreaseDateByOneMillennium(sDate date)
		{
			date.year -= 1000;
			return date;
		}
	}
	namespace read {
		int readNumber() {
			int userNumber = 0;
			cin >> userNumber;
			while (cin.fail())
			{
				// Explain error
				cout << "ERROR: A Number must be entered:\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> userNumber;
			}
			return  userNumber;
		}
		float readFloatNumber() {
			float userNumber = 0;
			while (!(cin >> userNumber))
			{
				// Explain error
				cout << "ERROR: A Number must be entered:\n";
				cin.clear();
				cin.ignore(132, '\n');
			}
			return  userNumber;
		}
		int readPositiveNumber() {
			int positiveNumber = 0;
			do {
				cout << "Please enter a number greater than zero :\n";
				positiveNumber = readNumber();
			} while (positiveNumber <= 0);

			return positiveNumber;
		}
		int readPositiveNumberMsg(string msg) {
			int positiveNumber = 0;
			do {
				cout << msg;
				positiveNumber = readNumber();
			} while (positiveNumber < 0);

			return positiveNumber;
		}
		int readNumberMsg(string msg) {
			int number = 0;
			cout << msg << " ";
			number = readNumber();
			return number;
		}
		float readFloatNumberMsg(string msg) {
			float number = 0.0;
			cout << msg;
			number = readFloatNumber();
			return number;
		}
		string readText(string message) {
			string txt = "";
			cout << message;
			getline(cin, txt);
			return  txt;
		}
		char readChar(string message) {
			char txt = ' ';
			cout << message << "\n";
			cin >> txt;
			return  txt;
		}
		int readNumberInRangeMsg(string msg, int from, int to) {
			int number = 0;
			do {
				cout << msg;
				number = readNumber();
			} while (number > to || number < from);

			return number;
		}
		calendar::sDate readDate() {
			calendar::sDate date;
			date.day = read::readNumberInRangeMsg("Please enter a day :", 1, 31);
			cout << "\n";
			date.month = read::readNumberInRangeMsg("Please enter a month :", 1, 12);
			cout << "\n";
			date.year = read::readPositiveNumberMsg("Please enter a year :");
			cout << "\n";
			return date;
		}
	}
	namespace draw {
		string generateLine(short length = 0, char symbol = '_') {
			string line = "";
			while (length != 0) {
				line += symbol;
				length--;
			}
			return line;
		}
		string generateTabs(short length = 0) {
			string tabs = "";
			while (length != 0) {
				tabs += " ";
				length--;
			}
			return tabs;
		}
	}
	namespace manipulators {
		vector<string> split(string& s, string delimiter = " ") {
			vector<string> words;
			int currentIndex = 0;
			string word = "";
			s = s + delimiter;
			while ((currentIndex = s.find(delimiter)) != s.npos) {
				word = s.substr(0, currentIndex);
				s.erase(0, currentIndex + delimiter.length());
				if (word != "" && word != delimiter)
					words.push_back(word);
			}
			return words;
		}
	}
}
