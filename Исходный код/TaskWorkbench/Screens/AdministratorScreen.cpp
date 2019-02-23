/*
 * AdministratorScreen.cpp
 *
 *  Created on: 13 ����. 2017 �.
 *      Author: �������
 */

#include "AdministratorScreen.h"

bool AdministratorScreen::created = false;
AdministratorScreen::AdministratorScreen(list<UserAccount> &ListUserAccounts,
		list<Task> &ListTasks) {
	this->ListUserAccounts = &ListUserAccounts;
	this->ListTasks = &ListTasks;
	this->created = true;
	this->ListFreeUserId = readFile(ServiceUserAccounts::PATH_FREE_USERID,
			ListFreeUserId);
	this->ListFreeTaskId = readFile(ServiceTasks::PATH_FREE_TASKID,
			ListFreeTaskId);
}

AdministratorScreen::~AdministratorScreen() {
}

AdministratorScreen& AdministratorScreen::instance(
		list<UserAccount> &ListUserAccounts, list<Task> &ListTasks) {
	static AdministratorScreen *inst;
	if (!created)
		inst = new AdministratorScreen(ListUserAccounts, ListTasks);
	return *inst;
}

void AdministratorScreen::showAdministratorScreen() {
	unsigned int variation;
	while (true) {
		system("cls");
		cout<<"----------������� ���� ��������������----------"<<endl;
		cout << "1.\t������� ������ �������������\n"
				<< "2.\t������� � ����������\n" << "3.\t���������� ���������\n"
				<< "0.\t�����" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			accountManagementMenu();
			break;
		case 2:
			tasksAndStatisticsMenu();
			break;
		case 3:
			ListUserAccounts->sort(
					ServiceUserAccounts::compUserAccountByUserId);
			ListTasks->sort(ServiceTasks::compTaskByTaskId);
			writeFile(UserAccount::PATH_USER_ACCOUNTS, *ListUserAccounts);
			writeFile(Task::PATH_TASKS, *ListTasks);
			writeFile(ServiceUserAccounts::PATH_FREE_USERID, ListFreeUserId);
			writeFile(ServiceTasks::PATH_FREE_TASKID, ListFreeTaskId);
			*ListUserAccounts = readFile(UserAccount::PATH_USER_ACCOUNTS,
					*ListUserAccounts);
			*ListTasks = readFile(Task::PATH_TASKS, *ListTasks);
			ListFreeUserId = readFile(ServiceUserAccounts::PATH_FREE_USERID,
					ListFreeUserId);
			ListFreeTaskId = readFile(ServiceTasks::PATH_FREE_TASKID,
					ListFreeTaskId);
			system("cls");
			cout << "��������� ���������" << endl;
			system("pause");
			break;
		case 0:
			ListUserAccounts->sort(
					ServiceUserAccounts::compUserAccountByUserId);
			ListTasks->sort(ServiceTasks::compTaskByTaskId);
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void AdministratorScreen::accountManagementMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(*ListUserAccounts);
		cout<<"----------���� ���������� �������� �������� ������������----------"<<endl;
		cout << "1.\t�������� ������� ������ ������������\n"
				<< "2.\t������������� ������� ������ ������������\n"
				<< "3.\t�������� ������� ������ ������������\n"
				<< "4.\t�������� ���� ������� ������� �������������\n"
				<< "5.\t���������� �� �����������/�-�\n"
				<< "6.\t���������� �� ��������/�-�\n" << "7.\t�����\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			ServiceUserAccounts::addUserAccount(*ListUserAccounts, ListFreeUserId);
			break;
		case 2:
			editingUserAccountMenu();
			break;
		case 3:
			ServiceUserAccounts::deleteUserAccountAndTasks(*ListUserAccounts,
					*ListTasks, ListFreeUserId, ListFreeTaskId);
			break;
		case 4:
			ServiceUserAccounts::deleteAllUserAccountsAndTasks(
					*ListUserAccounts, *ListTasks, ListFreeUserId,
					ListFreeTaskId);
			break;
		case 5:
			sortInAscendingOrderUserAccountsMenu();
			break;
		case 6:
			sortInDecreasingOrderUserAccountsMenu();
			break;
		case 7:
			findUserAccountMenu();
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void AdministratorScreen::tasksAndStatisticsMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(*ListTasks);
		cout<<"----------���� ���������� ���������----------"<<endl;
		cout << "1.\t�������� �������\n" << "2.\t������������� �������\n"
				<< "3.\t�������� �������\n" << "4.\t�������� ���� �������\n"
				<< "5.\t���������� �� �����������/�-�\n"
				<< "6.\t���������� �� ��������/�-�\n" << "7.\t�����\n"
				<< "8.\t������ ������������ �������\n"
				<< "9.\t������ ������� � ��������� ����������\n"
				<< "10.\t������ �������, �� ��������� ����� ���������� ������� �������� X ����\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			ServiceTasks::addTask(*ListTasks, *ListUserAccounts, ListFreeTaskId);
			break;
		case 2:
			editingTaskMenu();
			break;
		case 3:
			ServiceTasks::deleteTask(*ListTasks, ListFreeTaskId);
			break;
		case 4:
			ServiceTasks::deleteAllTask(*ListTasks, ListFreeTaskId);
			break;
		case 5:
			sortInAscendingOrderTasksMenu();
			break;
		case 6:
			sortInDecreasingOrderTasksMenu();
			break;
		case 7:
			findTaskMenu();
			break;
		case 8:
			ServiceTasks::showOverdueTasks(*ListTasks);
			break;
		case 9:
			ServiceTasks::showTasksByUserId(*ListTasks);
			break;
		case 10:
			ServiceTasks::showOverdueTasksToThreeDays(*ListTasks);
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void AdministratorScreen::editingUserAccountMenu() {
	system("cls");
	cout
			<< "������� �������������� ������������, ������ �������� ���������� ��������"
			<< endl;
	unsigned int inputUserId = inputUnsignedInt(cin);
	ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
	list<UserAccount>::iterator findUserAccount =
			ServiceUserAccounts::findUserAccountByUserId(
					ListUserAccounts->begin(), ListUserAccounts->end(),
					inputUserId);
	if (findUserAccount != ListUserAccounts->end()) {
		cout
				<< "����������� �������������� ���� ������� ������ ������������ (������)\n"
				<< (*findUserAccount) << endl;
		string passwordAccount(inputString(cin));
		if (HashPasswordWithSal()(passwordAccount,
				(*findUserAccount).getSurname())
				== (*findUserAccount).getPassword()) {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findUserAccount) << endl;
				cout<<"----------���� �������������� ������� ������� �������������----------"<<endl;
				cout << "1.\t������� ��� �������� ������� ������ ������������\n"
						<< "2.\t����� ������� ������ ������������\n"
						<< "3.\t������ ������� ������ ������������\n"
						<< "4.\t��� ������ �� ������� ������ ������������\n"
						<< "0.\t���������" << endl;
				variation = inputUnsignedInt(cin);
				switch (variation) {
				case 1:
					ServiceUserAccounts::editingSNMUserAccount(findUserAccount,
							passwordAccount);
					ListUserAccounts->sort();
					break;
				case 2:
					ServiceUserAccounts::editingDepartmentUserAccount(
							findUserAccount);

					break;
				case 3:
					ServiceUserAccounts::editingPasswordUserAccount(
							findUserAccount, passwordAccount);
					break;
				case 4:
					ServiceUserAccounts::editingAllDataUserAccount(
							findUserAccount);
					ListUserAccounts->sort();
					break;
				case 0:
					break;
				default:
					showExceptionScreen();
				}
				if (variation == 0)
					break;
			}
		} else
			showExceptionScreen();
	} else
		showNotFindData();
}

void AdministratorScreen::editingTaskMenu() {
	system("cls");
	cout << "������� �������������� ������, ������ �������� ���������� ��������"
			<< endl;
	unsigned int inputTaskId = inputUnsignedInt(cin);
	ListTasks->sort(ServiceTasks::compTaskByTaskId);
	list<Task>::iterator findTask = ServiceTasks::findTaskByTaskId(
			ListTasks->begin(), ListTasks->end(), inputTaskId);
	list<UserAccount>::iterator activeAccount = (*ListUserAccounts).begin();
	if (findTask != ListTasks->end()) {
		cout << "����������� �������������� ����� ������� (��/���)\n"
				<< (*findTask) << endl;
		string confirmation(inputString(cin));
		if (confirmation == "��") {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findTask) << endl;
				cout<<"----------���� �������������� �������----------"<<endl;
				cout << "1.\t�������\n"
						<< "2.\t�������������� ������� � ������������\n"
						<< "3.\t����������� ���� �����\n"
						<< "4.\t���� ����� �������\n" << "5.\t����������\n"
						<< "6.\t��� ������ � �������\n" << "0.\t���������"
						<< endl;
				variation = inputUnsignedInt(cin);
				switch (variation) {
				case 1:
					ServiceTasks::editingContentTask(findTask);
					break;
				case 2:
					ServiceTasks::editingUserIdTask(findTask,
							*ListUserAccounts);
					break;
				case 3:
					ServiceTasks::editingPlannedDateTask(findTask);
					break;
				case 4:
					ServiceTasks::editingDateDeliveryTask(activeAccount,
							findTask);
					break;
				case 5:
					ServiceTasks::editingNotationTask(findTask);
					break;
				case 6:
					ServiceTasks::editingAllDataTask(findTask,
							*ListUserAccounts);
					break;
				case 0:
					break;
				default:
					showExceptionScreen();
				}
				if (variation == 0)
					break;
			}
		}
		if (confirmation != "��" && confirmation != "���")
			showExceptionScreen();
	} else
		showNotFindData();
}

void AdministratorScreen::sortInAscendingOrderUserAccountsMenu() {
	unsigned int variation;
	system("cls");
	cout<<"-----���� ���������� ������ ������� ������� ������������� �� �����������-----"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n" << "3.\t�� �����\n"
			<< "4.\t�� ��������\n" << "5.\t�� �������\n" << "0.\t���������"
			<< endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
		break;
	case 2:
		ListUserAccounts->sort();
		break;
	case 3:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByName);
		break;
	case 4:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByMidname);
		break;
	case 5:
		ListUserAccounts->sort(
				ServiceUserAccounts::compUserAccountByDepartment);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::sortInAscendingOrderTasksMenu() {
	unsigned int variation;
	system("cls");
	cout<<"----------���� ���������� ������ ������� �� �����������----------"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
			<< "3.\t�� ������� ����������, �������� ������ �������\n"
			<< "4.\t�� ���� ������ �������\n"
			<< "5.\t�� ���� ����������� ����� �������\n"
			<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
			<< "0.\t���������" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListTasks->sort(ServiceTasks::compTaskByTaskId);
		break;
	case 2:
		ListTasks->sort(ServiceTasks::compTaskByContent);
		break;
	case 3:
		ListTasks->sort();
		break;
	case 4:
		ListTasks->sort(ServiceTasks::compTaskByAssignmentDate);
		break;
	case 5:
		ListTasks->sort(ServiceTasks::compTaskByPlannedDate);
		break;
	case 6:
		ListTasks->sort(ServiceTasks::compTaskByDateDelivery);
		break;
	case 7:
		ListTasks->sort(ServiceTasks::compTaskByNotation);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::sortInDecreasingOrderUserAccountsMenu() {
	unsigned int variation;
	system("cls");
	cout<<"-----���� ���������� ������ ������� ������� ������������� �� ��������-----"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
			<< "3.\t�� �����\n" << "4.\t�� ��������\n" << "5.\t�� �������\n"
			<< "0.\t���������" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByUserId);
		break;
	case 2:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountBySurname);
		break;
	case 3:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByName);
		break;
	case 4:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByMidname);
		break;
	case 5:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByDepartment);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::sortInDecreasingOrderTasksMenu(){
	unsigned int variation;
	system("cls");
	cout<<"----------���� ���������� ������ ������� �� ��������----------"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
			<< "3.\t�� �� ������� ����������, �������� ������ �������\n"
			<< "4.\t�� ���� ������ �������\n"
			<< "5.\t�� ���� ����������� ����� �������\n"
			<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
			<< "0.\t���������" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListTasks->sort(ServiceTasks::recompTaskByTaskId);
		break;
	case 2:
		ListTasks->sort(ServiceTasks::recompTaskByContent);
		break;
	case 3:
		ListTasks->sort(ServiceTasks::recompTaskByUserId);
		break;
	case 4:
		ListTasks->sort(ServiceTasks::recompTaskByAssignmentDate);
		break;
	case 5:
		ListTasks->sort(ServiceTasks::recompTaskByPlannedDate);
		break;
	case 6:
		ListTasks->sort(ServiceTasks::recompTaskByDateDelivery);
		break;
	case 7:
		ListTasks->sort(ServiceTasks::recompTaskByNotation);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::findUserAccountMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
		cout<<"----------���� ������ ������� ������� �������������----------"<<endl;
		cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
				<< "3.\t�� �����\n" << "4.\t�� ��������\n" << "5.\t�� �������\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		list<UserAccount> findListUserAccounts;
		list<UserAccount>::iterator begin = ListUserAccounts->begin();
		list<UserAccount>::iterator end = ListUserAccounts->end();
		string str;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int userId;
			cout << "������� ������������� ��� ������ ������ ������" << endl;
			userId = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByUserId(begin, end,
						userId);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				system("pause");
			} else
				showNotFindData();
			break;
		case 2:
			system("cls");
			cout
					<< "������� ������� (������/�����/����� �������) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountBySurname(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				system("pause");
			} else
				showNotFindData();
			break;
		case 3:
			system("cls");
			cout
					<< "������� ��� (������/�����/����� �����) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByName(begin, end,
						str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				system("pause");
			} else
				showNotFindData();
			break;
		case 4:
			system("cls");
			cout
					<< "������� �������� (������/�����/����� ��������) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByMidname(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				system("pause");
			} else
				showNotFindData();
			break;
		case 5:
			system("cls");
			cout
					<< "������� ������ (������/�����/����� ������) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByDepartment(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				system("pause");
			} else
				showNotFindData();
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
		system("pause");
	}
}

void AdministratorScreen::findTaskMenu(){
	unsigned int variation;
	while (true) {
		system("cls");
		ListTasks->sort(ServiceTasks::compTaskByTaskId);
		cout<<"----------���� ������ �������----------"<<endl;
		cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
				<< "3.\t�� �� ������� ����������, �������� ������ �������\n"
				<< "4.\t�� ���� ������ �������\n"
				<< "5.\t�� ���� ����������� ����� �������\n"
				<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		list<Task> findListTasks;
		list<Task>::iterator begin = ListTasks->begin();
		list<Task>::iterator end = ListTasks->end();
		string str;
		Date d;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int taskId;
			cout << "������� ������������� ��� ������ ������ ������" << endl;
			taskId = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceTasks::findTaskByTaskId(begin,end,taskId);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 2:
			system("cls");
			cout
					<< "������� ������� (������/�����/����� �������) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceTasks::findTaskByContent(begin,end,str);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 3:
			system("cls");
			unsigned int userId;
			cout
					<< "������� ������������� ��� ������ ������ ������"
					<< endl;
			userId = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceTasks::findTaskByUserId(begin,end,userId);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 4:
			system("cls");
			cout
					<< "������� ���� ������ ������� ��� ������ ������ ������"
					<< endl;
			cin >> d;
			while (true) {
				begin = ServiceTasks::findTaskByAssignmentDate(begin,end,d);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 5:
			system("cls");
			cout
					<< "������� ���� ����������� ����� ������� ��� ������ ������ ������"
					<< endl;
			cin >> d;
			while (true) {
				begin = ServiceTasks::findTaskByPlannedDate(begin,end,d);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 6:
			system("cls");
			cout
					<< "������� ���� ����������� ����� ������� ��� ������ ������ ������"
					<< endl;
			cin >> d;
			while (true) {
				begin = ServiceTasks::findTaskByDateDelivery(begin,end,d);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 7:
			system("cls");
			cout
					<< "������� ���������� (������/�����/����� ����������) ��� ������ ������ ������"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceTasks::findTaskByNotation(begin,end,str);
				if (begin == end)
					break;
				findListTasks.push_back(*begin);
				begin++;
			}
			if (findListTasks.size() != 0) {
				showList(findListTasks);
				system("pause");
			} else
				showNotFindData();
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
		system("pause");
	}
}
