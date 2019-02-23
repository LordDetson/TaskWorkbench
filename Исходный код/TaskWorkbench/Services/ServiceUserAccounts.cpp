/*
 * ServiceUserAccounts.cpp
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "ServiceUserAccounts.h"

const string ServiceUserAccounts::PATH_FREE_USERID =
		"./Resources/FreeUserId.txt";

ServiceUserAccounts::ServiceUserAccounts() {
}

ServiceUserAccounts::~ServiceUserAccounts() {
}

bool ServiceUserAccounts::compUserAccountByUserId(UserAccount& first,
		UserAccount& second) {
	return first.getUserId() < second.getUserId();
}
bool ServiceUserAccounts::compUserAccountByName(UserAccount& first,
		UserAccount& second) {
	return (first.getName().compare(second.getName()) == -1 ? true : false);
}
bool ServiceUserAccounts::compUserAccountByMidname(UserAccount& first,
		UserAccount& second) {
	return (first.getMidname().compare(second.getMidname()) == -1 ? true : false);
}
bool ServiceUserAccounts::compUserAccountByDepartment(UserAccount& first,
		UserAccount& second) {
	return (first.getDepartment().compare(second.getDepartment()) == -1 ?
			true : false);
}
bool ServiceUserAccounts::recompUserAccountByUserId(UserAccount& first,
		UserAccount& second) {
	return first.getUserId() > second.getUserId();
}
bool ServiceUserAccounts::recompUserAccountBySurname(UserAccount& first,
		UserAccount& second) {
	return (first.getSurname().compare(second.getSurname()) == 1 ? true : false);
}
bool ServiceUserAccounts::recompUserAccountByName(UserAccount& first,
		UserAccount& second) {
	return (first.getName().compare(second.getName()) == 1 ? true : false);
}
bool ServiceUserAccounts::recompUserAccountByMidname(UserAccount& first,
		UserAccount& second) {
	return (first.getMidname().compare(second.getMidname()) == 1 ? true : false);
}
bool ServiceUserAccounts::recompUserAccountByDepartment(UserAccount& first,
		UserAccount& second) {
	return (first.getDepartment().compare(second.getDepartment()) == 1 ?
			true : false);
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountByUserId(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		unsigned int userId) {
	for (; begin != end; begin++)
		if (to_string((*begin).getUserId()).find(to_string(userId))!=string::npos)
			return begin;
	return end;
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountByPassword(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		string password) {
	for (; begin != end; begin++)
		if ((*begin).getPassword().find(password) != string::npos)
			return begin;
	return end;
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountBySurname(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		string surname) {
	for (; begin != end; begin++)
		if ((*begin).getSurname().find(surname) != string::npos)
			return begin;
	return end;
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountByName(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		string name) {
	for (; begin != end; begin++)
		if ((*begin).getName().find(name) != string::npos)
			return begin;
	return end;
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountByMidname(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		string midname) {
	for (; begin != end; begin++)
		if ((*begin).getMidname().find(midname) != string::npos)
			return begin;
	return end;
}

list<UserAccount>::iterator ServiceUserAccounts::findUserAccountByDepartment(
		list<UserAccount>::iterator begin, list<UserAccount>::iterator end,
		string department) {
	for (; begin != end; begin++)
		if ((*begin).getDepartment().find(department) != string::npos)
			return begin;
	return end;
}

void ServiceUserAccounts::addUserAccount(list<UserAccount> &ListUserAccounts, list<unsigned int> &ListFreeUserId) {
	system("cls");
	unsigned int maxUserIdInListNow = (*ListUserAccounts.begin()).getUserId();
	if (ListFreeUserId.size() == 0) {
		for (UserAccount ua : ListUserAccounts) {
			if (maxUserIdInListNow < ua.getUserId())
				maxUserIdInListNow = ua.getUserId();
		}
		maxUserIdInListNow++;
	} else {
		maxUserIdInListNow = *ListFreeUserId.begin();
		ListFreeUserId.pop_front();
	}
	UserAccount newUser;
	newUser.setUserId(maxUserIdInListNow);
	cout << "Введите данные о новом пользователе c идентификатором "
			<< newUser.getUserId() << "\n" << endl;
	cin >> newUser;
	cout << "Подтвердите создание новой учетной записи пользователя (да/нет)"
			<< endl;
	cout << newUser << endl;
	string confirmation(inputString(cin));
	if (confirmation == "да")
		ListUserAccounts.push_back(newUser);
	if (confirmation != "да" && confirmation != "нет")
		showExceptionScreen();
}

void ServiceUserAccounts::editingSNMUserAccount(list<UserAccount>::iterator& it,
		string passwordAccount) {
	cout << "Фамилия" << endl;
	(*it).setSurname(inputString(cin));
	(*it).setPasdword(
			HashPasswordWithSal()(passwordAccount, (*it).getSurname()));
	cout << "Имя" << endl;
	(*it).setName(inputString(cin));
	cout << "Отчество" << endl;
	(*it).setMidname(inputString(cin));
}

void ServiceUserAccounts::editingDepartmentUserAccount(
		list<UserAccount>::iterator& it) {
	cout << "Отдел" << endl;
	(*it).setDepartment(inputString(cin));
}

void ServiceUserAccounts::editingPasswordUserAccount(
		list<UserAccount>::iterator& it, string passwordAccount) {
	cout << "Новый пароль" << endl;
	passwordAccount = inputString(cin);
	(*it).setPasdword(
			HashPasswordWithSal()(passwordAccount, (*it).getSurname()));
}

void ServiceUserAccounts::editingAllDataUserAccount(
		list<UserAccount>::iterator& it) {
	cin >> (*it);
}

void ServiceUserAccounts::deleteUserAccountAndTasks(
		list<UserAccount> &ListUserAccounts, list<Task> &ListTasks, list<unsigned int> &ListFreeUserId, list<unsigned int> &ListFreeTaskId) {
	system("cls");
	cout
			<< "ВВедите индентификатор пользователя, данные которого необходимо удалить"
			<< endl;
	unsigned int inputUserId = inputUnsignedInt(cin);
	ListUserAccounts.sort(ServiceUserAccounts::compUserAccountByUserId);
	ListTasks.sort(ServiceTasks::compTaskByTaskId);
	if (inputUserId != 0) {
		list<UserAccount>::iterator findUserAccount = ServiceUserAccounts::findUserAccountByUserId(
				ListUserAccounts.begin(), ListUserAccounts.end(), inputUserId);
		if (findUserAccount != ListUserAccounts.end()) {
			cout
					<< "Подтвердите удаление учетной записи пользователя и всех его заданий (да/нет)"
					<< endl;
			cout << (*findUserAccount) << endl;
			string confirmation(inputString(cin));
			if (confirmation == "да")
				deleteUserAccountAndTasksByIterator(ListUserAccounts, ListTasks, findUserAccount, ListFreeUserId, ListFreeTaskId);
			if (confirmation != "да" && confirmation != "нет")
				showExceptionScreen();
		} else
			showNotFindData();
	} else
		cout << "Администратора удалить нельзя" << endl;
}

void ServiceUserAccounts::deleteUserAccountAndTasksByIterator(list<UserAccount> &ListUserAccounts, list<Task> &ListTasks, list<UserAccount>::iterator &findUserAccount, list<unsigned int> &ListFreeUserId, list<unsigned int> &ListFreeTaskId){
	while (true) {
		list<Task>::iterator begin = ListTasks.begin();
		list<Task>::iterator end = ListTasks.end();
		begin = ServiceTasks::findTaskByUserId(begin, end,
				(*findUserAccount).getUserId());
		if (begin == end)
			break;
		ServiceTasks::deleteTaskByIterator(ListTasks, begin, ListFreeTaskId);
	}
	ListFreeUserId.push_back((*findUserAccount).getUserId());
	ListUserAccounts.remove((*findUserAccount));
}

void ServiceUserAccounts::deleteAllUserAccountsAndTasks(
		list<UserAccount> &ListUserAccounts, list<Task> &ListTasks, list<unsigned int> &ListFreeUserId, list<unsigned int> &ListFreeTaskId) {
	cout
			<< "Подтвердите удаление всех учетных записей пользователей и всех заданий (да/нет)"
			<< endl;
	string confirmation(inputString(cin));
	if (confirmation == "да") {
		while(true){
			list<UserAccount>::iterator begin = ++ListUserAccounts.begin();
			list<UserAccount>::iterator end = ListUserAccounts.end();
			if(begin == end)
				break;
			ServiceUserAccounts::deleteUserAccountAndTasksByIterator(ListUserAccounts, ListTasks, begin, ListFreeUserId, ListFreeTaskId);
		}
	}
	if (confirmation != "да" && confirmation != "нет")
		showExceptionScreen();

}
