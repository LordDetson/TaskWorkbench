/*
 * Task.cpp
 *
 *  Created on: 11 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "Task.h"

const string Task::PATH_TASKS = "./Resources/Tasks.txt";

Task::Task() :
		taskId(0), content(""), userId(0), assignmentDate(), plannedDate(), dateDelivery(), notation(
				"") {
}

Task::Task(unsigned int taskId, string content, unsigned int userId,
		Date assignmentDate, Date plannedDate, Date dateDelivery,
		string notation) :
		taskId(taskId), content(content), userId(userId), assignmentDate(
				assignmentDate), plannedDate(plannedDate), dateDelivery(
				dateDelivery), notation(notation) {
}

Task::Task(const Task& obj) :
		taskId(obj.taskId), content(obj.content), userId(obj.userId), assignmentDate(
				obj.assignmentDate), plannedDate(obj.plannedDate), dateDelivery(
				obj.dateDelivery), notation(obj.notation) {
}

Task::~Task() {
}

void Task::setTaskId(unsigned int taskId) {
	this->taskId = taskId;
}

void Task::setContent(string content) {
	this->content = content;
}

void Task::setUserId(unsigned int userId) {
	this->userId = userId;
}

void Task::setAssignmentDate(const Date& assignmentDate) {
	this->assignmentDate = assignmentDate;
}

void Task::setPlannedDate(const Date& plannedDate) {
	this->plannedDate = plannedDate;
}

void Task::setDateDelivery(const Date& dateDelivery) {
	this->dateDelivery = dateDelivery;
}

void Task::setNotation(string notation) {
	this->notation = notation;
}

unsigned int Task::getTaskId() {
	return this->taskId;
}

string Task::getContent() {
	return this->content;
}

unsigned int Task::getUserId() {
	return this->userId;
}

Date& Task::getAssignmentDate() {
	return this->assignmentDate;
}

Date& Task::getPlannedDate() {
	return this->plannedDate;
}

Date& Task::getDateDelivery() {
	return this->dateDelivery;
}

string Task::getNotation() {
	return this->notation;
}

string Task::toString() {
	string str;
	str.append("[Task@");
	str.append("taskId=");
	str.append(to_string(this->taskId));
	str.append(",content=");
	str.append(this->content);
	str.append(",userId=");
	str.append(to_string(this->userId));
	str.append(",assignmentDate=");
	str.append(this->assignmentDate.toString());
	str.append(",plannedDate=");
	str.append(this->plannedDate.toString());
	str.append(",dateDelivery=");
	str.append(this->dateDelivery.toString());
	str.append(",notation=");
	str.append(this->notation);
	str.append("]");
	return str;
}

Task& Task::operator=(const Task& obj) {
	this->userId = obj.userId;
	this->content = obj.content;
	this->taskId = obj.taskId;
	this->assignmentDate = obj.assignmentDate;
	this->plannedDate = obj.plannedDate;
	this->dateDelivery = obj.dateDelivery;
	this->notation = obj.notation;
	return *this;
}

bool operator<(const Task& obj1, const  Task& obj2) {
	return obj1.userId < obj2.userId;
}

bool operator==(const Task& obj1, const Task& obj2) {
	return obj1.taskId == obj2.taskId;
}

ostream& operator<<(ostream& stream, Task& obj) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if(obj.dateDelivery.getYear() == 0){
		if(obj.plannedDate-Date::getTodayDate() < 1){
			SetConsoleTextAttribute(hConsole, (WORD) ( 4 | 0));
		}
		else if(obj.plannedDate-Date::getTodayDate() < 4){
			SetConsoleTextAttribute(hConsole, (WORD) ( 14 | 0));
		}
		else if(obj.plannedDate-Date::getTodayDate() < 7){
			SetConsoleTextAttribute(hConsole, (WORD) ( 1 | 0));
		}
	}
	stream << setw(24) << right << "ID# задания: " << left << obj.taskId << "\n"
			<< setw(24) << right << "ID# пользователя: " << left << obj.userId << "\n"
			<< setw(24) << right << "Дата выдачи задания: " << left << obj.assignmentDate << "\n"
			<< setw(24) << right << "Дата планируемой сдачи: " << left << obj.plannedDate << "\n"
			<< setw(24) << right << "Дата сдачи задания: " << left << obj.dateDelivery << "\n"
			<< setw(24) << right << "Задание: " << left << obj.content << "\n"
			<< setw(24) << right << "Примечание: " << left << obj.notation << "\n";
	SetConsoleTextAttribute(hConsole, (WORD) ( 15 | 0));
	return stream;
}

istream& operator>>(istream& stream, Task& obj){
	cout<<"Задания"<<endl;
	obj.content=inputLine(stream);
	cout<<"Идентификатор сотрудника, которому присвоится задание"<<endl;
	obj.userId=inputUnsignedInt(stream);
	struct tm *tim;
	time_t tt = time(NULL);
	tim = localtime(&tt);
	obj.assignmentDate.setDay(tim->tm_mday);
	obj.assignmentDate.setMonth(tim->tm_mon+1);
	obj.assignmentDate.setYear(tim->tm_year+1900);
	cout<<"Дата выдачи задания (сегодняшняя дата): "<< obj.assignmentDate <<endl;
	cout<<"Планируемая дата сдачи выполненного задания"<<endl;
	stream>>obj.plannedDate;
	cout<<"Примечание"<<endl;
	obj.notation=inputLine(stream);
	return stream;
}

ofstream& operator<<(ofstream& fstream, Task& obj) {
	fstream << obj.taskId << " ";
	fstream << obj.content.length() << " ";
	fstream << obj.content << " ";
	fstream << obj.userId << " ";
	fstream << obj.assignmentDate << " ";
	fstream << obj.plannedDate << " ";
	fstream << obj.dateDelivery << " ";
	fstream << obj.notation.length() << " ";
	fstream << obj.notation;
	return fstream;
}

ifstream& operator>>(ifstream& fstream, Task& obj) {
	size_t size_content, size_notation;
	fstream >> obj.taskId >> size_content;
	fstream.get();
	obj.content.clear();
	for (size_t i = 0; i < size_content; i++) {
		obj.content += fstream.get();
	}
	fstream >> obj.userId;
	fstream >> obj.assignmentDate;
	fstream >> obj.plannedDate;
	fstream >> obj.dateDelivery;
	fstream >> size_notation;
	fstream.get();
	obj.notation.clear();
	for (size_t i = 0; i < size_notation; i++) {
		obj.notation += fstream.get();
	}
	return fstream;
}
