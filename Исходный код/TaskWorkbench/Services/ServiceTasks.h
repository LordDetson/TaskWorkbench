/*
 * ServiceTasks.h
 *
 *  Created on: 21 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef SERVICES_TASKS_H_
#define SERVICES_TASKS_H_
#include <iostream>
#include <list>
#include <ctime>
#include "../Data_Classes/Task.h"
#include "../Data_Classes/UserAccount.h"
#include "../Ñontrollers/ControllerIOFStream.h"
#include "../Screens/ExceptionScreen.h"
#include "ServiceData.h"

class ServiceTasks {
private:
	ServiceTasks();
	ServiceTasks(const ServiceTasks&);
	~ServiceTasks();
	ServiceTasks& operator=(const ServiceTasks&);
public:
	static const string PATH_FREE_TASKID;

	static bool compTaskByTaskId(Task& first, Task& second);
	static bool compTaskByContent(Task& first, Task& second);
	static bool compTaskByAssignmentDate(Task& first, Task& second);
	static bool compTaskByPlannedDate(Task& first, Task& second);
	static bool compTaskByDateDelivery(Task& first, Task& second);
	static bool compTaskByNotation(Task& first, Task& second);

	static bool recompTaskByTaskId(Task& first, Task& second);
	static bool recompTaskByContent(Task& first, Task& second);
	static bool recompTaskByUserId(Task& first, Task& second);
	static bool recompTaskByAssignmentDate(Task& first, Task& second);
	static bool recompTaskByPlannedDate(Task& first, Task& second);
	static bool recompTaskByDateDelivery(Task& first, Task& second);
	static bool recompTaskByNotation(Task& first, Task& second);

	static list<Task>::iterator findTaskByTaskId(
			list<Task>::iterator begin, list<Task>::iterator end,
			unsigned int taskId);
	static list<Task>::iterator findTaskByContent(
			list<Task>::iterator begin, list<Task>::iterator end,
			string content);
	static list<Task>::iterator findTaskByUserId(
			list<Task>::iterator begin, list<Task>::iterator end,
			unsigned int userId);
	static list<Task>::iterator findTaskByAssignmentDate(
			list<Task>::iterator begin, list<Task>::iterator end,
			Date assignmentDate);
	static list<Task>::iterator findTaskByPlannedDate(
			list<Task>::iterator begin, list<Task>::iterator end,
			Date plannedDate);
	static list<Task>::iterator findTaskByDateDelivery(
			list<Task>::iterator begin, list<Task>::iterator end,
			Date dateDelivery);
	static list<Task>::iterator findTaskByNotation(
			list<Task>::iterator begin, list<Task>::iterator end,
			string notation);

	static void addTask(list<Task>&, list<UserAccount>&, list<unsigned int>&);
	static void editingContentTask(list<Task>::iterator&);
	static void editingUserIdTask(list<Task>::iterator&, list<UserAccount>&);
	static void editingPlannedDateTask(list<Task>::iterator&);
	static void editingDateDeliveryTask(list<UserAccount>::iterator&, list<Task>::iterator&);
	static void editingNotationTask(list<Task>::iterator&);
	static void editingAllDataTask(list<Task>::iterator&, list<UserAccount>&);

	static void deleteTask(list<Task>&, list<unsigned int>&);
	static void deleteTaskByIterator(list<Task>&, list<Task>::iterator&, list<unsigned int>&);
	static void deleteAllTask(list<Task>&, list<unsigned int>&);

	static void showOverdueTasks(list<Task>&);
	static void showTasksByUserId(list<Task>&);
	static void showOverdueTasksToThreeDays(list<Task>&);
};

#endif /* SERVICES_TASKS_H_ */
