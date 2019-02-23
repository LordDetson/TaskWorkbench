#include <iostream>
#include <list>
#include "./Screens/LoginAndPasswordScreen.h"
#include "./Screens/AdministratorScreen.h"
#include "./Screens/UserScreen.h"
#include "./�ontrollers/ControllerIOFStream.h"
#include "./Data_Classes/UserAccount.h"
#include "./Data_Classes/Task.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Date todayDate(Date::getTodayDate());
	cout << "������������ ����� � �������������� ���������� ��������\n"
			<< "���������� �����������\n"
			<< "����������� ��������������� �������� �����\n"
			<< "��������� ������������\n"
			<< "������� ������������ ����������� ����� ����������������\n\n"
			<< "������������ ������ �������� ������� ����� �������� �������\n\n"
			<< "�������� ������ �� ����������\n"
			<< "���������-��������������� ����������������\n\n" << setw(45) << left
			<< "�������� ������� ��. ��641" << right << "�. �. �������\n"
			<< setw(45) << left << "������������ �������" << right << "�. �. ����������\n\n"
			<< left << "����� 2017\n"
			<< "����������� ����: " << todayDate << endl;
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
