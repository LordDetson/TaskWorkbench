/*
 * UserScreen.cpp
 *
 *  Created on: 13 нояб. 2017 г.
 *      Author: Дмитрий
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
		cout<<"----------Главное меню пользователя----------"<<endl;
		cout<<"1.\tУведомить о выполнении задания\n"
				<<"2.\tСортировка по возрастанию/А-Я\n"
				<<"3.\tСортировка по убыванию/Я-А\n"
				<<"4.\tПоиск\n"
				<<"5.\tСписок просроченых задания\n"
				<<"6.\tСписок заданий, до истечения срока выполнения которых осталось 3 дней\n"
				<<"0.\tВыйти и сохранить изменения"
				<<endl;
		variation = inputUnsignedInt(cin);
		switch(variation){
		case 1:
		{
			system("cls");
			cout << "Введите индентификатор заданя, данные которого необходимо изменить"
					<< endl;
			unsigned int inputTaskId = inputUnsignedInt(cin);
			ListTasksBuff.sort(ServiceTasks::compTaskByTaskId);
			list<Task>::iterator findTask = ServiceTasks::findTaskByTaskId(
					ListTasksBuff.begin(), ListTasksBuff.end(), inputTaskId);
			if (findTask != ListTasksBuff.end()) {
				cout << "Подтвердите редактирование этого задания (да/нет)\n"
						<< (*findTask) << endl;
				string confirmation(inputString(cin));
				if (confirmation == "да") {
					ServiceTasks::editingDateDeliveryTask(*activeAccount,findTask);
				}
				if (confirmation != "да" && confirmation != "нет")
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
	cout<<"----------Меню для сортировки заданий в порядке возростания----------"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
			<< "3.\tПо по индексу сотрудника, которому выдано задание\n"
			<< "4.\tПо дате выдачи задания\n"
			<< "5.\tПо дате планируемой сдачи задания\n"
			<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
			<< "0.\tВернуться" << endl;
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
	cout<<"----------Меню для сортировки заданий в порядке убывания----------"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
			<< "3.\tПо по индексу сотрудника, которому выдано задание\n"
			<< "4.\tПо дате выдачи задания\n"
			<< "5.\tПо дате планируемой сдачи задания\n"
			<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
			<< "0.\tВернуться" << endl;
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
		cout<<"----------Меню для поиска заданий----------"<<endl;
		cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
				<< "3.\tПо по индексу сотрудника, которому выдано задание\n"
				<< "4.\tПо дате выдачи задания\n"
				<< "5.\tПо дате планируемой сдачи задания\n"
				<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
				<< "0.\tВернуться" << endl;
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
			cout << "Введите идентификатор для поиска нужной записи" << endl;
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
					<< "Введите задание (начало/конец/часть задания) для поиска нужной записи"
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
					<< "Введите идентификатор для поиска нужной записи"
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
					<< "Введите дату выдачи задания для поиска нужной записи"
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
					<< "Введите дату планируемой сдачи задания для поиска нужной записи"
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
					<< "Введите дату планируемой сдачи задания для поиска нужной записи"
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
					<< "Введите примечание (начало/конец/часть примечания) для поиска нужной записи"
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
