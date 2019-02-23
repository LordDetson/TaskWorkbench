/*
 * Task.h
 *
 *  Created on: 11 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef DATA_CLASSES_TASK_H_
#define DATA_CLASSES_TASK_H_
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#include "Date.h"
using namespace std;

class Task {
private:
	unsigned int taskId;
	string content;
	unsigned int userId;
	Date assignmentDate;
	Date plannedDate;
	Date dateDelivery;
	string notation;
public:
	static const string PATH_TASKS;
	Task();
	Task(unsigned int, string, unsigned int, Date, Date, Date, string);
	Task(const Task&);
	~Task();
	void setTaskId(unsigned int);
	void setContent(string);
	void setUserId(unsigned int);
	void setAssignmentDate(const Date&);
	void setPlannedDate(const Date&);
	void setDateDelivery(const Date&);
	void setNotation(string);
	unsigned int getTaskId();
	string getContent();
	unsigned int getUserId();
	Date& getAssignmentDate();
	Date& getPlannedDate();
	Date& getDateDelivery();
	string getNotation();
	string toString();
	Task& operator=(const Task&);
	friend bool operator<(const Task&, const Task&);
	friend bool operator==(const Task&, const  Task&);
	friend ostream& operator<<(ostream&, Task&);
	friend istream& operator>>(istream&, Task&);
	friend ofstream& operator<<(ofstream&, Task&);
	friend ifstream& operator>>(ifstream&, Task&);

};

#endif /* DATA_CLASSES_TASK_H_ */
