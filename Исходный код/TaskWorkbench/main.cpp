#include <iostream>
#include <list>
#include "./Screens/LoginAndPasswordScreen.h"
#include "./Screens/AdministratorScreen.h"
#include "./Screens/UserScreen.h"
#include "./Сontrollers/ControllerIOFStream.h"
#include "./Data_Classes/UserAccount.h"
#include "./Data_Classes/Task.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Date todayDate(Date::getTodayDate());
	cout << "Министерство связи и информатизации Республики Беларусь\n"
			<< "Учреждение образования\n"
			<< "БЕЛОРУССКАЯ ГОСУДАРСТВЕННАЯ АКАДЕМИЯ СВЯЗИ\n"
			<< "Факультет электросвязи\n"
			<< "Кафедра программного обеспечения сетей телекоммуникаций\n\n"
			<< "ПРЕДСТАВЛЯЕМ ВАШЕМУ ВНИМАНИЮ СИСТЕМУ УЧЕТА ВЫДАННЫХ ЗАДАНИЙ\n\n"
			<< "курсовой проект по дисциплине\n"
			<< "«Объектно-ориентированное программирование»\n\n" << setw(45) << left
			<< "Выполнил студент гр. СП641" << right << "Д. С. Бабанин\n"
			<< setw(45) << left << "Руководитель проекта" << right << "Т. Л. Труханович\n\n"
			<< left << "Минск 2017\n"
			<< "Сегодняшняя дата: " << todayDate << endl;
	system("pause");

	list<UserAccount> ListUserAccounts;
	ListUserAccounts = readFile(UserAccount::PATH_USER_ACCOUNTS,
			ListUserAccounts);
	list<Task> ListTasks;
	ListTasks = readFile(Task::PATH_TASKS, ListTasks);
	list<UserAccount>::iterator activeAccount =
			LoginAndPasswordScreen::instance(ListUserAccounts).showLoginAndPasswordScreen();
	if ((*activeAccount).getUserId() == 0) {
		AdministratorScreen::instance(ListUserAccounts, ListTasks).showAdministratorScreen();
		return 0;
	}
	UserScreen::instance(ListTasks, activeAccount).showUserScreen();
	return 0;
}
