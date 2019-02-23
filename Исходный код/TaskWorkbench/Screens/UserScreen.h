/*
 * UserScreen.h
 *
 *  Created on: 13 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef SCREENS_USERSCREEN_H_
#define SCREENS_USERSCREEN_H_
#include <iostream>
#include <string>
#include <list>
#include "../Data_Classes/Task.h"
#include "../Services/ServiceData.h"
#include "../Services/ServiceTasks.h"
using namespace std;

class UserScreen {
private:
	list<Task> *ListTasks;
	list<Task> ListTasksBuff;
	list<UserAccount>::iterator *activeAccount;
	static bool created;

	UserScreen(list<Task>&, list<Task>&, list<UserAccount>::iterator&);
	~UserScreen();
	UserScreen(const UserScreen&);
	UserScreen& operator=(const UserScreen&);
	void sortInAscendingOrderTasksMenu();
	void sortInDecreasingOrderTasksMenu();
	void findTaskMenu();
public:
	static UserScreen& instance(list<Task>&, list<UserAccount>::iterator&);
	void showUserScreen();
};

#endif /* SCREENS_USERSCREEN_H_ */
