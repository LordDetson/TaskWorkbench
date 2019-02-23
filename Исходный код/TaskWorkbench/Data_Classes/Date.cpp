/*
 * Date.cpp
 *
 *  Created on: 11 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "Date.h"

Date::Date() :
		day(0), month(0), year(0) {
}

Date::Date(short int day, short int month, short int year) :
		day(day), month(month), year(year) {
}

Date::Date(const Date& obj) :
		day(obj.day), month(obj.month), year(obj.year) {
}

Date::~Date() {
}

void Date::setDay(short int day) {
	this->day = day;
}

void Date::setMonth(short int month) {
	this->month = month;
}

void Date::setYear(short int year) {
	this->year = year;
}
short int Date::getDay() {
	return this->day;
}

short int Date::getMonth() {
	return this->month;
}

short int Date::getYear() {
	return this->year;
}

string Date::toString() {
	string str;
	str.append("[Date@");
	str.append("day=");
	str.append(to_string(this->day));
	str.append(",month=");
	str.append(to_string(this->month));
	str.append(",year=");
	str.append(to_string(this->year));
	str.append("]");
	return str;
}

Date& Date::operator=(const Date& obj) {
	this->day = obj.day;
	this->month = obj.month;
	this->year = obj.year;
	return *this;
}

int Date::operator-(const Date& obj){
	int countDay = 0;
	countDay = (this->year - obj.year) * 365;
	countDay += (this->month - obj.month) * 31;
	countDay += this->day - obj.day;
	return countDay;
}

int Date::comparisonDate(const Date& obj) {
	if (this->year == obj.year) {
		if (this->month == obj.month) {
			if (this->day == obj.day) {
				return 0;
			} else if (this->day > obj.day) {
				return 1;
			} else if (this->day < obj.day) {
				return -1;
			}
		} else if (this->month > obj.month) {
			return 1;
		} else if (this->month < obj.month) {
			return -1;
		}
	} else if (this->year > obj.year) {
		return 1;
	} else if (this->year < obj.year) {
		return -1;
	}
	return 0;
}

bool operator<(Date& obj1, Date& obj2) {
	return (obj1.comparisonDate(obj2) < 0) ? true : false;
}

bool operator==(Date& obj1, Date& obj2) {
	return (obj1.comparisonDate(obj2) == 0) ? true : false;
}

istream& operator>>(istream& stream, Date& obj) {
	while(true){
		cout << "День" << endl;
		obj.day = inputShortInt(stream);
		cout << "Месяц" << endl;
		obj.month = inputShortInt(stream);
		cout << "Год" << endl;
		obj.year = inputShortInt(stream);
		if (!(obj.day > 0 && obj.day < 32 && obj.month > 0 && obj.month < 13
				&& obj.year > 1)) {
			showExceptionScreen();
		}
		else
			break;
	}
	return stream;
}

ostream& operator<<(ostream& stream, Date& obj) {
	stream << setw(2) << right << obj.day << "." << setw(2) << right
			<< obj.month << "." << setw(4) << right << obj.year;
	return stream;
}

ifstream& operator>>(ifstream& fstream, Date& obj) {
	fstream >> obj.day >> obj.month >> obj.year;
	return fstream;
}

ofstream& operator<<(ofstream& fstream, Date& obj) {
	fstream << obj.day << " " << obj.month << " " << obj.year;
	return fstream;
}

Date Date::getTodayDate(){
	Date todayDate;
	struct tm *tim;
	time_t tt = time(NULL);
	tim = localtime(&tt);
	todayDate.setDay(tim->tm_mday);
	todayDate.setMonth(tim->tm_mon+1);
	todayDate.setYear(tim->tm_year+1900);
	return todayDate;
}
