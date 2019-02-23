/*
 * UserAccount.cpp
 *
 *  Created on: 6 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "UserAccount.h"

const string UserAccount::PATH_USER_ACCOUNTS = "./Resources/UserAccounts.txt";

UserAccount::UserAccount() :
		userId(0), password(""), surname(""), name(""), midname(""), department(
				"") {

}

UserAccount::UserAccount(const UserAccount& obj) :
		userId(obj.userId), password(obj.password), surname(obj.surname), name(
				obj.name), midname(obj.midname), department(obj.department) {

}

UserAccount::UserAccount(unsigned int userId, string password, string surname,
		string name, string midname, string department) :
		userId(userId), password(password), surname(surname), name(name), midname(
				midname), department(department) {

}

UserAccount::~UserAccount() {

}

void UserAccount::setUserId(const unsigned int userId) {
	this->userId = userId;
}

void UserAccount::setPasdword(const string password) {
	this->password = password;
}

void UserAccount::setSurname(const string surname) {
	this->surname = surname;
}

void UserAccount::setName(const string name) {
	this->name = name;
}

void UserAccount::setMidname(const string midname) {
	this->midname = midname;
}

void UserAccount::setDepartment(const string department) {
	this->department = department;
}

unsigned int UserAccount::getUserId() {
	return userId;
}

string UserAccount::getPassword() {
	return password;
}

string UserAccount::getSurname() {
	return surname;
}

string UserAccount::getName() {
	return name;
}

string UserAccount::getMidname() {
	return midname;
}

string UserAccount::getDepartment() {
	return department;
}

string UserAccount::toString() {
	string str;
	str.append("[UserAccount@");
	str.append("userId=");
	str.append(to_string(getUserId()));
	str.append(",password=");
	str.append(getPassword());
	str.append(",surname=");
	str.append(getSurname());
	str.append(",name=");
	str.append(getName());
	str.append(",midname=");
	str.append(getMidname());
	str.append(",department=");
	str.append(getDepartment());
	str.append("]");
	return str;
}

UserAccount& UserAccount::operator=(const UserAccount& obj) {
	this->userId = obj.userId;
	this->password = obj.password;
	this->surname = obj.surname;
	this->name = obj.name;
	this->midname = obj.midname;
	this->department = obj.department;
	return *this;
}

bool operator<(const UserAccount& obj1, const UserAccount& obj2) {
	return (obj1.surname.compare(obj2.surname) < 0 ? true : false);
}

bool operator==(const UserAccount& obj1, const UserAccount& obj2) {
	return obj1.userId == obj2.userId;
}

ostream& operator<<(ostream& stream, UserAccount& obj) {
	stream << setw(10) << right << "ID#: " << obj.userId << "\n"
			<< setw(10) << right << "Фамилия: " << obj.surname << "\n"
			<< setw(10) << right << "Имя: " << obj.name << "\n"
			<< setw(10) << right << "Отчество: " << obj.midname << "\n"
			<< setw(10) << right << "Отдел: " << obj.department << "\n";
	return stream;
}

istream& operator>>(istream& stream, UserAccount& obj) {
	cout<<"Пароль"<<endl;
	obj.password=inputString(stream);
	cout<<"Фамилия"<<endl;
	obj.surname=inputString(stream);
	obj.password=HashPasswordWithSal()(obj.password,obj.surname);
	cout<<"Имя"<<endl;
	obj.name=inputString(stream);
	cout<<"Отчество"<<endl;
	obj.midname=inputString(stream);
	cout<<"Отдел"<<endl;
	obj.department=inputString(stream);
	return stream;
}

ofstream& operator<<(ofstream& fstream, UserAccount& obj) {
	fstream << obj.userId << " " << obj.password << " " << obj.surname << " "
			<< obj.name << " " << obj.midname << " " << obj.department;
	return fstream;
}

ifstream& operator>>(ifstream& fstream, UserAccount& obj) {
	fstream >> obj.userId >> obj.password >> obj.surname >> obj.name
			>> obj.midname >> obj.department;
	return fstream;
}
