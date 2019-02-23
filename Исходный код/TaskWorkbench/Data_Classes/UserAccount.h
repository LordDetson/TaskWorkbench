/*
 * UserAccount.h
 *
 *  Created on: 6 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef DATA_CLASSES_USERACCOUNT_H_
#define DATA_CLASSES_USERACCOUNT_H_
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Ñonverters/HashPasswordWithSal.h"
#include "../Ñontrollers/ControllerIStream.h"
using namespace std;

class UserAccount {
private:
	unsigned int userId;
	string password;
	string surname;
	string name;
	string midname;
	string department;
public:
	static const string PATH_USER_ACCOUNTS;
	UserAccount();
	UserAccount(const UserAccount&);
	UserAccount(unsigned int, string, string, string, string, string);
	~UserAccount();

	void setUserId(const unsigned int);
	void setPasdword(const string password);
	void setSurname(const string surname);
	void setName(const string name);
	void setMidname(const string midname);
	void setDepartment(const string department);
	unsigned int getUserId();
	string getPassword();
	string getSurname();
	string getName();
	string getMidname();
	string getDepartment();
	string toString();
	UserAccount& operator=(const UserAccount&);
	friend bool operator<(const UserAccount&, const UserAccount&);
	friend bool operator==(const UserAccount&, const UserAccount&);
	friend ostream& operator<<(ostream&, UserAccount&);
	friend istream& operator>>(istream&, UserAccount&);
	friend ofstream& operator<<(ofstream&, UserAccount&);
	friend ifstream& operator>>(ifstream&, UserAccount&);
};

#endif /* DATA_CLASSES_USERACCOUNT_H_ */
