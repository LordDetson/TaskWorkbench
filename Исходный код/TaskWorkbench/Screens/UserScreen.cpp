/*
 * UserScreen.cpp
 *
 *  Created on: 13 ����. 2017 �.
 *      Author: �������
 */

#include "UserScreen.h"

bool UserScreen::created = false;

UserScreen::UserScreen(list<Task> &ListTasks, list<Task> &ListTasksBuff, list<UserAccount>::iterator &activeAccount) {
	this->ListTasks = &ListTasks;
	this->ListTasksBuff = ListTasksBuff;
	this->activeAccount = &activeAccount;
	this->created = true;
}

UserScreen::~UserScreen() {
}

UserScreen& UserScreen::instance(list<Task> &ListTasks,
		list<UserAccount>::iterator &activeAccount) {
	list<Task> ListTasksBuff;
	list<Task>::iterator begin = ListTasks.begin();
	list<Task>::iterator end = ListTasks.end();
	while (true) {
		begin = ServiceTasks::findTaskByUserId(begin, end, (*activeAccount).getUserId());
		if (begin == end)
			break;
		ListTasksBuff.push_back(*begin);
		begin++;
	}
	static UserScreen *inst;
	if (!created)
		inst = new UserScreen(ListTasks, ListTasksBuff, activeAccount);
	return *inst;
}

void UserScreen::showUserScreen() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(ListTasksBuff);
		cout<<"----------������� ���� ������������----------"<<endl;
		cout<<"1.\t��������� � ���������� �������\n"
				<<"2.\t���������� �� �����������/�-�\n"
				<<"3.\t���������� �� ��������/�-�\n"
				<<"4.\t�����\n"
				<<"5.\t������ ����������� �������\n"
				<<"6.\t������ �������, �� ��������� ����� ���������� ������� �������� 3 ����\n"
				<<"0.\t����� � ��������� ���������"
				<<endl;
		variation = inputUnsignedInt(cin);
		switch(variation){
		case 1:
		{
			system("cls");
			cout << "������� �������������� ������, ������ �������� ���������� ��������"
					<< endl;
			unsigned int inputTaskId = inputUnsignedInt(cin);
			ListTasksBuff.sort(ServiceTasks::compTaskByTaskId);
			list<Task>::iterator findTask = ServiceTasks::findTaskByTaskId(
					ListTasksBuff.begin(), ListTasksBuff.end(), inputTaskId);
			if (findTask != ListTasksBuff.end()) {
				cout << "����������� �������������� ����� ������� (��/���)\n"
						<< (*findTask) << endl;
				string confirmation(inputString(cin));
				if (confirmation == "��") {
					ServiceTasks::editingDateDeliveryTask(*activeAccount,findTask);
				}
				if (confirmation != "��" && confirmation != "���")
					showExceptionScreen();
			}
			else
				showNotFindData();
		}
			break;
		case 2:
			sortInAscendingOrderTasksMenu();
			break;
		case 3:
			sortInDecreasingOrderTasksMenu();
			break;
		case 4:
			findTaskMenu();
			break;
		case 5:
			ServiceTasks::showOverdueTasks(ListTasksBuff);
			break;
		case 6:
			ServiceTasks::showOverdueTasksToThreeDays(ListTasksBuff);
			break;
		case 0:
		{
			list<Task>::iterator findEditTask;
			for(Task t:ListTasksBuff){
				findEditTask = ServiceTasks::findTaskByTaskId((*ListTasks).begin(),(*ListTasks).end(),t.getTaskId());
				*findEditTask = t;
			}
			ListTasks->sort(ServiceTasks::compTaskByTaskId);
			writeFile(Task::PATH_TASKS, *ListTasks);
			break;
		}
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void UserScreen::sortInAscendingOrderTasksMenu(){
	unsigned int variation;
	system("cls");
	cout<<"----------���� ��� ���������� ������� � ������� �����������----------"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
			<< "3.\t�� �� ������� ����������, �������� ������ �������\n"
			<< "4.\t�� ���� ������ �������\n"
			<< "5.\t�� ���� ����������� ����� �������\n"
			<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
			<< "0.\t���������" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListTasksBuff.sort(ServiceTasks::compTaskByTaskId);
		break;
	case 2:
		ListTasksBuff.sort(ServiceTasks::compTaskByContent);
		break;
	case 3:
		ListTasksBuff.sort();
		break;
	case 4:
		ListTasksBuff.sort(ServiceTasks::compTaskByAssignmentDate);
		break;
	case 5:
		ListTasksBuff.sort(ServiceTasks::compTaskByPlannedDate);
		break;
	case 6:
		ListTasksBuff.sort(ServiceTasks::compTaskByDateDelivery);
		break;
	case 7:
		ListTasksBuff.sort(ServiceTasks::compTaskByNotation);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void UserScreen::sortInDecreasingOrderTasksMenu(){
	unsigned int variation;
	system("cls");
	cout<<"----------���� ��� ���������� ������� � ������� ��������----------"<<endl;
	cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
			<< "3.\t�� �� ������� ����������, �������� ������ �������\n"
			<< "4.\t�� ���� ������ �������\n"
			<< "5.\t�� ���� ����������� ����� �������\n"
			<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
			<< "0.\t���������" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListTasksBuff.sort(ServiceTasks::recompTaskByTaskId);
		break;
	case 2:
		ListTasksBuff.sort(ServiceTasks::recompTaskByContent);
		break;
	case 3:
		ListTasksBuff.sort(ServiceTasks::recompTaskByUserId);
		break;
	case 4:
		ListTasksBuff.sort(ServiceTasks::recompTaskByAssignmentDate);
		break;
	case 5:
		ListTasksBuff.sort(ServiceTasks::recompTaskByPlannedDate);
		break;
	case 6:
		ListTasksBuff.sort(ServiceTasks::recompTaskByDateDelivery);
		break;
	case 7:
		ListTasksBuff.sort(ServiceTasks::recompTaskByNotation);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void UserScreen::findTaskMenu(){

	unsigned int variation;
	while (true) {
		system("cls");
		cout<<"----------���� ��� ������ �������----------"<<endl;
		cout << "1.\t�� ��������������\n" << "2.\t�� �������\n"
				<< "3.\t�� �� ������� ����������, �������� ������ �������\n"
				<< "4.\t�� ���� ������ �������\n"
				<< "5.\t�� ���� ����������� ����� �������\n"
				<< "6.\t�� ���� ����� �������\n" << "7.\t�� ����������\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		list<Task> findListTasks;
		list<Task>::iterator begin = ListTasksBuff.begin();
		list<Task>::iterator end = ListTasksBuff.end();
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
