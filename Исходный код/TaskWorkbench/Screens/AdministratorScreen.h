/*
 * AdministratorScreen.h
 *
 *  Created on: 13 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef SCREENS_ADMINISTRATORSCREEN_H_
#define SCREENS_ADMINISTRATORSCREEN_H_

#include <iostream>
#include <string>
#include <list>
#include "../Data_Classes/UserAccount.h"
#include "../Data_Classes/Task.h"
#include "../Services/ServiceData.h"
#include "../Services/ServiceUserAccounts.h"
#include "../Services/ServiceTasks.h"
#include "../Ñontrollers/ControllerIStream.h"
#include "../Ñontrollers/ControllerIOFStream.h"
#include "ExceptionScreen.h"
using namespace std;

class AdministratorScreen {
private:
	list<UserAccount> *ListUserAccounts;
	list<unsigned int> ListFreeUserId;
	list<Task> *ListTasks;
	list<unsigned int> ListFreeTaskId;
	static bool created;

	AdministratorScreen(list<UserAccount>&, list<Task>&);
	AdministratorScreen(const AdministratorScreen&);
	~AdministratorScreen();
	AdministratorScreen& operator=(const AdministratorScreen&);
	void accountManagementMenu();
	void tasksAndStatisticsMenu();
	void editingUserAccountMenu();
	void editingTaskMenu();
	void sortInAscendingOrderUserAccountsMenu();
	void sortInAscendingOrderTasksMenu();
	void sortInDecreasingOrderUserAccountsMenu();
	void sortInDecreasingOrderTasksMenu();
	void findUserAccountMenu();
	void findTaskMenu();
public:
	static AdministratorScreen& instance(list<UserAccount>&, list<Task>&);
	void showAdministratorScreen();
};

#endif /* SCREENS_ADMINISTRATORSCREEN_H_ */
