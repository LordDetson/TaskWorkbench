/*
 * AdministratorScreen.cpp
 *
 *  Created on: 13 нояб. 2017 г.
 *      Author: Дмитрий
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
		cout<<"----------Главное меню администратора----------"<<endl;
		cout << "1.\tУчетные записи пользователей\n"
				<< "2.\tЗадания и статистика\n" << "3.\tСохранение изменений\n"
				<< "0.\tВыйти" << endl;
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
			cout << "Изменения сохранены" << endl;
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
		cout<<"----------Меню управления учетными записями пользователя----------"<<endl;
		cout << "1.\tДобавить учетную запись пользователя\n"
				<< "2.\tРедактировать учетную запись пользователя\n"
				<< "3.\tУдаление учетной записи пользователя\n"
				<< "4.\tУдаление всех учетных записей пользователей\n"
				<< "5.\tСортировка по возрастанию/А-Я\n"
				<< "6.\tСортировка по убыванию/Я-А\n" << "7.\tПоиск\n"
				<< "0.\tВернуться" << endl;
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
		cout<<"----------Меню управления заданийми----------"<<endl;
		cout << "1.\tДобавить задание\n" << "2.\tРедактировать задание\n"
				<< "3.\tУдаление задания\n" << "4.\tУдаление всех заданий\n"
				<< "5.\tСортировка по возрастанию/А-Я\n"
				<< "6.\tСортировка по убыванию/Я-А\n" << "7.\tПоиск\n"
				<< "8.\tСписок просроченных заданий\n"
				<< "9.\tСписок заданий у заданного сотрудника\n"
				<< "10.\tСписок заданий, до истечения срока выполнения которых осталось X дней\n"
				<< "0.\tВернуться" << endl;
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
			<< "Введите индентификатор пользователя, данные которого необходимо изменить"
			<< endl;
	unsigned int inputUserId = inputUnsignedInt(cin);
	ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
	list<UserAccount>::iterator findUserAccount =
			ServiceUserAccounts::findUserAccountByUserId(
					ListUserAccounts->begin(), ListUserAccounts->end(),
					inputUserId);
	if (findUserAccount != ListUserAccounts->end()) {
		cout
				<< "Подтвердите редактирование этой учетной записи пользователя (пароль)\n"
				<< (*findUserAccount) << endl;
		string passwordAccount(inputString(cin));
		if (HashPasswordWithSal()(passwordAccount,
				(*findUserAccount).getSurname())
				== (*findUserAccount).getPassword()) {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findUserAccount) << endl;
				cout<<"----------Меню редактирования учетных записей пользователей----------"<<endl;
				cout << "1.\tФамилию Имя Отчество учетной записи пользователя\n"
						<< "2.\tОтдел учетной записи пользователя\n"
						<< "3.\tПароль учетной записи пользователя\n"
						<< "4.\tВсе данные об учетной записи пользователя\n"
						<< "0.\tВернуться" << endl;
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
	cout << "Введите индентификатор заданя, данные которого необходимо изменить"
			<< endl;
	unsigned int inputTaskId = inputUnsignedInt(cin);
	ListTasks->sort(ServiceTasks::compTaskByTaskId);
	list<Task>::iterator findTask = ServiceTasks::findTaskByTaskId(
			ListTasks->begin(), ListTasks->end(), inputTaskId);
	list<UserAccount>::iterator activeAccount = (*ListUserAccounts).begin();
	if (findTask != ListTasks->end()) {
		cout << "Подтвердите редактирование этого задания (да/нет)\n"
				<< (*findTask) << endl;
		string confirmation(inputString(cin));
		if (confirmation == "да") {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findTask) << endl;
				cout<<"----------Меню редактирования заданий----------"<<endl;
				cout << "1.\tЗадание\n"
						<< "2.\tПренадлежность задания к пользователю\n"
						<< "3.\tПланируемую дату сдачи\n"
						<< "4.\tДату сдачи задания\n" << "5.\tПримечание\n"
						<< "6.\tВсе данные о задании\n" << "0.\tВернуться"
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
		if (confirmation != "да" && confirmation != "нет")
			showExceptionScreen();
	} else
		showNotFindData();
}

void AdministratorScreen::sortInAscendingOrderUserAccountsMenu() {
	unsigned int variation;
	system("cls");
	cout<<"-----Меню сортировки списка учетных записей пользователей по возрастанию-----"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n" << "3.\tПо имени\n"
			<< "4.\tПо отчеству\n" << "5.\tПо отделам\n" << "0.\tВернуться"
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
	cout<<"----------Меню сортировки списка заданий по возрастанию----------"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
			<< "3.\tПо индексу сотрудника, которому выдано задание\n"
			<< "4.\tПо дате выдачи задания\n"
			<< "5.\tПо дате планируемой сдачи задания\n"
			<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
			<< "0.\tВернуться" << endl;
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
	cout<<"-----Меню сортировки списка учетных записей пользователей по убыванию-----"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n"
			<< "3.\tПо имени\n" << "4.\tПо отчеству\n" << "5.\tПо отделам\n"
			<< "0.\tВернуться" << endl;
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
	cout<<"----------Меню сортировки списка заданий по убыванию----------"<<endl;
	cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
			<< "3.\tПо по индексу сотрудника, которому выдано задание\n"
			<< "4.\tПо дате выдачи задания\n"
			<< "5.\tПо дате планируемой сдачи задания\n"
			<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
			<< "0.\tВернуться" << endl;
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
		cout<<"----------Меню поиска учетных записей пользователей----------"<<endl;
		cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n"
				<< "3.\tПо имени\n" << "4.\tПо отчеству\n" << "5.\tПо отделам\n"
				<< "0.\tВернуться" << endl;
		variation = inputUnsignedInt(cin);
		list<UserAccount> findListUserAccounts;
		list<UserAccount>::iterator begin = ListUserAccounts->begin();
		list<UserAccount>::iterator end = ListUserAccounts->end();
		string str;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int userId;
			cout << "Введите идентификатор для поиска нужной записи" << endl;
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
					<< "Введите фамилию (начало/конец/часть фамилии) для поиска нужной записи"
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
					<< "Введите имя (начало/конец/часть имени) для поиска нужной записи"
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
					<< "Введите отчество (начало/конец/часть отчества) для поиска нужной записи"
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
					<< "Введите отдела (начало/конец/часть отдела) для поиска нужной записи"
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
		cout<<"----------Меню поиска заданий----------"<<endl;
		cout << "1.\tПо идентификатору\n" << "2.\tПо заданию\n"
				<< "3.\tПо по индексу сотрудника, которому выдано задание\n"
				<< "4.\tПо дате выдачи задания\n"
				<< "5.\tПо дате планируемой сдачи задания\n"
				<< "6.\tПо дате сдачи задания\n" << "7.\tПо примечанию\n"
				<< "0.\tВернуться" << endl;
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
