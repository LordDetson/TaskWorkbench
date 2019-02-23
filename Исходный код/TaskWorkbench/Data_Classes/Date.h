/*
 * Date.h
 *
 *  Created on: 11 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef DATA_CLASSES_DATE_H_
#define DATA_CLASSES_DATE_H_
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include  "../Ñontrollers/ControllerIStream.h"
#include "../Screens/ExceptionScreen.h"
using namespace std;

class Date {
private:
	short int day;
	short int month;
	short int year;
public:
	Date();
	Date(short int, short int, short int);
	Date(const Date&);
	~Date();
	void setDay(short int);
	void setMonth(short int);
	void setYear(short int);
	short int getDay();
	short int getMonth();
	short int getYear();
	string toString();
	Date& operator=(const Date&);
	int operator-(const Date&);
	int comparisonDate(const Date&);
	friend bool operator<(const Date&, const Date&);
	friend bool operator==(const Date&, const Date&);
	friend istream &operator>>(istream&, Date&);
	friend ostream &operator<<(ostream&, Date&);
	friend ifstream &operator>>(ifstream&, Date&);
	friend ofstream &operator<<(ofstream&, Date&);
	static Date getTodayDate();
};

#endif /* DATA_CLASSES_DATE_H_ */
